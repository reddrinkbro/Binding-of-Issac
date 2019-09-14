#include "stdafx.h"
#include "clotty.h"

HRESULT clotty::init(float x, float y)
{
	_randomDirection = RND->getInt(2);
	_randomBreakTime = RND->getFromFloatTo(200.0f, 220.0f);
	_shottingTime = 0;
	_clotty.img = IMAGEMANAGER->addFrameImage("clotty", "image/enemy/main/clotty.bmp", 1408, 256, 11, 2, true, RGB(255, 0, 255));
	_clotty.x = x;
	_clotty.y = y;
	_clotty.rc = RectMakeCenter(_clotty.x, _clotty.y, _clotty.img->getFrameWidth(), _clotty.img->getFrameHeight());
	if (_randomDirection == 0)
	{
		_clotty.state = CLOTTYSTATE_LEFT;
	}
	else
	{
		_clotty.state = CLOTTYSTATE_RIGHT;
	}
	_clotty.count = 0.0f;
	_clotty.speed = 1.0f;
	_clotty.currentX = 0;
	_clotty.currentY = 0;
	//체력 수정 필요
	_clotty.hp = 4.0f;
	_bullet = new clottyBullet;
	_bullet->init(300);
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	return S_OK;
}

void clotty::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void clotty::update(void)
{
	frame();
	move();
	if (_shottingTime == 0)
	{
		restTime();
	}
	_shadow->update(_clotty.x-28, _clotty.y + 30);
	_bullet->update();
}

void clotty::render(void)
{
	_shadow->render();
	_bullet->render();
	draw();
}

void clotty::move(void)
{
	if (_clotty.state == CLOTTYSTATE_LEFT)
	{
		_clotty.x += _clotty.speed;
	}
	else
	{
		_clotty.x -= _clotty.speed;
	}
	_clotty.rc = RectMakeCenter(_clotty.x, _clotty.y, _clotty.img->getFrameWidth(), _clotty.img->getFrameHeight());
}

void clotty::draw(void)
{
	_clotty.img->frameRender(getMemDC(), _clotty.rc.left - CAMERAMANAGER->getX(), _clotty.rc.top - CAMERAMANAGER->getY(), _clotty.currentX, _clotty.currentY);
}

void clotty::frame(void)
{
	if (_clotty.state == CLOTTYSTATE_LEFT)
	{
		_clotty.currentY = 0;
	}
	else
	{
		_clotty.currentY = 1;
	}
	if (_clotty.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_clotty.count = TIMEMANAGER->getWorldTime() + 0.01f;
		_clotty.currentX++;
		if (_clotty.currentX > 7 && _shottingTime == 0)
		{
			_clotty.currentX = 0;
		}
		else if (_clotty.currentX > _clotty.img->getMaxFrameX())
		{
			_clotty.currentX = 0;
		}
		if (_clotty.currentX == 9 && _shottingTime !=0)
		{
			fire();
			_shottingTime--;
		}
	}
}

void clotty::fire(void)
{
	_bullet->fire(_clotty.x, _clotty.y, 2.5f);
}

void clotty::restTime(void)
{
	if (_randomBreakTime > 0)
	{
		_randomBreakTime--;
	}
	else
	{
		_randomBreakTime = RND->getFromFloatTo(200.0f, 280.0f);
		_shottingTime = 3;
	}
}

void clotty::bulletHit(float angle, float damage)
{
	_clotty.x += cosf(angle)*_clotty.speed * 8;
	_clotty.y -= sinf(angle)*_clotty.speed * 8;
	_clotty.rc = RectMakeCenter(_clotty.x, _clotty.y, _clotty.img->getFrameWidth(), _clotty.img->getFrameHeight());
	_clotty.hp-= damage;
}
