#include "stdafx.h"
#include "monstro.h"

HRESULT monstro::init(float x, float y)
{
	_monstro.img = IMAGEMANAGER->addFrameImage("monstro", "image/enemy/boss/monstro.bmp", 1600, 1344, 10, 6, true, RGB(255, 0, 255));
	_monstro.x = x;
	_monstro.y = y;
	_monstro.rc = RectMakeCenter(_monstro.x, _monstro.y, _monstro.img->getFrameWidth(), _monstro.img->getFrameHeight());
	_monstro.currentX = 0;
	_monstro.currentY = 0;
	_monstro.count = 0.0f;
	_monstro.maxHp = 20.0f;
	_monstro.hp = _monstro.maxHp;
	_monstro.angle = 0.0f;
	_monstro.randomPattern = RND->getInt(2);
	_monstro.restTime = 100;
	_monstro.speed = 2.3f;
	_monstro.isLeft = true;
	_monstro.state = MONSTROSTATE_NONE;
	_monstro.isDown = false;
	_monstro.jumpDistance = 400;
	_bullet = new monstroBullet;
	_bullet->init();
	_gravity = -5.0f;
	EFFECTMANAGER->addEffect("largeBloodEffect", "image/enemy/effect/largeBloodEffect.bmp", 3360, 166, 280, 166, 14, 1);
	EFFECTMANAGER->addEffect("pukeBulletEffect", "image/effect/pukeBulletEffect.bmp", 768, 64, 64, 64, 14, 1);
	_hpBar = new progressBar;
	_hpBar->init("image/UI/bossHpBarTop", "image/UI/bossHpBarBottom", CAMERAMANAGER->getGameMaxRenderX() / 2 - 129, 0, 258, 36);
	return S_OK;
}

void monstro::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void monstro::update(float x, float y)
{
	_hpBar->setGauge(_monstro.hp, _monstro.maxHp);
	_hpBar->update();
	_monstro.moveTargetPos.x = x;
	_monstro.moveTargetPos.y = y;
	frame();
	if (_monstro.state == MONSTROSTATE_NONE)
	{
		_monstro.currentX = 0;
		if(_monstro.isLeft)	_monstro.currentY = 0;
		else _monstro.currentY = 3;
		SOUNDMANAGER->stop("monstro fire");
		
		findPlayerPos();
	}
	else if(_monstro.state == MONSTROSTATE_MOVE)
	{
		move();
	}
	else if (_monstro.state == MONSTROSTATE_JUMP)
	{
		jump();
	}
	
	_bullet->update();
}

void monstro::render(void)
{
	_hpBar->render();
	draw();
	_bullet->render();
}

void monstro::move()
{	
	if (_monstro.y + 200 < _monstro.moveTargetPos.y)
	{
		_gravity += 0.085f;
	}
	else if (_monstro.y - 200 > _monstro.moveTargetPos.y)
	{
		_gravity += 0.05f;
	}
	else
	{
		_gravity += 0.075f;
	}
	if (_monstro.currentX < 3)
	{
		_monstro.x += cosf(_monstro.angle)*_monstro.speed;
		_monstro.y -= sinf(_monstro.angle)*_monstro.speed - _gravity;
		_monstro.rc = RectMakeCenter(_monstro.x, _monstro.y, _monstro.img->getFrameWidth(), _monstro.img->getFrameHeight());
	}
}

void monstro::draw(void)
{
	_monstro.img->frameRender(getMemDC(), _monstro.rc.left - CAMERAMANAGER->getX(), _monstro.rc.top - CAMERAMANAGER->getY(), _monstro.currentX, _monstro.currentY);
}

