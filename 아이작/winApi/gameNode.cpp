#include "stdafx.h"
#include "gameNode.h"

//=========================
//	## �ʱ�ȭ ## init(void)
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
		//Ÿ�̸� �ʱ�ȭ
		SetTimer(_hWnd, 1, 10, NULL);
		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();
		//������� �ʱ�ȭ
		RND->init();
		//�̹��� �Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();
		//Ÿ�� �Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();
		//�ؽ�Ʈ������ �Ŵ��� �ʱ�ȭ
		TXTMANAGER->init();
		//INI������ �ʱ�ȭ
		INIDATA->init();
		//���� �ʱ�ȭ
		VOLUME->init();
		//�� �Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();
		//���� �Ŵ��� �ʱ�ȭ
		SOUNDMANAGER->init();
		//����Ʈ �Ŵ��� �ʱ�ȭ
		EFFECTMANAGER->init();
		//ī�޶� �Ŵ��� �ʱ�ȭ
		CAMERAMANAGER->init();
		
	}

	return S_OK;
}

//==============================
//	## ���� ## release(void)
//==============================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		//������� �̱��� ����
		RND->releaseSingleton();

		//�̹��� �Ŵ��� ����, �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//Ÿ�� �Ŵ��� ����, �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//�ؽ�Ʈ������ �Ŵ��� ����, �̱��� ����
		TXTMANAGER->release();
		TXTMANAGER->releaseSingleton();

		//INI������ ����, �̱��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();

		//�� �Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		//���� �Ŵ��� ����, �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		//����Ʈ �Ŵ��� ����, �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//ī�޶� �Ŵ��� ����, �̱��� ����
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		//���� ����
		VOLUME->release();
		VOLUME->releaseSingleton();

		addSound();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================
//	## ������Ʈ ## update(void)
//=============================
void gameNode::update(void)
{
	//���ΰ�ħ (���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´� (true => false)
	
	//InvalidateRect(_hWnd, NULL, FALSE);
	
}

//============================
//	## ���� ## render(HDC hdc)
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
//	## �������ν��� ## MainProc
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