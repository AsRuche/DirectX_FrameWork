#pragma once

class Window
{
public:
	/// <summary>
	/// ウィンドウの作成
	/// </summary>
	/// <param name="clientWidth">ウィンドウのクライアント領域の幅</param>
	/// <param name="clientHeight">ウィンドウのクライアント領域の高さ</param>
	/// <param name="titleName">ウィンドウのタイトル名</param>
	/// <param name="windowClassName">ウィンドウクラス名</param>
	/// <returns>ウィンドウの作成に成功したらtrueを返す</returns>
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName,const std::wstring& windowClassName);

	/// <summary>
	/// ウィンドウメッセージの処理
	/// </summary>
	/// <returns>ウィンドウが破棄されたらfalseを返す</returns>
	bool ProcessMessage();
private:
	HWND m_hWnd;
};

