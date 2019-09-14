#include "stdafx.h"
#include "frowningGaper.h"

HRESULT frowningGaper::init(float x, float y)
{
	_body.state = GAPERBODYSTATE_CENTER;
	_body.img = IMAGEMANAGER->addFrameImage("monsterBody", "image/enemy/main/monsterBody.bmp", 640, 192, 10, 3, true, RGB(255, 0, 255));
	_body.x = x;
	_body.y = y;
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.img->getFrameWidth(), _body.img->getFrameHeight());
	_body.currentX = 0;
	_body.currentY = 0;
	_body.angle = 0.0f;
	_body.speed = 1.4f;
	_body.count = 0.0f;
	//체력 수정 필요
	_body.hp = 4.0f;
	_head.img = IMAGEMANAGER->addFrameImage("frowningGaperHead", "image/enemy/main/frowningGaper.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	_head.x = _body.x;
	_head.y = _body.y - _body.img->getFrameHeight() / 2;
	_head.rc = RectMakeCenter(_head.x, _head.y, _head.img->getFrameWidth(), _head.img->getFrameHeight());
	_head.currentX = 0;
	_head.count = 0.0f;
	_playerChase = false;
	_horfRandomSpwanValue = RND->getInt(10);
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	return S_OK;
}

void frowningGaper::release(void)
{
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void frowningGaper::update(void)
{
}

void frowningGaper::render(void)
{
	_shadow->render();
	draw();
}

void frowningGaper::move(float x, float y)
{

	if (getDistance(_body.x,_body.y, x, y) < 250)
	{
		_playerChase = true;
	}
	frameBody();
	_body.angle = getAngle(_body.x, _body.y, x, y);
	_body.x += cosf(_body.angle) * _body.speed;
	_body.y -= sinf(_body.angle) * _body.speed;

	_head.x = _body.x;
	_head.y = _body.y - _body.img->getFrameHeight() / 2;
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.img->getFrameWidth(), _body.img->getFrameHeight());
	_head.rc = RectMakeCenter(_head.x, _head.y, _head.img->getFrameWidth(), _head.img->getFrameHeight());
	
	if (_playerChase)
	{
		if (_body.rc.left > x)
		{
			_body.state = GAPERBODYSTATE_LEFT;
		}
		else if (_body.rc.right < x)
		{
			_body.state = GAPERBODYSTATE_RIGHT;
		}
		else
		{
			_body.state = GAPERBODYSTATE_CENTER;
		}
		frameHead();
	}
	_shadow->update(_body.rc.left + 5, _body.rc.top + 30);
}

void frowningGaper::draw(void)
{
	_body.img->frameRender(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), _body.rc.top - CAMERAMANAGER->getY(), _body.currentX, _body.currentY);
	_head.img->frameRender(getMemDC(), _head.rc.left - CAMERAMANAGER->getX(), _head.rc.top - CAMERAMANAGER->getY(), _head.currentX, 0);
}

void frowningGaper::frameBody(void)
{
	if (_body.state == GAPERBODYSTATE_CENTER)
	{
		_body.currentY = 0;
	}
	else if (_body.state == GAPERBODYSTATE_LEFT)
	{
		_body.currentY = 2;
	}
	else if (_body.state == GAPERBODYSTATE_RIGHT)
	{
		_body.currentY = 1;
	}
	if (_body.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_body.count = TIMEMANAGER->getWorldTime();
		_body.currentX++;
		if (_body.currentX > _body.img->getMaxFrameX())
		{
			_body.currentX = 0;
		}
	}
}

void frowningGaper::frameHead(void)
{
	if (_head.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_head.count = TIMEMANAGER->getWorldTime() + 0.18f;
		if (_head.currentX <= _head.img->getMaxFrameX())
		{
			_head.currentX++;
			if (_head.currentX > _head.img->getMaxFrameX())
			{
				_head.currentX = _head.img->getMaxFrameX();
			}
		}
	}
}

void frowningGaper::bulletHit(float angle, float damage)
{
	_body.x += cosf(angle)*_body.speed * 5;
	_body.y -= sinf(angle)*_body.speed * 5;
	_head.x = _body.x;
	_head.y = _body.y - _body.img->getFrameHeight() / 2;
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.img->getFrameWidth(), _body.img->getFrameHeight());
	_head.rc = RectMakeCenter(_head.x, _head.y, _head.img->getFrameWidth(), _head.img->getFrameHeight());
	_body.hp-= damage;
}
