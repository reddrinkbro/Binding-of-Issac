#include "stdafx.h"
#include "healthPoint.h"

HRESULT healthPoint::init(float x, float y , bool isInChest)
{
	_healthPoint.img = IMAGEMANAGER->addImage("healthPoint", "image/item/healthPoint.bmp", 32, 26, true, RGB(255, 0, 255));
	_healthPoint.x = x;
	_healthPoint.y = y;
	_healthPoint.rc = RectMakeCenter(_healthPoint.x, _healthPoint.y, _healthPoint.img->getWidth(), _healthPoint.img->getHeight());
	_healthPoint.distance = 100;
	_healthPoint.isMove = true;
	_healthPoint.isInChest = isInChest;
	_healthPoint.angle = -PI / 3;
	if (isInChest) _healthPoint.speed = 0.6f;
	else _healthPoint.speed = 0.0f;

	_gravity = -2.0f;
	_currnetAnlgeValue = PI / 2;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void healthPoint::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void healthPoint::update(void)
{
	 drop();
}

void healthPoint::render(void)
{
	_shadow->render();
	draw();
}

void healthPoint::draw(void)
{
	_healthPoint.img->render(getMemDC(), _healthPoint.rc.left - CAMERAMANAGER->getX(), _healthPoint.rc.top - CAMERAMANAGER->getY());
}


void healthPoint::move(float x, float y, float speed)
{
	float angle = getAngle(x, y, _healthPoint.x, _healthPoint.y);
	_healthPoint.x += cosf(angle)* (speed - 1);
	_healthPoint.y -= sinf(angle)* (speed - 1);
	_healthPoint.rc = RectMakeCenter(_healthPoint.x, _healthPoint.y, _healthPoint.img->getWidth(), _healthPoint.img->getHeight());
}

void healthPoint::drop(void)
{
	_healthPoint.distance--;
	if (_healthPoint.distance > 0)
	{
		if (_healthPoint.isInChest) _gravity += 0.05f;
		else _gravity += 0.045f;
		_healthPoint.x += cosf(_healthPoint.angle + _currnetAnlgeValue) * _healthPoint.speed;
		_healthPoint.y -= sinf(_healthPoint.angle + _currnetAnlgeValue) * _healthPoint.speed - _gravity;
		_healthPoint.rc = RectMakeCenter(_healthPoint.x, _healthPoint.y, _healthPoint.img->getWidth(), _healthPoint.img->getHeight());
	}
	else
	{
		_shadow->update(_healthPoint.x - 20, _healthPoint.y);
		_healthPoint.isMove = false;
	}
}
