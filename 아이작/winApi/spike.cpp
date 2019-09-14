#include "stdafx.h"
#include "spike.h"

HRESULT spikeSmall::init(float x, float y)
{
	_spike.img = IMAGEMANAGER->addFrameImage("spikeSmall", "image/mapObject/spikeSmall.bmp", 64, 320, 1, 5, true, RGB(255, 0, 255));
	_spike.x = x;
	_spike.y = y;
	_spike.rc = RectMakeCenter(_spike.x, _spike.y, _spike.img->getFrameWidth(), _spike.img->getFrameHeight());
	_spike.count = 0.0f;
	_spike.currentY = 0;
	_spike.startTime = 200;
	_spike.endTime = 50;
	return S_OK;
}

void spikeSmall::release(void)
{
}

void spikeSmall::update(void)
{
	_spike.startTime--;
	frame();
}

void spikeSmall::render(void)
{
	_spike.img->frameRender(getMemDC(), _spike.rc.left - CAMERAMANAGER->getX(), _spike.rc.top - CAMERAMANAGER->getY(), 1, _spike.currentY);
}

void spikeSmall::frame(void)
{
	if (_spike.startTime < 0)
	{
		if (_spike.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_spike.count = TIMEMANAGER->getWorldTime();
			_spike.currentY++;
			if (_spike.currentY > _spike.img->getMaxFrameY())
			{
				_spike.currentY = _spike.img->getMaxFrameY();
				_spike.endTime--;
				if (_spike.endTime < 0)
				{
					_spike.currentY = 0;
					_spike.startTime = 200;
					_spike.endTime = 50;
				}
			}
		}
	}
}

HRESULT spikeLarge::init(float x, float y)
{
	_spike.img = IMAGEMANAGER->addFrameImage("spikeLarge", "image/mapObject/spikeLarge.bmp", 64, 320, 1, 5, true, RGB(255, 0, 255));
	_spike.x = x;
	_spike.y = y;
	_spike.rc = RectMakeCenter(_spike.x, _spike.y, _spike.img->getFrameWidth(), _spike.img->getFrameHeight());
	_spike.count = 0.0f;
	_spike.currentY = 0;
	_spike.startTime = 200;
	_spike.endTime = 50;
	return S_OK;
}

void spikeLarge::release(void)
{
}

void spikeLarge::update(void)
{
	_spike.startTime--;
	frame();
}

void spikeLarge::render(void)
{
	_spike.img->frameRender(getMemDC(), _spike.rc.left - CAMERAMANAGER->getX(), _spike.rc.top - CAMERAMANAGER->getY(), 1, _spike.currentY);
}

void spikeLarge::frame(void)
{
	if (_spike.startTime < 0)
	{
		if (_spike.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_spike.count = TIMEMANAGER->getWorldTime();
			_spike.currentY++;
			if (_spike.currentY > _spike.img->getMaxFrameY())
			{
				_spike.currentY = _spike.img->getMaxFrameY();
				_spike.endTime--;
				if (_spike.endTime < 0)
				{
					_spike.currentY = 0;
					_spike.startTime = 200;
					_spike.endTime = 50;
				}
			}
		}
	}
}
