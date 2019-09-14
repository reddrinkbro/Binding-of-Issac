#include "stdafx.h"
#include "shadow.h"

HRESULT shadow::init(SHADOWSIZE size)
{
	if(size == SHADOWSIZE_SMALL) _img = IMAGEMANAGER->addImage("shadowSmall", "image/shadow/shadowSmall.bmp", 40, 17, true, RGB(255, 0, 255));
	else if (size == SHADOWSIZE_MEDIUM) _img = IMAGEMANAGER->addImage("shadowMedium", "image/shadow/shadowMedium.bmp", 54, 23, true, RGB(255, 0, 255));
	else _img = IMAGEMANAGER->addImage("shadowLarge", "image/shadow/shadowLarge.bmp", 120, 51, true, RGB(255, 0, 255));
	_alpha = 20;
	_x = 0;
	_y = 0;
	return S_OK;
}

void shadow::release(void)
{
}

void shadow::update(float x, float y)
{
	_x = x;
	_y = y;
}

void shadow::render(void)
{
	_img->alphaRender(getMemDC(), _x - CAMERAMANAGER->getX(), _y - CAMERAMANAGER->getY(), _alpha);
}