void monstro::frame(void)
{

	if (_monstro.state == MONSTROSTATE_FIRE)
	{
		if (_monstro.isLeft) _monstro.currentY = 0;
		else _monstro.currentY = 3;
		if (_monstro.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if (_monstro.currentX == 0) _monstro.count = TIMEMANAGER->getWorldTime() + 0.05f;
			else if (_monstro.currentX == 2)
			{
				_monstro.count = TIMEMANAGER->getWorldTime() + 0.65f;
				_bullet->fire(_monstro.x, _monstro.y + 50, _monstro.angle, RND->getFromIntTo(10, 12), false);
				SOUNDMANAGER->play("monstro fire", VOLUME->getSfxVolume() / 10);
			}
			else _monstro.count = TIMEMANAGER->getWorldTime();
			_monstro.currentX++;
			if (_monstro.currentX > 3)
			{
				_monstro.currentX = 0;
				_monstro.state = MONSTROSTATE_NONE;
			}
		}
	}
	else if (_monstro.state == MONSTROSTATE_JUMP)
	{
		if (_monstro.isLeft) _monstro.currentY = 2;
		else _monstro.currentY = 5;
		if (_monstro.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if (_monstro.currentX < 2)
			{
				SOUNDMANAGER->stop("monstro jump");
				_monstro.count = TIMEMANAGER->getWorldTime() -0.05f;
				_monstro.currentX++;
			}
			else if (_monstro.currentX > 4)
			{
				if (_monstro.currentX == 6)
				{
					_bullet->fire(_monstro.x, _monstro.y + 100, _monstro.angle, RND->getFromIntTo(18, 20), true);
					SOUNDMANAGER->play("monstro jump", VOLUME->getSfxVolume() / 10);
				}
				_monstro.count = TIMEMANAGER->getWorldTime() - 0.05f;
				_monstro.currentX++;
			}
			if (_monstro.currentX > _monstro.img->getMaxFrameX())
			{
				_monstro.currentX = 0;
				_monstro.isDown = false;
				_monstro.state = MONSTROSTATE_NONE;
			}
		}
	}
	else if (_monstro.state == MONSTROSTATE_MOVE)
	{
		if (_monstro.isLeft) _monstro.currentY = 1;
		else _monstro.currentY = 4;
		
		if (_monstro.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			if (_monstro.currentX == 1)
			{
				_monstro.count = TIMEMANAGER->getWorldTime() + 0.65f;
				SOUNDMANAGER->stop("monstro jump");
			}
			else if (_monstro.currentX > 2)
			{
				_monstro.count = TIMEMANAGER->getWorldTime() - 0.05f;
				if (_monstro.currentX == 4)
				{
					SOUNDMANAGER->play("monstro jump", VOLUME->getSfxVolume() / 10);
				}
			}
			else _monstro.count = TIMEMANAGER->getWorldTime();
			_monstro.currentX++;
			if (_monstro.currentX > 8)
			{
				_gravity = -5.0f;
				_monstro.currentX = 0;
				_monstro.state = MONSTROSTATE_NONE;
			}
		}
	}
	else if (_monstro.state == MONSTROSTATE_DIE)
	{
		if (_monstro.isLeft)
		{
			_monstro.currentX = 9;
			_monstro.currentY = 2;
		}
		else
		{
			_monstro.currentX = 9;
			_monstro.currentY = 5;
		}
	}
}

void monstro::jump(void)
{
	if (_monstro.isLeft &&_monstro.x >= _monstro.jumpTargetPos.x && _monstro.currentX == 3)
	{
		_monstro.x -= 10.0f;
	}
	else if (_monstro.isLeft && _monstro.x < _monstro.jumpTargetPos.x && _monstro.currentX == 3)
	{
		_monstro.currentX = 4;
	}
	if (!_monstro.isLeft &&_monstro.x <= _monstro.jumpTargetPos.x && _monstro.currentX == 3)
	{
		_monstro.x += 10.0f;
	}
	else if (!_monstro.isLeft &&_monstro.x > _monstro.jumpTargetPos.x && _monstro.currentX == 3)
	{
		_monstro.currentX = 4;
	}
	if (!_monstro.isDown)
	{
		_monstro.jumpDistance -= 5.0f;
		_monstro.y -= 14.0f;
		if (_monstro.jumpDistance < 0)
		{
			_monstro.currentX = 3;
			_monstro.jumpDistance = 400;
			_monstro.isDown = true;
		}
	}
	else if (_monstro.isDown && _monstro.currentX == 4)
	{
		_monstro.y += 13.0f;
		if (_monstro.jumpTargetPos.y - 80 < _monstro.y)
		{
			_monstro.currentX = 5;
		}
	}
	_monstro.rc = RectMakeCenter(_monstro.x, _monstro.y, _monstro.img->getFrameWidth(), _monstro.img->getFrameHeight());
}

void monstro::findPlayerPos(void)
{
	_monstro.restTime--;
	if (_monstro.restTime < 0)
	{
		_monstro.jumpTargetPos = _monstro.moveTargetPos;
		_monstro.angle = getAngle(_monstro.x, _monstro.y, _monstro.moveTargetPos.x, _monstro.moveTargetPos.y);
		_monstro.moveDistance = getDistance(_monstro.x, _monstro.y, _monstro.moveTargetPos.x, _monstro.moveTargetPos.y);
		if (_monstro.x > _monstro.moveTargetPos.x) _monstro.isLeft = true;
		else _monstro.isLeft = false;
		
		if (_monstro.moveDistance > 300)
		{
			_monstro.state = MONSTROSTATE_JUMP;
		}
		else
		{
			if (_monstro.randomPattern == 0)
			{
				if (_monstro.moveDistance < 100)_monstro.state = MONSTROSTATE_FIRE;
				else _monstro.state = MONSTROSTATE_MOVE;
			}
			else
			{
				_monstro.state = MONSTROSTATE_FIRE;
			}
		}
		_monstro.randomPattern = RND->getInt(2);
		_monstro.restTime = 100;
	}
}

void monstro::bulletHit(float damage)
{
	_monstro.hp-= damage;
	if(_monstro.hp < 0)	_monstro.state = MONSTROSTATE_DIE;
}
