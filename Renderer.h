#pragma once


class Renderer
{
public:
    Renderer();
    ~Renderer();

    // DirectX 12 �������� (�f�o�C�X��X���b�v�`�F�[���̏���)
    bool Initialize(HWND hWnd, int width, int height);

    // �t���[���J�n���� (RenderTarget �̃��Z�b�g�Ȃ�)
    void BeginFrame(float clearColor[4]);

    // �t���[���I������ (�X���b�v�`�F�[���̃t���b�v��)
    void EndFrame();

private:
    // �������֘A���\�b�h
    bool CreateDevice();
    bool CreateSwapChain(HWND hWnd, int width, int height);
    bool CreateCommandInterfaces();
    bool CreateRTVHeapAndBuffers(int width, int height);

    // DirectX 12 ���\�[�X
    Microsoft::WRL::ComPtr<ID3D12Device> m_device;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;

    // �����_�[�^�[�Q�b�g�ւ̎Q�Ɗ֘A
    static const UINT FrameCount = 2;  // �o�b�t�@�� (�_�u���o�b�t�@)
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    UINT m_rtvDescriptorSize = 0;

    // �V���N���p
    UINT m_frameIndex = 0;
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue = 0;
    HANDLE m_fenceEvent = nullptr;

    // �w���p�[
    void WaitForGPU(); // �R�}���h���s������ҋ@
};
