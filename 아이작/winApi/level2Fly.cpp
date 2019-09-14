#include "stdafx.h"
#include "level2Fly.h"

HRESULT level2Fly::init(float x, float y)
{
	_level2Fly.img = IMAGEMANAGER->addFrameImage("level2Fly", "image/enemy/main/level2Fly.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	_level2Fly.x = x;
	_level2Fly.y = y;
	_level2Fly.rc = RectMakeCenter(_level2Fly.x, _level2Fly.y, _level2Fly.img->getFrameWidth(), _level2Fly.img->getFrameHeight());
	_level2Fly.angle = 0.0f;
	_level2Fly.currentX = 0.0f;
	_level2Fly.hp = 3.0f;
	_level2Fly.wolrdCount = 0.0f;
	_level2Fly.speed = 1.8f;
	_level2Fly.randCount = RND->getFromFloatTo(0.02f, 0.025f);
	_isfireEnd = false;
	_playerX = _playerY = 0;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void level2Fly::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void level2Fly::update(float x, float y)
{
	_shadow->update(_level2Fly.x - 20, _level2Fly.y + 50);
	_playerX = x;
	_playerY = y;
	frame();
	move();
	
}

void level2Fly::render(void)
{
	_shadow->render();
	draw();
	
}

void level2Fly::move(void)
{
	_level2Fly.angle = getAngle(_level2Fly.x, _level2Fly.y, _playerX, _playerY);
	_level2Fly.x += cosf(_level2Fly.angle) * _level2Fly.speed;
	_level2Fly.y -= sinf(_level2Fly.angle) * _level2Fly.speed;
	_level2Fly.rc = RectMakeCenter(_level2Fly.x, _level2Fly.y, _level2Fly.img->getFrameWidth(), _level2Fly.img->getFrameHeight());
}

void level2Fly::draw(void)
{
	
	_level2Fly.img->frameRender(getMemDC(), _level2Fly.rc.left - CAMERAMANAGER->getX(), _level2Fly.rc.top - CAMERAMANAGER->getY(), _level2Fly.currentX, 0);
	
}

void level2Fly::frame(void)
{
	if (_level2Fly.wolrdCount + _level2Fly.randCount < TIMEMANAGER->getWorldTime())
	{
		_level2Fly.wolrdCount = TIMEMANAGER->getWorldTime();
		if (_level2Fly.currentX == 0)
		{
			_level2Fly.currentX = 1;
		}
		else
		{
			_level2Fly.currentX = 0;
		}
	}
}

void level2Fly::bulletHit(float angle, float damage)
{
	_level2Fly.x += cosf(angle)*_level2Fly.speed * 8;
	_level2Fly.y -= sinf(angle)*_level2Fly.speed * 8;
	_level2Fly.rc = RectMakeCenter(_level2Fly.x, _level2Fly.y, _level2Fly.img->getFrameWidth(), _level2Fly.img->getFrameHeight());
	_level2Fly.hp-= damage;
}
