#include "Window.h"


// ウィンドウプロシージャ(ウィンドウメッセージの処理を行う関数)
LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		//ウィンドウが破棄されたとき、メッセージキューにWM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	default:
		//デフォルトの処理を行う
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// ウィンドウの作成：引数（ウィンドウのクライアント領域の幅、ウィンドウのクライアント領域の高さ、ウィンドウのタイトル名、ウィンドウクラス名）
bool Window::Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName)
{
	// インスタンスハンドルの取得
	HINSTANCE hInstance = GetModuleHandle(0);


	//=========================================================
	// メインウィンドウ作成
	//=========================================================

	//ウィンドウクラスの登録（ウィンドウの見た目や挙動を決定する）
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);				//構造体のサイズ
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;	//ウィンドウプロシージャ
	wc.lpszClassName = windowClassName.c_str();	//ウィンドウクラス名
	wc.hInstance = hInstance;					//インスタンスハンドル

	//ウィンドウクラスの登録
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	//ウィンドウの作成
	m_hWnd = CreateWindow(
		windowClassName.c_str(),	//ウィンドウクラス名
		titleName.c_str(),			//ウィンドウのタイトル名
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,		//ウィンドウスタイル（タイトルバー、境界線、最大化、最小化、閉じるボタンを持つウィンドウ）
		CW_USEDEFAULT,				//ウィンドウのX座標（OSに任せる）
		CW_USEDEFAULT,				//ウィンドウのY座標（OSに任せる）
		clientWidth,				//ウィンドウの幅
		clientHeight,				//ウィンドウの高さ
		nullptr,					//親ウィンドウのハンドル
		nullptr,					//メニューハンドル
		hInstance,					//インスタンスハンドル（このウィンドウを所有するインスタンス）
		nullptr						//追加パラメータ
	);

	if (!m_hWnd)
	{
		return false;
	}

	//ウィンドウを表示
	ShowWindow(m_hWnd, SW_SHOW);

	//ウィンドウを更新
	UpdateWindow(m_hWnd);

	return true;
}

bool Window::ProcessMessage()
{
	//メッセージ構造体
	MSG msg = {};//初期化

	//メッセージがある限りループ
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//メッセージを処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//WM_QUITメッセージがあればfalseを返す
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}

	return true;
}

