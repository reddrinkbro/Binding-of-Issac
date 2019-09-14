#include "stdafx.h"
#include "blubber.h"
#include "dungeonMap.h"
HRESULT blubber::init(float x, float y)
{
	_blubber.img = IMAGEMANAGER->addFrameImage("blubber", "image/enemy/main/blubber.bmp", 1536, 192, 12, 3, true, RGB(255, 0, 255));
	_blubber.x = x;
	_blubber.y = y;
	_blubber.rc = RectMakeCenter(_blubber.x, _blubber.y, _blubber.img->getFrameWidth(), _blubber.img->getFrameHeight());
	_blubber.currentX = 4;
	_blubber.currentY = 0;
	_blubber.randDirection = RND->getInt(4);
	if (_blubber.randDirection == 0) _blubber.state = BLUBBERSTATE_UP;
	else if (_blubber.randDirection == 1) _blubber.state = BLUBBERSTATE_DOWN;
	else if (_blubber.randDirection == 2) _blubber.state = BLUBBERSTATE_LEFT;
	else _blubber.state = BLUBBERSTATE_RIGHT;
	
	_blubber.hp = 5.0f;
	_blubber.speed = 0.8f;
	_blubber.count = 0.0f;
	_blubber.distance = 50;

	_bullet = new blubberBullet;
	_bullet->init(RND->getFromIntTo(200, 300));

	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	return S_OK;
}

void blubber::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void blubber::update(void)
{
	_shadow->update(_blubber.x -58, _blubber.y + 15);
	frame();
	move();
	_bullet->update();
}

void blubber::render(void)
{
	_shadow->render();
	draw();
	_bullet->render();
}

void blubber::move(void)
{
	_blubber.distance--;
	if (_blubber.distance < 0)
	{
		randomDirection();
	}
	switch (_blubber.state)
	{
	case BLUBBERSTATE_UP:
		_blubber.y -= _blubber.speed;
		break;
	case BLUBBERSTATE_DOWN:
		_blubber.y += _blubber.speed;
		break;
	case BLUBBERSTATE_LEFT:
		_blubber.x -= _blubber.speed;
		break;
	case BLUBBERSTATE_RIGHT:
		_blubber.x += _blubber.speed;
		break;
	}
	_blubber.rc = RectMakeCenter(_blubber.x, _blubber.y, _blubber.img->getFrameWidth(), _blubber.img->getFrameHeight());
}

void blubber::draw(void)
{
	_blubber.img->frameRender(getMemDC(), _blubber.rc.left - CAMERAMANAGER->getX(), _blubber.rc.top - CAMERAMANAGER->getY(), _blubber.currentX, _blubber.currentY);
}

void blubber::frame(void)
{
	if (_blubber.state == BLUBBERSTATE_UP || _blubber.state == BLUBBERSTATE_DOWN)
	{
		_blubber.currentY = 0;
	}
	else if (_blubber.state == BLUBBERSTATE_LEFT)
	{
		_blubber.currentY = 2;
	}
	else if (_blubber.state == BLUBBERSTATE_RIGHT)
	{
		_blubber.currentY = 1;
	}
	if (_blubber.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_blubber.count = TIMEMANAGER->getWorldTime();
		_blubber.currentX++;
		if (_blubber.currentX == 3)
		{
			_bullet->fire(_blubber.x, _blubber.y - 10, 1.8f);
		}
		if (_blubber.currentX > _blubber.img->getMaxFrameX())
		{
			_blubber.currentX = 0;
		}
	}
}

void blubber::randomDirection(void)
{
	if (_blubber.randDirection == 0)
	{
		_blubber.state = BLUBBERSTATE_UP;
		_blubber.distance = 200;
		_blubber.randDirection = RND->getInt(4);
	}
	else if (_blubber.randDirection == 1)
	{
		_blubber.state = BLUBBERSTATE_DOWN;
		_blubber.distance = 200;
		_blubber.randDirection = RND->getInt(4);
	}
	else if (_blubber.randDirection == 2)
	{
		_blubber.state = BLUBBERSTATE_LEFT;
		_blubber.distance = 200;
		_blubber.randDirection = RND->getInt(4);
	}
	else
	{
		_blubber.state = BLUBBERSTATE_RIGHT;
		_blubber.distance = 200;
		_blubber.randDirection = RND->getInt(4);
	}
}

void blubber::bulletHit(float angle, float damage)
{
	_blubber.x += cosf(angle)*_blubber.speed * 8;
	_blubber.y -= sinf(angle)*_blubber.speed * 8;
	_blubber.rc = RectMakeCenter(_blubber.x, _blubber.y, _blubber.img->getFrameWidth(), _blubber.img->getFrameHeight());
	_blubber.hp-= damage;
}