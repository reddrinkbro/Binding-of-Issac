// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKver.h>

//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN
// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>

using namespace std;

//GDI+
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;
//======================================
//	## ���� ���� ��������� �̰��� �߰� ##
//======================================
#include "commonMacroFiunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "cameraManager.h"
#include "soundVolume.h"
using namespace MY_UTIL;

//================================
//	## �̱����� �̰��� �߰��Ѵ� ##
//================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTMANAGER txtDataManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define VOLUME soundVolume::getSingleton()

//================================
//	## ��ũ�� ## (������â �ʱ�ȭ)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		330
#define WINSTARTY		10
//����ȭ�� + ����� + ������ Ÿ���̹���
#define WINSIZEX		/*992*/ 1300
#define WINSIZEY		/*672*/900
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## ��ũ�� �Լ� ## (Ŭ�������� �����Ҵ�� �κ� ����)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## �������� ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern int			_modeSelect;
//=================================================
//	## ���� Ÿ�� ���� ## 
//=================================================
#define TILESIZE 64						//������ ȭ�� Ÿ�� ������
#define TILEX 75						//����ȭ�� Ÿ�� ������ X
#define TILEY 75						//����ȭ�� Ÿ�� ������ Y
#define MAPTILESIZEX TILEX * TILESIZE
#define MAPTILESIZEY TILEY * TILESIZE

//ȭ�� ������ �� Ÿ�� ����
#define SAMPLETILEX 9
#define SAMPLETILEY 7

//ȭ�� ������ ���ӽ� Ÿ�� ����
#define PROPSTILEX 9
#define PROPSTILEY 6

//ȭ�� ������ ������Ʈ ����
#define OBJECTTILEX 8
#define OBJECTTILEY 5

//ȭ�� ������ �����ӿ�����Ʈ ����
#define FRAMEOBJECTTILEX 4
#define FRAMEOBJECTTILEY 2

//ȭ�� ������ �� ������Ʈ ����
#define DOORTILEX 5
#define DOORTILEY 4

//ȭ�� ������ ���� ������Ʈ ����
#define MONSTEROBJECTTILEX 4
#define MONSTEROBJECTTILEY 3

//ȭ�� ������ ������ ������Ʈ ����
#define ITEMOBJECTTILEX 4
#define ITEMOBJECTTILEY 3

//=================================================
//	## ������ �ӵ� ���� ## 
//=================================================
#define FRAMECOUNT 0.1f

