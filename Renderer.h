#pragma once


class Renderer
{
public:
    Renderer();
    ~Renderer();

    // DirectX 12 を初期化 (デバイスやスワップチェーンの準備)
    bool Initialize(HWND hWnd, int width, int height);

    // フレーム開始処理 (RenderTarget のリセットなど)
    void BeginFrame(float clearColor[4]);

    // フレーム終了処理 (スワップチェーンのフリップ等)
    void EndFrame();

private:
    // 初期化関連メソッド
    bool CreateDevice();
    bool CreateSwapChain(HWND hWnd, int width, int height);
    bool CreateCommandInterfaces();
    bool CreateRTVHeapAndBuffers(int width, int height);

    // DirectX 12 リソース
    Microsoft::WRL::ComPtr<ID3D12Device> m_device;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;

    // レンダーターゲットへの参照関連
    static const UINT FrameCount = 2;  // バッファ数 (ダブルバッファ)
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    UINT m_rtvDescriptorSize = 0;

    // シンクロ用
    UINT m_frameIndex = 0;
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue = 0;
    HANDLE m_fenceEvent = nullptr;

    // ヘルパー
    void WaitForGPU(); // コマンド実行完了を待機
};
