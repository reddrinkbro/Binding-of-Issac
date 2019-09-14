#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## 초기화 ## init(void)
//=========================
HRESULT gameNode::init(void)
{	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	if (managerInit)
	{
		//타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);
		//키매니져 초기화
		KEYMANAGER->init();
		//랜덤펑션 초기화
		RND->init();
		//이미지 매니져 초기화
		IMAGEMANAGER->init();
		//타임 매니져 초기화
		TIMEMANAGER->init();
		//텍스트데이터 매니져 초기화
		TXTMANAGER->init();
		//INI데이터 초기화
		INIDATA->init();
		//볼륨 초기화
		VOLUME->init();
		//씬 매니져 초기화
		SCENEMANAGER->init();
		//사운드 매니져 초기화
		SOUNDMANAGER->init();
		//이펙트 매니져 초기화
		EFFECTMANAGER->init();
		//카메라 매니져 초기화
		CAMERAMANAGER->init();
		
	}

	return S_OK;
}

//==============================
//	## 해제 ## release(void)
//==============================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니져 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		//랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		//이미지 매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//타임 매니져 해제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//텍스트데이터 매니져 해제, 싱글톤 해제
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		//INI데이터 해제, 싱글톤 해제
		INIDATA->release();
		INIDATA->releaseSingleton();

		//씬 매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		//사운드 매니져 해제, 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		//이펙트 매니져 해제, 싱글톤 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//카메라 매니저 해제, 싱글톤 해제
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		//볼륨 해제
		VOLUME->release();
		VOLUME->releaseSingleton();

		addSound();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================
//	## 업데이트 ## update(void)
//=============================
void gameNode::update(void)
{
	//새로고침 (고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	
	//InvalidateRect(_hWnd, NULL, FALSE);
	
}

//============================
//	## 렌더 ## render(HDC hdc)
//============================
void gameNode::render(void)
{
}

void gameNode::tileDraw(void)
{
}
void gameNode::addSound(void)
{
	SOUNDMANAGER->addSound("title screen", "sound/music/title screen.mp3", true, true);
	SOUNDMANAGER->addSound("title screen jingle", "sound/music/title screen jingle.mp3", true, false);
	SOUNDMANAGER->addSound("basement", "sound/music/basement.mp3", true, true);
	SOUNDMANAGER->addSound("boss fight intro jingle", "sound/music/boss fight intro jingle.mp3", true, false);
	SOUNDMANAGER->addSound("basic boss fight", "sound/music/basic boss fight.mp3", true, true);
	SOUNDMANAGER->addSound("tear fire", "sound/sfx/tear fire.mp3", false, false);
	SOUNDMANAGER->addSound("bomb", "sound/sfx/bomb.mp3", false, false);
	SOUNDMANAGER->addSound("chest drop 1", "sound/sfx/chest drop 1.mp3", false, false);
	SOUNDMANAGER->addSound("chest open", "sound/sfx/chest open.mp3", false, false);
	SOUNDMANAGER->addSound("coin pickup", "sound/sfx/coin pickup.mp3", false, false);
	SOUNDMANAGER->addSound("hp up", "sound/sfx/hp up.mp3", false, false);
	SOUNDMANAGER->addSound("isaac hit", "sound/sfx/isaac hit.mp3", false, false);
	SOUNDMANAGER->addSound("key drop", "sound/sfx/key drop.mp3", false, false);
	SOUNDMANAGER->addSound("key pickup", "sound/sfx/key pickup.mp3", false, false);
	SOUNDMANAGER->addSound("monster die", "sound/sfx/monster die.mp3", false, false);
	SOUNDMANAGER->addSound("monstro fire", "sound/sfx/monstro fire.mp3", false, false);
	SOUNDMANAGER->addSound("monstro jump", "sound/sfx/monstro jump.mp3", false, false);
	SOUNDMANAGER->addSound("power up1", "sound/sfx/power up1.mp3", false, false);
	SOUNDMANAGER->addSound("summonsound", "sound/sfx/summonsound.mp3", false, false);
	SOUNDMANAGER->addSound("thumbs down", "sound/sfx/thumbs down.mp3", false, false);
	SOUNDMANAGER->addSound("bomb pickup", "sound/sfx/bomb pickup.mp3", false, false);
	SOUNDMANAGER->addSound("isaac dies", "sound/sfx/isaac dies.mp3", false, false);
	SOUNDMANAGER->addSound("duke spawn one", "sound/sfx/duke spawn one.mp3", false, false);
	SOUNDMANAGER->addSound("duke spawn two", "sound/sfx/duke spawn two.mp3", false, false);
	SOUNDMANAGER->addSound("boss die", "sound/sfx/boss die.mp3", false, false);
	SOUNDMANAGER->addSound("zombie walker kid", "sound/sfx/zombie walker kid.mp3", false, false);
	SOUNDMANAGER->addSound("castleportcullis", "sound/sfx/castleportcullis.mp3", false, false);
	SOUNDMANAGER->addSound("megamaw fire1", "sound/sfx/megamaw fire1.mp3", false, false);
	SOUNDMANAGER->addSound("megamaw fire2", "sound/sfx/megamaw fire2.mp3", false, false);
}
//============================
//	## 메인프로시져 ## MainProc
//============================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		this->tileDraw();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}