#include "stdafx.h"
#include "charger.h"

HRESULT charger::init(float x, float y)
{
	int randomDirection = RND->getInt(4);
	_charger.img = IMAGEMANAGER->addFrameImage("charger", "image/enemy/main/charger.bmp", 256, 320, 4, 5, true, RGB(255, 0, 255));
	_charger.x = x;
	_charger.y = y;
	_charger.rc = RectMakeCenter(_charger.x, _charger.y, _charger.img->getFrameWidth(), _charger.img->getFrameHeight());
	_charger.hp = 2.0f;
	_charger.currentX = 0;
	_charger.currentY = 0;
	_charger.speed = 1.0f;
	if (randomDirection == 0) _charger.state = CHARGERSTATE_UP;
	else if (randomDirection == 1) _charger.state = CHARGERSTATE_DOWN;
	else if (randomDirection == 2) _charger.state = CHARGERSTATE_LEFT;
	else  _charger.state = CHARGERSTATE_RIGHT;
	_charger.isCharge = false;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void charger::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void charger::update(void)
{
	if (!_charger.isCharge)
	{
		frame();
		move();
	}
	_shadow->update(_charger.x - 20, _charger.y);
	_charger.rc = RectMakeCenter(_charger.x, _charger.y, _charger.img->getFrameWidth(), _charger.img->getFrameHeight());
}

void charger::render(void)
{
	_shadow->render();
	draw();
}

void charger::move(void)
{
	switch (_charger.state)
	{
	case CHARGERSTATE_UP:
		_charger.y -= _charger.speed;
		break;
	case CHARGERSTATE_DOWN:
		_charger.y += _charger.speed;
		break;
	case CHARGERSTATE_LEFT:
		_charger.x -= _charger.speed;
		break;
	case CHARGERSTATE_RIGHT:
		_charger.x += _charger.speed;
		break;
	}
}

void charger::draw(void)
{
	_charger.img->frameRender(getMemDC(), _charger.rc.left - CAMERAMANAGER->getX(), _charger.rc.top - CAMERAMANAGER->getY(), _charger.currentX , _charger.currentY);
}

void charger::frame(void)
{
	switch (_charger.state)
	{
	case CHARGERSTATE_UP:
		_charger.currentY = 2;
		break;
	case CHARGERSTATE_DOWN:
		_charger.currentY = 3;
		break;
	case CHARGERSTATE_LEFT:
		_charger.currentY = 1;
		break;
	case CHARGERSTATE_RIGHT:
		_charger.currentY = 0;
		break;
	}
	if (_charger.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_charger.count = TIMEMANAGER->getWorldTime();
		_charger.currentX++;
		if (_charger.currentX > _charger.img->getMaxFrameX())
		{
			_charger.currentX = 0;
		}
	}
}

void charger::charge(float x, float y)
{
	_charger.isCharge = true;
	_charger.currentY = 4;
	if (_charger.rc.top > y)
	{
		_charger.state = CHARGERSTATE_UP;
	}
	else if (_charger.rc.left > x)
	{
		_charger.state = CHARGERSTATE_LEFT;
	}
	else if (_charger.rc.right < x)
	{ 
		_charger.state = CHARGERSTATE_RIGHT;
	}
	else
	{
		_charger.state = CHARGERSTATE_DOWN;
	}
	switch (_charger.state)
	{
	case CHARGERSTATE_UP:
		_charger.currentX = 2;
		_charger.y -= 2.7f;
		break;
	case CHARGERSTATE_DOWN:
		_charger.currentX = 0;
		_charger.y += 2.7f;
		break;
	case CHARGERSTATE_LEFT:
		_charger.currentX = 3;
		_charger.x -= 2.7f;
		break;
	case CHARGERSTATE_RIGHT:
		_charger.currentX = 1;
		_charger.x += 2.7f;
		break;
	}
}

void charger::bulletHit(float damage)
{
	_charger.hp -= damage;
}
