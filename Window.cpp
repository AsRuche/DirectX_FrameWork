#include "Window.h"


// �E�B���h�E�v���V�[�W��(�E�B���h�E���b�Z�[�W�̏������s���֐�)
LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		//�E�B���h�E���j�����ꂽ�Ƃ��A���b�Z�[�W�L���[��WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	default:
		//�f�t�H���g�̏������s��
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// �E�B���h�E�̍쐬�F�����i�E�B���h�E�̃N���C�A���g�̈�̕��A�E�B���h�E�̃N���C�A���g�̈�̍����A�E�B���h�E�̃^�C�g�����A�E�B���h�E�N���X���j
bool Window::Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName)
{
	// �C���X�^���X�n���h���̎擾
	HINSTANCE hInstance = GetModuleHandle(0);


	//=========================================================
	// ���C���E�B���h�E�쐬
	//=========================================================

	//�E�B���h�E�N���X�̓o�^�i�E�B���h�E�̌����ڂ⋓�������肷��j
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);				//�\���̂̃T�C�Y
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;	//�E�B���h�E�v���V�[�W��
	wc.lpszClassName = windowClassName.c_str();	//�E�B���h�E�N���X��
	wc.hInstance = hInstance;					//�C���X�^���X�n���h��

	//�E�B���h�E�N���X�̓o�^
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	//�E�B���h�E�̍쐬
	m_hWnd = CreateWindow(
		windowClassName.c_str(),	//�E�B���h�E�N���X��
		titleName.c_str(),			//�E�B���h�E�̃^�C�g����
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,		//�E�B���h�E�X�^�C���i�^�C�g���o�[�A���E���A�ő剻�A�ŏ����A����{�^�������E�B���h�E�j
		CW_USEDEFAULT,				//�E�B���h�E��X���W�iOS�ɔC����j
		CW_USEDEFAULT,				//�E�B���h�E��Y���W�iOS�ɔC����j
		clientWidth,				//�E�B���h�E�̕�
		clientHeight,				//�E�B���h�E�̍���
		nullptr,					//�e�E�B���h�E�̃n���h��
		nullptr,					//���j���[�n���h��
		hInstance,					//�C���X�^���X�n���h���i���̃E�B���h�E�����L����C���X�^���X�j
		nullptr						//�ǉ��p�����[�^
	);

	if (!m_hWnd)
	{
		return false;
	}

	//�E�B���h�E��\��
	ShowWindow(m_hWnd, SW_SHOW);

	//�E�B���h�E���X�V
	UpdateWindow(m_hWnd);

	return true;
}

bool Window::ProcessMessage()
{
	//���b�Z�[�W�\����
	MSG msg = {};//������

	//���b�Z�[�W��������胋�[�v
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���b�Z�[�W������
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//WM_QUIT���b�Z�[�W�������false��Ԃ�
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}

	return true;
}

