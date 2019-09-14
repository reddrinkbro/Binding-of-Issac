#include "stdafx.h"
#include "mainGame.h"

//=====================
//	## �������� ##
//=====================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

mainGame* _mg;

//======================
//	## �Լ� ���漱�� ##
//======================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//=======================
//	## ������ �����Լ� ##
//=======================
int APIENTRY WinMain(HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{

	_mg = new mainGame();

	//�ν��Ͻ��� ���������� ��Ƶд�
	_hInstance = hInstance;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü

	//������ ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���콺 Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������
	wndClass.hInstance = hInstance;									//�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ����ǥ X
		WINSTARTY,				//������ ȭ����ǥ Y
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//������ �� �ڽ� �����츦 �����ϸ� �������ְ� �׷��� ������ NULL
	);

	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�
	//setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);

	//���ΰ��� Ŭ������ �ʱ�ȭ ���н� ����
	if (FAILED(_mg->init()))
	{
		return 0;
	}
	
	//MSG : �ü������ �����ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;
	//�޼��� ����
	//GetMessage : �޼����� ������ �� ���������� �����ִ� �Լ�
	//PeekMessage : �޼����� ������ ���ϵǴ� �Լ�

	//���ӿ�	
	
	while (true) 
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}
	

	//TranslateMessage : Ű���� �Է¸޼��� ó���� ���
	//�Էµ� Ű�� ����Ű���� Ȯ���� �빮�� Ȥ�� �ҹ���, �ѱ�, ���������� ���� 
	//WM_CHAR �޼��� �߻���Ų��
	//DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �������ش�

	//�Ϲ� ���α׷��ֿ�
	/*while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}*/

	_mg->release();

	//������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//������ ���ν��� : �޼����� �ü���� �����ϰ� �ڵ��ϴ� ����
//hWnd : ��� �����쿡�� �߻��� �޼������� ����
//iMessage : �޼��� ���� ��ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� ����
//lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����(x, y)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//=================================================================
//	## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//=================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}