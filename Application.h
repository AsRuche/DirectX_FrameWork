#pragma once
#include"Window.h"

class Application
{
public:
	/// <summary>
	///�A�v���P�[�V�����̎��s
	/// </summary>
	bool AppRun();
private:
	Window m_window;	//�E�B���h�E�N���X�̃C���X�^���X
	Application() {}	//�R���X�g���N�^
public:
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}
};

