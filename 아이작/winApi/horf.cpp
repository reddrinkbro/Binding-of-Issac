#include "stdafx.h"
#include "horf.h"

HRESULT horf::init(float x, float y)
{
	_horf.img = IMAGEMANAGER->addFrameImage("horf", "image/enemy/main/horf.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));
	_horf.x = x;
	_horf.y = y;
	_horf.rc = RectMakeCenter(_horf.x, _horf.y, _horf.img->getFrameWidth(), _horf.img->getFrameHeight());
	_horf.speed = 0.9f;
	_horf.hp = 3.0f;
	_horf.currentX = 0;
	_horf.distance = 5.0f;
	_horf.state = HORFSTATE_NONE;
	_horf.isFire = false;
	_horf.count = 0.0f;
	_coolDownTime = 100;
	_bullet = new horfBullet;
	_bullet->init();
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	return S_OK;
}

void horf::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void horf::update(float x, float y)
{
	_shadow->update(_horf.rc.left + 5, _horf.rc.top + 50);
	float distance = getDistance(_horf.x, _horf.y, x, y);
	_horf.targetX = x;
	_horf.targetY = y;
	if (distance<300 && _coolDownTime <= 0)
	{
		_horf.isFire = true;
	}
	if (!_horf.isFire)
	{
		_horf.currentX = 0;
		move();
		_coolDownTime--;
	}
	else 
	{
		frame();
	}
	_bullet->update();
}

void horf::render(void)
{
	_shadow->render();
	_bullet->draw();
	draw();
}

void horf::move(void)
{
	if (_horf.state == HORFSTATE_NONE)
	{
		_horf.x += _horf.speed;
		_horf.distance -= 0.5;
		_horf.state = HORFSTATE_LEFT;
	}
	else if (_horf.state == HORFSTATE_LEFT)
	{
		_horf.x -= _horf.speed;
		_horf.distance-= 0.5f;
		if (_horf.distance < 0)
		{
			_horf.distance = 5.0f;
			_horf.state = HORFSTATE_RIGHT;
		}
	}
	else if (_horf.state == HORFSTATE_RIGHT)
	{
		_horf.x += _horf.speed;
		_horf.distance-= 0.5f;
		if (_horf.distance < 0)
		{
			_horf.distance = 5.0f;
			_horf.state = HORFSTATE_LEFT;
		}
	}
	_horf.rc = RectMakeCenter(_horf.x, _horf.y, _horf.img->getFrameWidth(), _horf.img->getFrameHeight());
}

void horf::draw(void)
{
	_horf.img->frameRender(getMemDC(), _horf.rc.left - CAMERAMANAGER->getX(), _horf.rc.top - CAMERAMANAGER->getY(), _horf.currentX, 0);
}

void horf::frame(void)
{
	if (_horf.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_horf.count = TIMEMANAGER->getWorldTime() + 0.7f;
		_horf.currentX++;
		if(_horf.currentX == _horf.img->getMaxFrameX()) _bullet->fire(_horf.x, _horf.y, _horf.targetX, _horf.targetY, 2.5f);
		if (_horf.currentX > _horf.img->getMaxFrameX())
		{
			_horf.currentX = 0;
			_coolDownTime = 100;
			_horf.isFire = false;
		}
	}
}

void horf::bulletHit(float angle, float damage)
{
	_horf.x += cosf(angle)*_horf.speed ;
	_horf.y -= sinf(angle)*_horf.speed ;
	_horf.rc = RectMakeCenter(_horf.x, _horf.y, _horf.img->getFrameWidth(), _horf.img->getFrameHeight());
	_horf.hp-= damage;
}
