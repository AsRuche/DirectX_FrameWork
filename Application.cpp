#include "Application.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application::GetInstance().AppRun();

	return 0;
}

bool Application::AppRun()
{
	//ウィンドウの作成
	if (!m_window.Create(1280, 720,L"DirectXFramework",L"WindowClass"))
	{
		return false;
	}

	//ウィンドウが破棄されるまでメッセージループ
	while (true)
	{
		//ウィンドウメッセージの処理
		if (!m_window.ProcessMessage())
		{
			//ウィンドウが破棄されたら終了

			break;
		}
	}

	return true;
}