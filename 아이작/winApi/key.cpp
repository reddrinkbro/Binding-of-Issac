#include "stdafx.h"
#include "key.h"

HRESULT key::init(float x, float y)
{
	_key.img = IMAGEMANAGER->addImage("key", "image/item/key.bmp", 28, 40, true, RGB(255, 0, 255));
	_key.x = x;
	_key.y = y;
	_key.rc = RectMakeCenter(_key.x, _key.y, _key.img->getWidth(), _key.img->getHeight());
	_key.isMove = true;
	_key.speed = 0.0f;
	_key.distance = 100;

	_gravity = -2.0f;
	_currnetAnlgeValue = PI / 2;

	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void key::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void key::update(void)
{
	if (_key.isMove) move();
}

void key::render(void)
{
	_shadow->render();
	_key.img->render(getMemDC(), _key.rc.left - CAMERAMANAGER->getX(), _key.rc.top - CAMERAMANAGER->getY());
}

void key::move(void)
{
	_key.distance--;
	if (_key.distance > 0)
	{
		_gravity += 0.045f;
		_key.y -= sinf(_currnetAnlgeValue) * _key.speed - _gravity;
		_key.rc = RectMakeCenter(_key.x, _key.y, _key.img->getWidth(), _key.img->getWidth());
	}
	else
	{
		_shadow->update(_key.x - 20, _key.y + 15);
		SOUNDMANAGER->play("key drop", VOLUME->getSfxVolume() / 10);
		_key.isMove = false;
	}
}
