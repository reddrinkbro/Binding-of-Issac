#include "stdafx.h"
#include "tumor.h"

HRESULT tumor::init(float x, float y)
{
	_tumor.img = IMAGEMANAGER->addFrameImage("tumor", "image/enemy/main/tumor.bmp", 376, 183, 4, 2, true, RGB(255, 0, 255));
	_tumor.x = x;
	_tumor.y = y;
	_tumor.rc = RectMakeCenter(_tumor.x, _tumor.y, _tumor.img->getFrameWidth(), _tumor.img->getFrameHeight());
	_tumor.currentX = 0;
	_tumor.currentY = 0;
	_tumor.speed = 0.2f;
	_tumor.hp = 5.0f;
	_tumor.count = 0.0f;
	_tumor.distance = 50;
	_tumor.state = TUMORSTATE_DOWN;

	_shootingTime = 3;
	_tumorFrame = 0.24f;

	_bullet = new sixWayBullet;
	_bullet->init(300);

	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	return S_OK;
}

void tumor::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void tumor::update(void)
{
	_shadow->update(_tumor.x - 28, _tumor.y + 50);
	if (_tumor.distance < 0)
	{
		frame();
	}
	if (_tumor.hp < 3 && _tumor.hp > 1)
	{
		_tumorFrame = 0.18f;
	}
	else if (_tumor.hp == 1)
	{
		_tumorFrame = 0.12f;
	}
	_bullet->update();
}

void tumor::render(void)
{
	_shadow->render();
	_bullet->render();
	draw();
}

void tumor::move(float x, float y)
{
	if (_tumor.y < y) _tumor.state = TUMORSTATE_DOWN;
	else _tumor.state = TUMORSTATE_UP;
	if (_tumor.state == TUMORSTATE_DOWN)
	{
		if (_tumor.x > x) _tumor.x -= _tumor.speed;
		else _tumor.x += _tumor.speed;
		if(_tumor.y > y + 30 || _tumor.y < y - 30) _tumor.y += _tumor.speed;
		_tumor.distance--;
	}
	else
	{
		if (_tumor.x > x) _tumor.x -= _tumor.speed;
		else _tumor.x += _tumor.speed;
		if (_tumor.y > y - 30) _tumor.y -= _tumor.speed;
		_tumor.distance--;
	}
	_tumor.rc = RectMakeCenter(_tumor.x, _tumor.y, _tumor.img->getFrameWidth(), _tumor.img->getFrameHeight());
}

void tumor::draw(void)
{
	_tumor.img->frameRender(getMemDC(), _tumor.rc.left - CAMERAMANAGER->getX(), _tumor.rc.top - CAMERAMANAGER->getY(), _tumor.currentX, _tumor.currentY);
}

void tumor::frame(void)
{
	if (_tumor.state == TUMORSTATE_DOWN)
	{
		_tumor.currentY = 0;
	}
	else if (_tumor.state == TUMORSTATE_UP)
	{
		_tumor.currentY = 1;
	}
	if (_tumor.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_tumor.count = TIMEMANAGER->getWorldTime() + _tumorFrame;
		_tumor.currentX++;
		if (_tumor.currentX == _tumor.img->getMaxFrameX() && _shootingTime >= 0)
		{
			fire();
		}
		else if (_tumor.currentX == _tumor.img->getMaxFrameX() && _shootingTime < 0)
		{
			_shootingTime = 3;
			_tumor.distance = 50;
		}
		if (_tumor.currentX > _tumor.img->getMaxFrameX())
		{
			_tumor.currentX = 0;
		}
	}
}

void tumor::fire(void)
{
	_bullet->fire(_tumor.x, _tumor.y, 5.0f);
}

void tumor::bulletHit(float angle, float damage)
{
	_tumor.x += cosf(angle)*_tumor.speed * 8;
	_tumor.y -= sinf(angle)*_tumor.speed * 8;
	_tumor.rc = RectMakeCenter(_tumor.x, _tumor.y, _tumor.img->getFrameWidth(), _tumor.img->getFrameHeight());
	_tumor.hp-= damage;
}
