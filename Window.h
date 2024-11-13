#pragma once

class Window
{
public:
	/// <summary>
	/// �E�B���h�E�̍쐬
	/// </summary>
	/// <param name="clientWidth">�E�B���h�E�̃N���C�A���g�̈�̕�</param>
	/// <param name="clientHeight">�E�B���h�E�̃N���C�A���g�̈�̍���</param>
	/// <param name="titleName">�E�B���h�E�̃^�C�g����</param>
	/// <param name="windowClassName">�E�B���h�E�N���X��</param>
	/// <returns>�E�B���h�E�̍쐬�ɐ���������true��Ԃ�</returns>
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName,const std::wstring& windowClassName);

	/// <summary>
	/// �E�B���h�E���b�Z�[�W�̏���
	/// </summary>
	/// <returns>�E�B���h�E���j�����ꂽ��false��Ԃ�</returns>
	bool ProcessMessage();
private:
	HWND m_hWnd;
};

