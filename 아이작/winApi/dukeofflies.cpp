#include "stdafx.h"
#include "dukeofflies.h"

HRESULT dukeofflies::init(float x, float y)
{
	_dukeofflies.img = IMAGEMANAGER->addFrameImage("dukeofflies", "image/enemy/boss/dukeofflies.bmp", 1400, 480, 7, 3, true, RGB(255, 0, 255));
	_dukeofflies.x = x;
	_dukeofflies.y = y;
	_dukeofflies.rc = RectMakeCenter(_dukeofflies.x, _dukeofflies.y, _dukeofflies.img->getFrameWidth(), _dukeofflies.img->getFrameHeight());
	_dukeofflies.currentX = 0;
	_dukeofflies.currentY = 0;
	_dukeofflies.count = 0.0f;
	_dukeofflies.maxHp = 20.0f;
	_dukeofflies.hp = _dukeofflies.maxHp;
	_dukeofflies.angle = PI / 4;
	_dukeofflies.speed = 0.3f;
	_dukeofflies.state = DUKEOFFLIESSTATE_NONE;
	_dukeofflies.randomPattern = RND->getInt(2);
	_dukeofflies.restTime = 150;
	_dukeofflies.isSpawn = false;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_LARGE);
	_hpBar = new progressBar;
	_hpBar->init("image/UI/bossHpBarTop", "image/UI/bossHpBarBottom", CAMERAMANAGER->getGameMaxRenderX() / 2 - 129, 0, 258, 36);
	
	EFFECTMANAGER->addEffect("largeBloodEffect", "image/enemy/effect/largeBloodEffect.bmp", 3360, 166, 280, 166, 14, 1);
	return S_OK;
}

void dukeofflies::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void dukeofflies::update(void)
{
	_hpBar->setGauge(_dukeofflies.hp, _dukeofflies.maxHp);
	_hpBar->update();
	move();
	if (_dukeofflies.restTime < 0)
	{
		frame();
	}
	else
	{
		_dukeofflies.currentY = 0;
		_dukeofflies.restTime--;
		_dukeofflies.state = DUKEOFFLIESSTATE_NONE;
	}
	_shadow->update(_dukeofflies.x - 60, _dukeofflies.y + 50);
}

void dukeofflies::render(void)
{
	_hpBar->render();
	_shadow->render();
	draw();
}

void dukeofflies::move(void)
{
	_dukeofflies.x += cosf(_dukeofflies.angle)* _dukeofflies.speed;
	_dukeofflies.y -= sinf(_dukeofflies.angle)* _dukeofflies.speed;
	_dukeofflies.rc = RectMakeCenter(_dukeofflies.x, _dukeofflies.y, _dukeofflies.img->getFrameWidth(), _dukeofflies.img->getFrameHeight());
}

void dukeofflies::draw(void)
{
	_dukeofflies.img->frameRender(getMemDC(), _dukeofflies.rc.left - CAMERAMANAGER->getX(), _dukeofflies.rc.top - CAMERAMANAGER->getY(), _dukeofflies.currentX, _dukeofflies.currentY);
}

void dukeofflies::frame(void)
{
	
	if (_dukeofflies.randomPattern == 0)
	{
		_dukeofflies.state = DUKEOFFLIESSTATE_SPAWNONE;
	}
	else
	{
		_dukeofflies.state = DUKEOFFLIESSTATE_SPAWNTWO;
	}

	if (_dukeofflies.state == DUKEOFFLIESSTATE_SPAWNONE)
	{
		_dukeofflies.currentY = 2;
	}
	else
	{
		_dukeofflies.currentY = 1;
	}
	if (_dukeofflies.count + FRAMECOUNT< TIMEMANAGER->getWorldTime() && _dukeofflies.state != DUKEOFFLIESSTATE_NONE)
	{
		if (_dukeofflies.currentX == 0)
		{
			SOUNDMANAGER->stop("duke spawn two");
			SOUNDMANAGER->stop("duke spawn one");
		}
		if (_dukeofflies.currentX != 1) _dukeofflies.count = TIMEMANAGER->getWorldTime();
		else _dukeofflies.count = TIMEMANAGER->getWorldTime() + 0.45f;
		_dukeofflies.currentX++;
		if (_dukeofflies.currentX == 4)
		{
			_dukeofflies.isSpawn = true;
			if (_dukeofflies.state == DUKEOFFLIESSTATE_SPAWNTWO)
			{
				EFFECTMANAGER->play("monsterSpawnLarge", _dukeofflies.x - CAMERAMANAGER->getX(), _dukeofflies.y - CAMERAMANAGER->getY());
				SOUNDMANAGER->play("duke spawn two", VOLUME->getSfxVolume() / 10);
			}
			else if (_dukeofflies.state == DUKEOFFLIESSTATE_SPAWNONE)
			{
				SOUNDMANAGER->play("duke spawn one", VOLUME->getSfxVolume() / 10);
			}
		}
		if (_dukeofflies.currentX > _dukeofflies.img->getMaxFrameX())
		{
			_dukeofflies.currentX = 0;
			_dukeofflies.state = DUKEOFFLIESSTATE_NONE;
			_dukeofflies.randomPattern = RND->getInt(2);
			_dukeofflies.restTime = 150;
		}
	}
	
}

void dukeofflies::angleChange(void)
{
	_dukeofflies.angle += PI/4;
}

void dukeofflies::bulletHit(float angle, float damage)
{
	_dukeofflies.x += cosf(angle)*_dukeofflies.speed *10;
	_dukeofflies.y -= sinf(angle)*_dukeofflies.speed *10;
	_dukeofflies.rc = RectMakeCenter(_dukeofflies.x, _dukeofflies.y, _dukeofflies.img->getFrameWidth(), _dukeofflies.img->getFrameHeight());
	_dukeofflies.hp -= damage;
}
