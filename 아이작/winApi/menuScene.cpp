#include "stdafx.h"
#include "menuScene.h"

HRESULT menuScene::init(void)
{
	_image = IMAGEMANAGER->addImage("menu", "image/UI/menu.bmp", WINSIZEX, WINSIZEY);
	_title = IMAGEMANAGER->addImage("title", "image/UI/title.bmp", 912, 184, true, RGB(255, 0, 255));
	//메뉴
	_menu[0].img = IMAGEMANAGER->addImage("start", "image/UI/start.bmp", 186, 64, true, RGB(255, 0, 255));
	_menu[1].img = IMAGEMANAGER->addImage("tool", "image/UI/tool.bmp", 186, 64, true, RGB(255, 0, 255));
	_menu[2].img = IMAGEMANAGER->addImage("option", "image/UI/option.bmp", 186, 64, true, RGB(255, 0, 255));
	_menu[3].img = IMAGEMANAGER->addImage("close", "image/UI/close.bmp", 186, 64, true, RGB(255, 0, 255));
	for (int i = 0; i < 4; i++)
	{
		_menu[i].x = WINSIZEX / 2 + i * 10;
		_menu[i].y = WINSIZEY / 2 - 150 + i * 96;
		_menu[i].rc = RectMakeCenter(_menu[i].x, _menu[i].y, _menu[i].img->getWidth(), _menu[i].img->getHeight());
	}
	//화살표
	_arrow.img = IMAGEMANAGER->addImage("arrow", "image/UI/arrow.bmp", 24, 30, true, RGB(255, 0, 255));
	_arrow.x = _menu[0].rc.left - 20 - _arrow.img->getWidth();
	_arrow.y = _menu[0].y + _arrow.img->getHeight() / 2;
	_arrow.rc = RectMakeCenter(_arrow.x, _arrow.y, _arrow.img->getWidth(), _arrow.img->getHeight());
	_arrow.modeSelect = 0;
	addSound();

	SOUNDMANAGER->play("title screen", VOLUME->getMusicVolume() / 10);
	SOUNDMANAGER->stop("basic boss fight");
	return S_OK;
}

void menuScene::release(void)
{
}

void menuScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _arrow.modeSelect != 3)
	{
		_arrow.modeSelect++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _arrow.modeSelect != 0)
	{
		_arrow.modeSelect--;
	}
	modeSelect();
	_arrow.rc = RectMakeCenter(_arrow.x, _arrow.y, _arrow.img->getWidth(), _arrow.img->getHeight());
}

void menuScene::render(void)
{
	_image->render(getMemDC());
	_title->render(getMemDC(), WINSIZEX/2 - _title->getWidth() / 2, _menu[0].rc.top - 200);
	_arrow.img->render(getMemDC(), _arrow.rc.left, _arrow.rc.top);
	for (int i = 0; i < 4; i++)
	{
		_menu[i].img->render(getMemDC(), _menu[i].rc.left, _menu[i].rc.top);
	}
}

void menuScene::modeSelect(void)
{
	if (_arrow.modeSelect == 0)
	{
		_arrow.x = _menu[_arrow.modeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _menu[_arrow.modeSelect].y + _arrow.img->getHeight() / 2;
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// 씬 전환
			SOUNDMANAGER->stop("title screen");
			SOUNDMANAGER->play("title screen jingle", VOLUME->getMusicVolume() / 10);
			MoveWindow(_hWnd, WINSTARTX, WINSTARTY, CAMERAMANAGER->getGameMaxRenderX(), CAMERAMANAGER->getGameMaxRenderY(), true);
			SCENEMANAGER->changeScene("던전");
		}
	}
	else if (_arrow.modeSelect == 1)
	{
		_arrow.x = _menu[_arrow.modeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _menu[_arrow.modeSelect].y + _arrow.img->getHeight() / 2;
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			MoveWindow(_hWnd, WINSTARTX, WINSTARTY, WINSIZEX , WINSIZEY, true);
			SCENEMANAGER->changeScene("맵툴");
		}
	}
	else if (_arrow.modeSelect == 2)
	{
		_arrow.x = _menu[_arrow.modeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _menu[_arrow.modeSelect].y + _arrow.img->getHeight() / 2;
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// 씬 전환
			SCENEMANAGER->changeScene("옵션");
		}
	}
	else
	{
		_arrow.x = _menu[_arrow.modeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _menu[_arrow.modeSelect].y + _arrow.img->getHeight() / 2;
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//종료
			PostQuitMessage(0);
		}
	}
}
