#include "stdafx.h"
#include "ouijaboard.h"

HRESULT ouijaboard::init(float x, float y)
{
	_ouijaboard._image = IMAGEMANAGER->addImage("ouijaboard", "image/item/ouijaboard.bmp", 40, 40, true, RGB(255, 0, 255));
	_ouijaboard.x = x;
	_ouijaboard.y = y;
	_ouijaboard.isUp = false;
	_ouijaboard.distance = 50;
	_ouijaboard.isMove = true;

	return S_OK;
}

void ouijaboard::release(void)
{
}

void ouijaboard::update(void)
{
	if (_ouijaboard.isMove) move();
}

void ouijaboard::render(void)
{
	draw();
}

void ouijaboard::draw(void)
{
	_ouijaboard._image->render(getMemDC(), _ouijaboard.x - CAMERAMANAGER->getX(), _ouijaboard.y - CAMERAMANAGER->getY());
}

void ouijaboard::move(void)
{
	if (_ouijaboard.isUp)
	{
		_ouijaboard.y -= 0.2f;
	}
	else
	{
		_ouijaboard.y += 0.2f;
	}
	_ouijaboard.distance--;
	if (_ouijaboard.distance < 0)
	{
		if (_ouijaboard.isUp) _ouijaboard.isUp = false;
		else _ouijaboard.isUp = true;
		_ouijaboard.distance = 50;
	}
}

void ouijaboard::gainOuijaboard(float x, float y)
{
	_ouijaboard.x = x;
	_ouijaboard.y = y;
}
