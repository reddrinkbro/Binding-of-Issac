#include "stdafx.h"
#include "poop.h"

HRESULT basicPoop::init(float x, float y)
{
	_poop.img = IMAGEMANAGER->addFrameImage("poop1", "image/mapObject/poop1.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	_poop.x = x;
	_poop.y = y;
	_poop.rc = RectMakeCenter(_poop.x, _poop.y, _poop.img->getFrameWidth(), _poop.img->getFrameHeight());
	_poop.currentX = 0;
	return S_OK;
}

void basicPoop::release(void)
{
}

void basicPoop::update(void)
{
}

void basicPoop::render(void)
{
	_poop.img->frameRender(getMemDC(), _poop.rc.left - CAMERAMANAGER->getX(), _poop.rc.top - CAMERAMANAGER->getY(), _poop.currentX, 0);
}

void basicPoop::hit(void)
{
	_poop.currentX++;
}

HRESULT redPoop::init(float x, float y)
{
	_poop.img = IMAGEMANAGER->addFrameImage("poop2", "image/mapObject/poop2.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	_poop.x = x;
	_poop.y = y;
	_poop.rc = RectMakeCenter(_poop.x, _poop.y, _poop.img->getFrameWidth(), _poop.img->getFrameHeight());
	_poop.currentX = 0;
	return S_OK;
}

void redPoop::release(void)
{
}

void redPoop::update(void)
{
}

void redPoop::render(void)
{
	_poop.img->frameRender(getMemDC(), _poop.rc.left - CAMERAMANAGER->getX(), _poop.rc.top - CAMERAMANAGER->getY(), _poop.currentX, 0);
}

void redPoop::hit(void)
{
	_poop.currentX++;
}
