#pragma once
#include"Window.h"

class Application
{
public:
	/// <summary>
	///アプリケーションの実行
	/// </summary>
	bool AppRun();
private:
	Window m_window;	//ウィンドウクラスのインスタンス
	Application() {}	//コンストラクタ
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}
};

