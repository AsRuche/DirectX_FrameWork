#include "Renderer.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    // GPU ���̏���������҂��Ă���I��
    WaitForGPU();

    if (m_fenceEvent)
    {
        CloseHandle(m_fenceEvent);
        m_fenceEvent = nullptr;
    }
}

// DirectX 12 �������� (�f�o�C�X��X���b�v�`�F�[���̏���)
bool Renderer::Initialize(HWND hWnd, int width, int height)
{
	// �f�o�C�X�쐬�Ȃǂ̏������������܂Ƃ߂čs��
	if (!CreateDevice()) { return false; }                          // �f�o�C�X�쐬�iDirect3D 12 �̏������j
	if (!CreateSwapChain(hWnd, width, height)) { return false; }	// �X���b�v�`�F�[���쐬�i�o�b�N�o�b�t�@�̊Ǘ��Ȃǁj
	if (!CreateCommandInterfaces()) { return false; }			    // �R�}���h�C���^�[�t�F�[�X�쐬�iGPU�ɑ΂��ăR�}���h�𑗂邽�߂̃C���^�[�t�F�[�X�j
	if (!CreateRTVHeapAndBuffers(width, height)) { return false; }  // RTV �q�[�v�ƃo�b�t�@�쐬�iRTV�̓����_�����O���ʂ��i�[����ׂ̃o�b�t�@�ŁA�w�肳�ꂽ���ƍ����̃o�b�t�@���쐬�j

    // �t���[���C���f�b�N�X�擾
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();        // �o�b�N�o�b�t�@�̃C���f�b�N�X���擾�i�X���b�v�`�F�[���̃o�b�N�o�b�t�@�̃C���f�b�N�X���擾�j

    // �t�F���X�쐬 & �C�x���g�쐬
	if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))    // �t�F���X�Ƃ́AGPU�̏�������������܂őҋ@���邽�߂̎d�g��
    {
		// �t�F���X�쐬���s
        return false;
    }
	m_fenceValue = 1;// �t�F���X�̏����l��1�ɐݒ�

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);                             // ���̃C�x���g�́AGPU�̏�������������܂őҋ@���邽�߂̃C�x���g
    if (!m_fenceEvent)
    {
        return false;
    }

    return true;
}

void Renderer::BeginFrame(float clearColor[4])
{
    // �R�}���h�A���P�[�^�����Z�b�g
    m_commandAllocator->Reset();
    // �R�}���h���X�g�����Z�b�g
    m_commandList->Reset(m_commandAllocator.Get(), nullptr);

    // ���݂̃o�b�N�o�b�t�@���\�[�X���擾
    auto backBuffer = m_renderTargets[m_frameIndex].Get();

    // ���\�[�X�o���A (�o�͍����p�Ƀg�����W�V����)
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = backBuffer;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &barrier);

    // RTV (�����_�[�^�[�Q�b�g�r���[) ���擾
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        m_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
        m_frameIndex,
        m_rtvDescriptorSize
    );

    // RenderTarget ���N���A
    m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
    m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

void Renderer::EndFrame()
{
    // �o�b�N�o�b�t�@�� Present ��ԂɈڍs
    auto backBuffer = m_renderTargets[m_frameIndex].Get();
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = backBuffer;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &barrier);

    // �R�}���h���X�g�����
    m_commandList->Close();

    // �R�}���h���X�g�����s
    ID3D12CommandList* cmdLists[] = { m_commandList.Get() };
    m_commandQueue->ExecuteCommandLists(1, cmdLists);

    // Present (�_�u���o�b�t�@)
    m_swapChain->Present(1, 0);

    // ���t���[���ɔ����� GPU ���������
    WaitForGPU();

    // �o�b�N�o�b�t�@�C���f�b�N�X���X�V
    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

bool Renderer::CreateDevice()
{
#if defined(_DEBUG)
    // �f�o�b�O���C���[��L���� (Debug ���[�h��)
    {
        Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
    }
#endif

// DXGI �t�@�N�g������
Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
{
    return false;
}

// �A�_�v�^�� (����͍ŏ��Ɍ������� HW �A�_�v�^���g���Ȉ՗�)
Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
for (UINT i = 0; ; i++)
{
    if (factory->EnumAdapters1(i, &adapter) == DXGI_ERROR_NOT_FOUND)
    {
        break;
    }
    DXGI_ADAPTER_DESC1 desc;
    adapter->GetDesc1(&desc);

    // �\�t�g�E�F�A�A�_�v�^�͉��
    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
    {
        continue;
    }
    // �f�o�C�X�쐬������
    if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
    {
        break;
    }
}

// �����A�_�v�^�擾�Ɏ��s�����ꍇ�� WARP ���g����
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
    // �R�}���h�L���[�� SwapChain �O�ɕK�v�Ȃ̂ňꎞ�I�ɍ쐬���Ă���
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue))))
    {
        return false;
    }

    // DXGI �t�@�N�g���Đ���
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
    // �R�}���h�A���P�[�^�쐬
    if (FAILED(m_device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_commandAllocator))))
    {
        return false;
    }

    // �R�}���h���X�g�쐬
    if (FAILED(m_device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_commandAllocator.Get(),
        nullptr, // PSO �͂܂��ݒ肵�Ȃ�
        IID_PPV_ARGS(&m_commandList))))
    {
        return false;
    }

    // �R�}���h���X�g�͍ŏ��J������ԁB�����Ă���
    m_commandList->Close();

    return true;
}

bool Renderer::CreateRTVHeapAndBuffers(int width, int height)
{
    // RTV �p�f�B�X�N���v�^�q�[�v
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FrameCount;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap))))
    {
        return false;
    }

    m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // �o�b�N�o�b�t�@�̃��\�[�X���擾���� RTV �����
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

        // RTV ���쐬
        m_device->CreateRenderTargetView(m_renderTargets[i].Get(), nullptr, handle);
    }

    return true;
}

void Renderer::WaitForGPU()
{
    // �R�}���h�̊������t�F���X�őҋ@
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