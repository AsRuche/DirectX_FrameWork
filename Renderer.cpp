#include "Renderer.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    // GPU 側の処理完了を待ってから終了
    WaitForGPU();

    if (m_fenceEvent)
    {
        CloseHandle(m_fenceEvent);
        m_fenceEvent = nullptr;
    }
}

// DirectX 12 を初期化 (デバイスやスワップチェーンの準備)
bool Renderer::Initialize(HWND hWnd, int width, int height)
{
	// デバイス作成などの初期化処理をまとめて行う
	if (!CreateDevice()) { return false; }                          // デバイス作成（Direct3D 12 の初期化）
	if (!CreateSwapChain(hWnd, width, height)) { return false; }	// スワップチェーン作成（バックバッファの管理など）
	if (!CreateCommandInterfaces()) { return false; }			    // コマンドインターフェース作成（GPUに対してコマンドを送るためのインターフェース）
	if (!CreateRTVHeapAndBuffers(width, height)) { return false; }  // RTV ヒープとバッファ作成（RTVはレンダリング結果を格納する為のバッファで、指定された幅と高さのバッファを作成）

    // フレームインデックス取得
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();        // バックバッファのインデックスを取得（スワップチェーンのバックバッファのインデックスを取得）

    // フェンス作成 & イベント作成
	if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))    // フェンスとは、GPUの処理が完了するまで待機するための仕組み
    {
		// フェンス作成失敗
        return false;
    }
	m_fenceValue = 1;// フェンスの初期値を1に設定

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);                             // このイベントは、GPUの処理が完了するまで待機するためのイベント
    if (!m_fenceEvent)
    {
        return false;
    }

    return true;
}

void Renderer::BeginFrame(float clearColor[4])
{
    // コマンドアロケータをリセット
    m_commandAllocator->Reset();
    // コマンドリストをリセット
    m_commandList->Reset(m_commandAllocator.Get(), nullptr);

    // 現在のバックバッファリソースを取得
    auto backBuffer = m_renderTargets[m_frameIndex].Get();

    // リソースバリア (出力合成用にトランジション)
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = backBuffer;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &barrier);

    // RTV (レンダーターゲットビュー) を取得
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        m_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
        m_frameIndex,
        m_rtvDescriptorSize
    );

    // RenderTarget をクリア
    m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
    m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

void Renderer::EndFrame()
{
    // バックバッファを Present 状態に移行
    auto backBuffer = m_renderTargets[m_frameIndex].Get();
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = backBuffer;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &barrier);

    // コマンドリストを閉じる
    m_commandList->Close();

    // コマンドリストを実行
    ID3D12CommandList* cmdLists[] = { m_commandList.Get() };
    m_commandQueue->ExecuteCommandLists(1, cmdLists);

    // Present (ダブルバッファ)
    m_swapChain->Present(1, 0);

    // 次フレームに備えて GPU 同期を取る
    WaitForGPU();

    // バックバッファインデックスを更新
    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

bool Renderer::CreateDevice()
{
#if defined(_DEBUG)
    // デバッグレイヤーを有効に (Debug モード時)
    {
        Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
    }
#endif

// DXGI ファクトリ生成
Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
{
    return false;
}

// アダプタ列挙 (今回は最初に見つかった HW アダプタを使う簡易例)
Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
for (UINT i = 0; ; i++)
{
    if (factory->EnumAdapters1(i, &adapter) == DXGI_ERROR_NOT_FOUND)
    {
        break;
    }
    DXGI_ADAPTER_DESC1 desc;
    adapter->GetDesc1(&desc);

    // ソフトウェアアダプタは回避
    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
    {
        continue;
    }
    // デバイス作成を試す
    if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
    {
        break;
    }
}

// もしアダプタ取得に失敗した場合は WARP を使う例
if (!m_device)
{
    Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
    factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
    if (FAILED(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
    {
        return false;
    }
}

return true;
}

bool Renderer::CreateSwapChain(HWND hWnd, int width, int height)
{
    // コマンドキューは SwapChain 前に必要なので一時的に作成しておく
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue))))
    {
        return false;
    }

    // DXGI ファクトリ再生成
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC1 scDesc = {};
    scDesc.BufferCount = FrameCount;
    scDesc.Width = width;
    scDesc.Height = height;
    scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scDesc.SampleDesc.Count = 1;

    Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
    if (FAILED(factory->CreateSwapChainForHwnd(
        m_commandQueue.Get(),
        hWnd,
        &scDesc,
        nullptr,
        nullptr,
        &swapChain1)))
    {
        return false;
    }

    if (FAILED(swapChain1.As(&m_swapChain)))
    {
        return false;
    }

    return true;
}

bool Renderer::CreateCommandInterfaces()
{
    // コマンドアロケータ作成
    if (FAILED(m_device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_commandAllocator))))
    {
        return false;
    }

    // コマンドリスト作成
    if (FAILED(m_device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_commandAllocator.Get(),
        nullptr, // PSO はまだ設定しない
        IID_PPV_ARGS(&m_commandList))))
    {
        return false;
    }

    // コマンドリストは最初開いた状態。即閉じておく
    m_commandList->Close();

    return true;
}

bool Renderer::CreateRTVHeapAndBuffers(int width, int height)
{
    // RTV 用ディスクリプタヒープ
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FrameCount;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap))))
    {
        return false;
    }

    m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // バックバッファのリソースを取得して RTV を作る
    for (UINT i = 0; i < FrameCount; i++)
    {
        if (FAILED(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]))))
        {
            return false;
        }
        CD3DX12_CPU_DESCRIPTOR_HANDLE handle(
            m_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
            i,
            m_rtvDescriptorSize);

        // RTV を作成
        m_device->CreateRenderTargetView(m_renderTargets[i].Get(), nullptr, handle);
    }

    return true;
}

void Renderer::WaitForGPU()
{
    // コマンドの完了をフェンスで待機
    const UINT64 currentFenceValue = m_fenceValue;
    if (FAILED(m_commandQueue->Signal(m_fence.Get(), currentFenceValue)))
    {
        throw std::runtime_error("Failed to Signal Fence.");
    }
    m_fenceValue++;

    if (m_fence->GetCompletedValue() < currentFenceValue)
    {
        if (FAILED(m_fence->SetEventOnCompletion(currentFenceValue, m_fenceEvent)))
        {
            throw std::runtime_error("Failed to Set Fence Event.");
        }
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }
}