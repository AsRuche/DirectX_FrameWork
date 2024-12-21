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

	// Renderer 初期化
	HWND hWnd = m_window.GetHwnd(); // (Window クラスに GetHwnd() のような取得関数を用意)
	if (!m_renderer.Initialize(hWnd, 1280, 720))
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

		// 描画処理
		float clearColor[4] = { 0.2f, 0.4f, 0.6f, 1.0f }; // RGBA
		m_renderer.BeginFrame(clearColor);
		// ここでモデル描画やスプライト描画を入れていく
		m_renderer.EndFrame();
	}

	return true;
}