#include "stdafx.h"
#include "pentagram.h"

HRESULT pentagram::init(float x, float y)
{
	_penta._image = IMAGEMANAGER->addImage("pentagram", "image/item/pentagram.bmp", 40, 40, true, RGB(255, 0, 255));
	_penta.x = x;
	_penta.y = y;
	_penta.isUp = false;
	_penta.distance = 50;
	_penta.isMove = true;
	return S_OK;
}

void pentagram::release(void)
{
}

void pentagram::update(void)
{
	if(_penta.isMove) move();
}

void pentagram::render(void)
{
	draw();
}

void pentagram::draw(void)
{
	_penta._image->render(getMemDC(), _penta.x - CAMERAMANAGER->getX(), _penta.y - CAMERAMANAGER->getY());
}

void pentagram::move(void)
{
	if(_penta.isUp)
	{
		_penta.y -=0.2f;
	}
	else
	{
		_penta.y+= 0.2f;
	}
	_penta.distance--;
	if (_penta.distance < 0)
	{
		if (_penta.isUp) _penta.isUp = false;
		else _penta.isUp = true;
		_penta.distance = 50;
	}
}

void pentagram::gainPentagram(float x, float y)
{
	_penta.x = x;
	_penta.y = y;
}
