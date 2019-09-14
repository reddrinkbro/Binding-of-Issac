#include "stdafx.h"
#include "familiar.h"

HRESULT familiar::init(float x, float y)
{
	_familiar.img = IMAGEMANAGER->addFrameImage("familiar", "image/item/ghostbabyFamiliiar.bmp", 108, 216, 2, 4, true, RGB(255, 0, 255));
	_familiar.x = _familiar.centerX= x;
	_familiar.y = _familiar.centerY = y;
	_familiar.count = 0.0f;
	_familiar.currentX = 0;
	_familiar.currentY = 0;
	_familiar.state = FAMILIARSTATE_DOWN;
	_familiar.isFire = false;
	_bullet = new familiarBullet;
	_bullet->init(350);
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_SMALL);
	return S_OK;
}

void familiar::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void familiar::update(void)
{
	_shadow->update(_familiar.x + 5, _familiar.y + 50);
	frame();
	_bullet->update();
}

void familiar::render(void)
{
	_shadow->render();
	draw();
	_bullet->render();

}

void familiar::draw(void)
{
	_familiar.img->frameRender(getMemDC(), _familiar.x - CAMERAMANAGER->getX(), _familiar.y - CAMERAMANAGER->getY(), _familiar.currentX, _familiar.currentY);
}

void familiar::move(float x, float y, float speed)
{
	_familiar.centerX = x;
	_familiar.centerY = y;
	_familiar.speed = speed;
	float angle = getAngle(_familiar.x, _familiar.y, _familiar.centerX, _familiar.centerY);
	float distance = getDistance(_familiar.x, _familiar.y, _familiar.centerX, _familiar.centerY);
	if (distance > 45)
	{
		_familiar.x += cosf(angle) * _familiar.speed;
		_familiar.y -= sinf(angle) * _familiar.speed;
	}
}

void familiar::fire(void)
{
	switch (_familiar.state)
	{
	case FAMILIARSTATE_UP:
		_bullet->fire(_familiar.x + 20, _familiar.y + 10, 4.0f, BULLETDIRECTION_UP);
		break;
	case FAMILIARSTATE_DOWN:
		_bullet->fire(_familiar.x + 20, _familiar.y + 10, 4.0f, BULLETDIRECTION_DOWN);
		break;
	case FAMILIARSTATE_LEFT:
		_bullet->fire(_familiar.x + 20, _familiar.y + 10, 4.0f, BULLETDIRECTION_LEFT);
		break;
	case FAMILIARSTATE_RIGHT:
		_bullet->fire(_familiar.x + 20, _familiar.y + 10, 4.0f, BULLETDIRECTION_RIGHT);
		break;
	}
}

void familiar::frame(void)
{
	switch (_familiar.state)
	{
		_familiar.currentX = 1;
	case FAMILIARSTATE_UP:
		_familiar.currentY = 2;
		break;
	case FAMILIARSTATE_DOWN:
		_familiar.currentY = 0;
		break;
	case FAMILIARSTATE_LEFT:
		_familiar.currentY = 3;
		break;
	case FAMILIARSTATE_RIGHT:
		_familiar.currentY = 1;
		break;
	}
}
