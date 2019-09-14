#include "stdafx.h"
#include "treasureChest.h"

HRESULT treasureChest::init(float x, float y)
{
	_chest.img = IMAGEMANAGER->addFrameImage("treasureChest", "image/mapObject/treasureChest.bmp", 600, 180, 6, 2, true, RGB(255, 0, 255));
	_chest.x = x;
	_chest.y = y;
	_chest.rc = RectMakeCenter(_chest.x, _chest.y, _chest.img->getFrameWidth(), _chest.img->getFrameHeight());
	_chest.count = 0;
	_chest.currentX = 0;
	_chest.currentY = 0;
	_chest.state = CHESTSTATE_CLOSE;
	_time = 80;
	return S_OK;
}

void treasureChest::release(void)
{
}

void treasureChest::update(void)
{
	frame();
}

void treasureChest::render(void)
{
	draw();
}

void treasureChest::draw(void)
{
	if(_time>=0) _chest.img->frameRender(getMemDC(), _chest.rc.left - CAMERAMANAGER->getX(), _chest.rc.top - CAMERAMANAGER->getY(), _chest.currentX, _chest.currentY);
}

void treasureChest::frame(void)
{
	if (_chest.state == CHESTSTATE_CLOSE)
	{
		_chest.currentY = 0;
		if (_chest.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_chest.count = TIMEMANAGER->getWorldTime();
			_chest.currentX++;
			if (_chest.currentX > _chest.img->getMaxFrameX())
			{
				_chest.currentX = _chest.img->getMaxFrameX();
			}
		}
	}
	else
	{
		_time--;
		if (_chest.currentX == _chest.img->getMaxFrameX())
		{
			_chest.currentX = 0;
		}
		_chest.currentY = 1;
		if (_chest.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_chest.count = TIMEMANAGER->getWorldTime();
			_chest.currentX++;
			if (_chest.currentX > 2)
			{
				_chest.currentX = 2;
			}
		}
	}
}
