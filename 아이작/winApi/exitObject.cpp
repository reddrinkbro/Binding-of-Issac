#include "stdafx.h"
#include "exitObject.h"

HRESULT exitObject::init(float x, float y)
{
	_exit.img = IMAGEMANAGER->addFrameImage("exit", "image/mapObject/exit.bmp", 396, 128, 3, 1, true, RGB(255, 0, 255));
	_exit.x = x;
	_exit.y = y;
	_exit.rc = RectMakeCenter(_exit.x, _exit.y, _exit.img->getFrameWidth(), _exit.img->getFrameHeight());
	_exit.count = 0;
	_exit.currentX = 0;
	_exit.isOn = false;
	return S_OK;
}

void exitObject::release(void)
{
}

void exitObject::update(void)
{
	frame();
}

void exitObject::render(void)
{
	_exit.img->frameRender(getMemDC(), _exit.rc.left - CAMERAMANAGER->getX(), _exit.rc.top - CAMERAMANAGER->getY(), _exit.currentX, 0);
}

void exitObject::frame(void)
{
	if (_exit.count + FRAMECOUNT < TIMEMANAGER->getWorldTime() && !_exit.isOn)
	{
		_exit.count = TIMEMANAGER->getWorldTime();
		_exit.currentX++;
		if (_exit.currentX > _exit.img->getMaxFrameX())
		{
			_exit.currentX = 0;
			_exit.isOn = true;
		}
	}
}
