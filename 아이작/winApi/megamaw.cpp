#include "stdafx.h"
#include "megamaw.h"

HRESULT megamaw::init(float x, float y)
{
	_megamaw.img = IMAGEMANAGER->addFrameImage("megamaw", "image/enemy/boss/megamaw.bmp", 3260, 1304, 10, 4, true, RGB(255, 0, 255));
	_megamaw.x = x;
	_megamaw.y = y;
	_megamaw.rc = RectMakeCenter(_megamaw.x, _megamaw.y, _megamaw.img->getFrameWidth(), _megamaw.img->getFrameHeight());
	_megamaw.count = 0;
	_megamaw.currentX = 0;
	_megamaw.currentY = 0;
	_megamaw.maxHp = 20.0f;
	_megamaw.hp = _megamaw.maxHp;
	_megamaw.randomPattern = RND->getInt(2);
	_megamaw.restTime = 150;
	_megamaw.speed = 1.3f;
	_megamaw.isLeft = true;
	_megamaw.moveDistance = 5.0f;
	_megamaw.state = MEGAMAWSTATE_START;
	_megamaw.shakeTime = 3;

	_bullet = new megamawBullet;
	_bullet->init();
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_LARGE);
	_hpBar = new progressBar;
	_hpBar->init("image/UI/bossHpBarTop", "image/UI/bossHpBarBottom", CAMERAMANAGER->getGameMaxRenderX() / 2 - 129, 0, 258, 36);
	EFFECTMANAGER->addEffect("largeBloodEffect", "image/enemy/effect/largeBloodEffect.bmp", 3360, 166, 280, 166, 14, 1);
	return S_OK;
}

void megamaw::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void megamaw::update(float x, float y)
{
	_hpBar->setGauge(_megamaw.hp, _megamaw.maxHp);
	_hpBar->update();
	_megamaw.targetX = x;
	_megamaw.targetY = y;

	frame();
	_bullet->update();
	_shadow->update(_megamaw.x - 60, _megamaw.y + 110);
}

void megamaw::render(void)
{
	_hpBar->render();
	_shadow->render();
	draw();
	_bullet->render();
}

void megamaw::draw(void)
{
	_megamaw.img->frameRender(getMemDC(), _megamaw.rc.left - CAMERAMANAGER->getX(), _megamaw.rc.top - CAMERAMANAGER->getY(), _megamaw.currentX, _megamaw.currentY);
}

void megamaw::frame(void)
{
	if (_megamaw.state == MEGAMAWSTATE_START)
	{
		_megamaw.currentY = 0;
		if (_megamaw.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if(_megamaw.currentX == 2) _megamaw.count = TIMEMANAGER->getWorldTime() + 0.6f;
			else _megamaw.count = TIMEMANAGER->getWorldTime();
			_megamaw.currentX++;
			if (_megamaw.currentX > 6)
			{
				_megamaw.currentX = 6;
				_megamaw.state = MEGAMAWSTATE_NONE;
			}
		}
	}
	else if (_megamaw.state == MEGAMAWSTATE_NONE)
	{
		_megamaw.currentX = 6;
		_megamaw.currentY = 0;
		selectPattern();
	}
	else if (_megamaw.state == MEGAMAWSTATE_PATTERN1)
	{
		_megamaw.currentY = 1;
		if (_megamaw.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if(_megamaw.currentX == 1)_megamaw.count = TIMEMANAGER->getWorldTime() + 0.3f;
			else _megamaw.count = TIMEMANAGER->getWorldTime();
			if (_megamaw.currentX == 2)
			{
				shake();
				if (_megamaw.shakeTime < 0)
				{
					_megamaw.currentX++;
					_megamaw.shakeTime = 3;
				}
			}
			else
			{
				if (_megamaw.currentX == 4)
				{
					_megamaw.targetDistance = getDistance(_megamaw.x, _megamaw.y, _megamaw.targetX, _megamaw.targetY);
					_bullet->fire(_megamaw.x, _megamaw.y + 100, _megamaw.angle, 9, _megamaw.targetDistance, 0);
					SOUNDMANAGER->play("megamaw fire1", VOLUME->getSfxVolume() / 10);
				}
				_megamaw.currentX++;
			}
			if (_megamaw.currentX > 6)
			{
				_megamaw.currentX = 6;
				_megamaw.state = MEGAMAWSTATE_NONE;
			}
		}
	}
	else if (_megamaw.state == MEGAMAWSTATE_PATTERN2)
	{
		_megamaw.currentY = 2;
		if (_megamaw.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if (_megamaw.currentX > 4)
			{
				_megamaw.count = TIMEMANAGER->getWorldTime() - 0.05f;
				if(_megamaw.currentX == 7 ) SOUNDMANAGER->play("megamaw fire2", VOLUME->getSfxVolume() / 10);
				if (_megamaw.currentX == 8)
				{
					_bullet->fire(_megamaw.x, _megamaw.y + 100, _megamaw.angle, 10, _megamaw.targetDistance, RND->getFromIntTo(1, 3));
				}
			}
			else _megamaw.count = TIMEMANAGER->getWorldTime();
			_megamaw.currentX++;
			if (_megamaw.currentX > _megamaw.img->getMaxFrameX())
			{
				_megamaw.currentX = _megamaw.img->getMaxFrameX();
				_megamaw.state = MEGAMAWSTATE_NONE;
			}
		}
	}
	else if (_megamaw.state == MEGAMAWSTATE_DIE)
	{
		_megamaw.currentY = 3;
		if (_megamaw.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_megamaw.count = TIMEMANAGER->getWorldTime();
			_megamaw.currentX++;
			if (_megamaw.currentX > 1)
			{
				_megamaw.currentX = 1;
			}
		}
	}
}

void megamaw::shake(void)
{
	if (_megamaw.isLeft)
	{
		_megamaw.x -= _megamaw.speed;
		_megamaw.moveDistance -= 5.0f;
		if (_megamaw.moveDistance < 0)
		{
			_megamaw.moveDistance = 5.0f;
			_megamaw.shakeTime--;
			_megamaw.isLeft = false;
		}
	}
	else if (!_megamaw.isLeft)
	{
		_megamaw.x += _megamaw.speed;
		_megamaw.moveDistance -= 5.0f;
		if (_megamaw.moveDistance < 0)
		{
			_megamaw.moveDistance = 5.0f;
			_megamaw.shakeTime--;
			_megamaw.isLeft = true;
		}
	}
	_megamaw.rc = RectMakeCenter(_megamaw.x, _megamaw.y, _megamaw.img->getFrameWidth(), _megamaw.img->getFrameHeight());
}

void megamaw::selectPattern(void)
{
	_megamaw.restTime--;
	if (_megamaw.restTime < 0)
	{
		_megamaw.angle = getAngle(_megamaw.x, _megamaw.y, _megamaw.targetX, _megamaw.targetY);
		_megamaw.currentX = 0;
		if (_megamaw.randomPattern == 0)
		{
			if (_megamaw.rc.left < _megamaw.targetX && _megamaw.rc.right > _megamaw.targetX) _megamaw.state = MEGAMAWSTATE_PATTERN1;
			else _megamaw.state = MEGAMAWSTATE_PATTERN2;
		}
		else
		{
			_megamaw.state = MEGAMAWSTATE_PATTERN2;
		}
		_megamaw.randomPattern = RND->getInt(2);
		_megamaw.restTime = 150;
	}
}

void megamaw::bulletHit(float damage)
{
	_megamaw.hp -= damage;
}
