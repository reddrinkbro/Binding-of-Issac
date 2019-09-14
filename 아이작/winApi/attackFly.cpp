#include "stdafx.h"
#include "attackFly.h"

HRESULT attackFly::init(float x, float y)
{
	_attackFly.img = IMAGEMANAGER->addFrameImage("attackFly", "image/enemy/main/attackFly.bmp", 98, 32, 2, 1, true, RGB(255, 0, 255));
	_attackFly.x = x;
	_attackFly.y = y;
	_attackFly.rc = RectMakeCenter(_attackFly.x, _attackFly.y, _attackFly.img->getFrameWidth(), _attackFly.img->getFrameHeight());
	_attackFly.wolrdCount = 0.0f;
	_attackFly.randCount = RND->getFromFloatTo(0.02f,0.025f);
	_attackFly.angle = 0.0f;
	_attackFly.currentX = 0;
	_attackFly.hp = 3.0f;
	_attackFly.speed = 0.8f;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void attackFly::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void attackFly::update(void)
{
}

void attackFly::render(void)
{
	draw();
}

void attackFly::move(float x, float y)
{
	_shadow->update(_attackFly.x - 20, _attackFly.y + 50);
	frame();
	_attackFly.angle = getAngle(_attackFly.x, _attackFly.y, x, y);
	_attackFly.x += cosf(_attackFly.angle)*_attackFly.speed;
	_attackFly.y -= sinf(_attackFly.angle)*_attackFly.speed;
	_attackFly.rc = RectMakeCenter(_attackFly.x, _attackFly.y, _attackFly.img->getFrameWidth(), _attackFly.img->getFrameHeight());
}

void attackFly::draw(void)
{
	_shadow->render();
	_attackFly.img->frameRender(getMemDC(), _attackFly.rc.left- CAMERAMANAGER->getX(), _attackFly.rc.top - CAMERAMANAGER->getY(), _attackFly.currentX, 0);
}

void attackFly::frame(void)
{
	if (_attackFly.wolrdCount + _attackFly.randCount < TIMEMANAGER->getWorldTime())
	{
		_attackFly.wolrdCount = TIMEMANAGER->getWorldTime();
		if (_attackFly.currentX == 0)
		{
			_attackFly.currentX = 1;
		}
		else
		{
			_attackFly.currentX = 0;
		}
	}
}

void attackFly::bulletHit(float angle, float damage)
{
	_attackFly.x += cosf(angle)*_attackFly.speed * 10;
	_attackFly.y -= sinf(angle)*_attackFly.speed * 10;
	_attackFly.rc = RectMakeCenter(_attackFly.x, _attackFly.y, _attackFly.img->getFrameWidth(), _attackFly.img->getFrameHeight());
	_attackFly.hp-= damage;
}
