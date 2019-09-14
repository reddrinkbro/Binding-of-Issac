// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKver.h>

//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN
// Windows 헤더 파일:
#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더 파일입니다.
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
//	## 내가 만든 헤더파일을 이곳에 추가 ##
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
//	## 싱글톤을 이곳에 추가한다 ##
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
//	## 매크로 ## (윈도우창 초기화)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		330
#define WINSTARTY		10
//왼쪽화면 + 빈공간 + 오른쪽 타일이미지
#define WINSIZEX		/*992*/ 1300
#define WINSIZEY		/*672*/900
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## 매크로 함수 ## (클래스에서 동적할당된 부분 해제)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## 전역변수 ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern int			_modeSelect;
//=================================================
//	## 맵툴 타일 설정 ## 
//=================================================
#define TILESIZE 64						//오른쪽 화면 타일 사이즈
#define TILEX 75						//왼쪽화면 타일 사이즈 X
#define TILEY 75						//왼쪽화면 타일 사이즈 Y
#define MAPTILESIZEX TILEX * TILESIZE
#define MAPTILESIZEY TILEY * TILESIZE

//화면 오른쪽 맵 타일 갯수
#define SAMPLETILEX 9
#define SAMPLETILEY 7

//화면 오른쪽 프롭스 타일 갯수
#define PROPSTILEX 9
#define PROPSTILEY 6

//화면 오른쪽 오브젝트 갯수
#define OBJECTTILEX 8
#define OBJECTTILEY 5

//화면 오른쪽 프레임오브젝트 갯수
#define FRAMEOBJECTTILEX 4
#define FRAMEOBJECTTILEY 2

//화면 오른쪽 문 오브젝트 갯수
#define DOORTILEX 5
#define DOORTILEY 4

//화면 오른쪽 몬스터 오브젝트 갯수
#define MONSTEROBJECTTILEX 4
#define MONSTEROBJECTTILEY 3

//화면 오른쪽 아이템 오브젝트 갯수
#define ITEMOBJECTTILEX 4
#define ITEMOBJECTTILEY 3

//=================================================
//	## 프레임 속도 설정 ## 
//=================================================
#define FRAMECOUNT 0.1f

