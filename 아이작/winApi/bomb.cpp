#include "stdafx.h"
#include "bomb.h"

HRESULT bomb::init(float x, float y, bool isInChest)
{
	EFFECTMANAGER->addEffect("explosionEffect", "image/effect/explosionEffect.bmp", 1920, 160, 160, 160, 14, 1);
	_bomb.img = IMAGEMANAGER->addFrameImage("bomb", "image/item/bomb.bmp", 408, 64, 6, 1, true, RGB(255, 0, 255));
	_bomb.x = x;
	_bomb.y = y;
	_bomb.rc = RectMakeCenter(_bomb.x, _bomb.y, _bomb.img->getFrameWidth(), _bomb.img->getFrameHeight());
	_bomb.count = 0.0f;
	_bomb.currnetX = 0;
	if(isInChest) _bomb.speed = 0.6f;
	else _bomb.speed = 0.0f;
	_bomb.time = 200;
	_bomb.angle = PI/3;
	_bomb.isInstall = false;
	_bomb.isInChest = isInChest;
	_bomb.distance = 100;
	_bomb.isMove = true;

	_gravity = -2.0f;
	_currnetAnlgeValue = PI / 2;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void bomb::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void bomb::update(void)
{
}

void bomb::render(void)
{
	draw();
}

void bomb::draw(void)
{
	_shadow->render();
	_bomb.img->frameRender(getMemDC(), _bomb.rc.left - CAMERAMANAGER->getX(), _bomb.rc.top - CAMERAMANAGER->getY(), _bomb.currnetX, 0);
}

void bomb::frame(void)
{
	_bomb.time--;
	if (_bomb.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_bomb.count = TIMEMANAGER->getWorldTime();
		_bomb.currnetX++;
		if(_bomb.currnetX > _bomb.img->getMaxFrameX())
		{ 
			_bomb.currnetX = 1;
		}
	}
}

void bomb::drop(void)
{	
	_bomb.distance--;
	if (_bomb.distance > 0)
	{
		if (_bomb.isInChest)
		{
			_gravity += 0.05f;
		}
		else
		{
			_gravity += 0.045f;
		}
		_bomb.x += cosf(_bomb.angle + _currnetAnlgeValue) * _bomb.speed;
		_bomb.y -= sinf(_bomb.angle + _currnetAnlgeValue) * _bomb.speed - _gravity;
		_bomb.rc = RectMakeCenter(_bomb.x, _bomb.y, _bomb.img->getFrameWidth(), _bomb.img->getFrameHeight());
	}
	else
	{
		_shadow->update(_bomb.x - 28, _bomb.y + 20);
		SOUNDMANAGER->stop("bomb");
		_bomb.isMove = false;
	}
	
}
