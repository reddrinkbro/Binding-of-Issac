#include "stdafx.h"
#include "door.h"

HRESULT door::init(float x, float y, int select, DOOROBJECT state, bool isOpen)
{
	if (select == 0) _door.img = IMAGEMANAGER->addFrameImage("basementDoor", "image/mapObject/basementDoor.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
	else if (select == 1) _door.img = IMAGEMANAGER->addFrameImage("depthsDoor", "image/mapObject/depthsDoor.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
	else if (select == 2) _door.img = IMAGEMANAGER->addFrameImage("diceroomDoor", "image/mapObject/diceroomDoor.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
	else if (select == 3) _door.img = IMAGEMANAGER->addFrameImage("shopDoor", "image/mapObject/shopDoor.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
	else _door.img = IMAGEMANAGER->addFrameImage("bossDoor", "image/mapObject/bossDoor.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
	_door.x = x;
	_door.y = y;
	_door.count = 0;
	if(isOpen) _door.currentX = _door.img->getMaxFrameX();
	else _door.currentX = 0;
	if (state == DOOR_UP || state == SHOP_DOOR_UP || state == BOSS_DOOR_UP) _door.currentY = 0;
	else if (state == DOOR_RIGHT || state == SHOP_DOOR_RIGHT || state == BOSS_DOOR_RIGHT)  _door.currentY = 1;
	else if (state == DOOR_DOWN || state == SHOP_DOOR_DOWN || state == BOSS_DOOR_DOWN)  _door.currentY = 2;
	else if (state == DOOR_LEFT || state == SHOP_DOOR_LEFT || state == BOSS_DOOR_LEFT)  _door.currentY = 3;

	return S_OK;
}

void door::release(void)
{
}

void door::update(bool isOpen)
{
	if (isOpen)
	{
		if (_door.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_door.count = TIMEMANAGER->getWorldTime();
			_door.currentX++;
			if (_door.currentX > _door.img->getMaxFrameX())
			{
				_door.currentX = _door.img->getMaxFrameX();
			}
		}
	}
	else
	{
		if (_door.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_door.count = TIMEMANAGER->getWorldTime();
			_door.currentX--;
			if (_door.currentX < 0 )
			{
				_door.currentX = 0;
			}
		}
	}
}

void door::render(void)
{
	_door.img->frameRender(getMemDC(), _door.x - CAMERAMANAGER->getX(), _door.y - CAMERAMANAGER->getY(), _door.currentX, _door.currentY);
}

