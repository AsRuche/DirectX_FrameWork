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

	//�E�B���h�E���j�������܂Ń��b�Z�[�W���[�v
	while (true)
	{
		//�E�B���h�E���b�Z�[�W�̏���
		if (!m_window.ProcessMessage())
		{
			//�E�B���h�E���j�����ꂽ��I��

			break;
		}
	}

	return true;
}