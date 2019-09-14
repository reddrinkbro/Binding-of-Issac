#include "stdafx.h"
#include "miniMap.h"

HRESULT miniMap::init(void)
{
	_bgBlack = IMAGEMANAGER->addImage("bgBlack", "image/miniMap/bgblack.bmp", 640, 640);
	_x = WINSIZEX / 2 - _bgBlack->getWidth() / 2;
	_y = WINSIZEY / 2 - _bgBlack->getHeight() / 2;
	return S_OK;
}

void miniMap::release(void)
{
}

void miniMap::update(void)
{
}

void miniMap::render(void)
{
	_bgBlack->alphaRender(getMemDC(), _x , _y, 75);
	for (_viProgress = _vProgress.begin(); _viProgress != _vProgress.end(); ++_viProgress)
	{
		_viProgress->img->render(getMemDC(), _viProgress->x, _viProgress->y);
	}
}

void miniMap::addMap(int index)
{
	progress _progress;
	ZeroMemory(&_progress, sizeof(progress));
	_progress.img = new image;
	_progress.img->init("image/miniMap/progress2.bmp", _bgBlack->getWidth() / 8 + 8, _bgBlack->getHeight() / 12 + 12);
	_progress.index = index;
	_progress.x = ((_progress.index % TILEX) + _bgBlack->getWidth() * (_progress.index % TILEX)) / TILEX + _x;
	_progress.y = ((_progress.index / TILEY) + _bgBlack->getHeight() * (_progress.index / TILEY) )/ TILEY + _y;
	_progress._progressState = PROGRESSSTATE_NONE;
	_vProgress.push_back(_progress);
}

void miniMap::addMap(int leftTop, int rightTop, int bottom)
{
	progress _progress;
	ZeroMemory(&_progress, sizeof(progress));
	_progress.img = new image;
	_progress.img->init("image/miniMap/progress2.bmp", rightTop * _bgBlack->getWidth() / TILEX + 8 , bottom * _bgBlack->getHeight() / TILEY + 10);
	_progress.index = leftTop;
	_progress.x = ((_progress.index % TILEX) + _bgBlack->getWidth() * (_progress.index % TILEX)) / TILEX + _x;
	_progress.y = (_progress.index / TILEX) * _bgBlack->getHeight() / TILEY  + _y ;
	_progress._progressState = PROGRESSSTATE_NONE;
	_vProgress.push_back(_progress);
}

void miniMap::deleteMap(int index)
{
	for (_viProgress = _vProgress.begin(); _viProgress != _vProgress.end(); )
	{
		if (_viProgress->index == index)
		{
			_vProgress.erase(_viProgress);
			break;
		}
		else
		{
			++_viProgress;
		}
	}
}
