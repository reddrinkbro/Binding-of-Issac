#include "stdafx.h"
#include "ghostBaby.h"


HRESULT ghostBaby::init(float x, float y)
{
	_ghost.img = IMAGEMANAGER->addImage("ghostbaby", "image/item/ghostbaby.bmp", 40, 40, true, RGB(255, 0, 255));
	_ghost.x = x;
	_ghost.y = y;
	_ghost.isUp = false;
	_ghost.distance = 50;
	_ghost.isMove = true;
	return S_OK;
}

void ghostBaby::release(void)
{
}

void ghostBaby::update(void)
{
	if (_ghost.isMove) move();
}

void ghostBaby::render(void)
{
	draw();
}

void ghostBaby::draw(void)
{
	_ghost.img->render(getMemDC(), _ghost.x - CAMERAMANAGER->getX(), _ghost.y - CAMERAMANAGER->getY());
}

void ghostBaby::move(void)
{
	if (_ghost.isUp)
	{
		_ghost.y -= 0.2f;
	}
	else
	{
		_ghost.y += 0.2f;
	}
	_ghost.distance--;
	if (_ghost.distance < 0)
	{
		if (_ghost.isUp) _ghost.isUp = false;
		else _ghost.isUp = true;
		_ghost.distance = 50;
	}
}

void ghostBaby::gainGhostBaby(float x, float y)
{
	_ghost.x = x;
	_ghost.y = y;
}
