#include "stdafx.h"
#include "coin.h"

HRESULT coin::init(float x, float y)
{
	_coin.img = IMAGEMANAGER->addFrameImage("coin", "image/item/coin.bmp", 384, 64, 8, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("coinGet", "image/effect/coinGet.bmp", 680, 80, 85, 80, 14, 3);
	_coin.x = x;
	_coin.y = y;
	_coin.rc = RectMakeCenter(_coin.x, _coin.y, _coin.img->getFrameWidth(), _coin.img->getFrameHeight());
	_coin.count = 0;
	_coin.currnetX = 0;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void coin::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void coin::update(void)
{
	frame();
}

void coin::render(void)
{
	_shadow->render();
	draw();
}

void coin::draw(void)
{
	_coin.img->frameRender(getMemDC(), _coin.rc.left - CAMERAMANAGER->getX(), _coin.rc.top - CAMERAMANAGER->getY(), _coin.currnetX, 0);
}

void coin::frame(void)
{
	if (_coin.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_coin.count = TIMEMANAGER->getWorldTime();
		_coin.currnetX++;
		if (_coin.currnetX > _coin.img->getMaxFrameX())
		{
			_shadow->update(_coin.x - 20, _coin.y + 15);
			_coin.currnetX = _coin.img->getMaxFrameX();
		}
	}
}
