#include "Application.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application::GetInstance().AppRun();

	return 0;
}

bool Application::AppRun()
{
	//�E�B���h�E�̍쐬
	if (!m_window.Create(1280, 720,L"DirectXFramework",L"WindowClass"))
	{
		return false;
	}

	// Renderer ������
	HWND hWnd = m_window.GetHwnd(); // (Window �N���X�� GetHwnd() �̂悤�Ȏ擾�֐���p��)
	if (!m_renderer.Initialize(hWnd, 1280, 720))
	{
		return false;
	}

	//�E�B���h�E���j�������܂Ń��b�Z�[�W���[�v
	while (true)
	{
		//�E�B���h�E���b�Z�[�W�̏���
		if (!m_window.ProcessMessage())
		{
			//�E�B���h�E���j�����ꂽ��I��

			break;
		}

		// �`�揈��
		float clearColor[4] = { 0.2f, 0.4f, 0.6f, 1.0f }; // RGBA
		m_renderer.BeginFrame(clearColor);
		// �����Ń��f���`���X�v���C�g�`������Ă���
		m_renderer.EndFrame();
	}

	return true;
}