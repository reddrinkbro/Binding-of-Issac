#include "stdafx.h"
#include "tilesPaper.h"

HRESULT tilesPaper::init(int tileSize, int objectSize, int propsSize)
{
	
	//타일 페이퍼 init
	_paper.img = IMAGEMANAGER->addFrameImage("paper", "image/tilesPaper/paper.bmp", 800, 2400, 1, 3, true, RGB(255, 0, 255));
	_paper.x = WINSIZEX - _paper.img->getFrameWidth() / 2;
	_paper.y = _paper.img->getFrameHeight() / 2;
	_paper.currentFrameY = 0;
	_paper.rc = RectMakeCenter(_paper.x, _paper.y, _paper.img->getFrameWidth(), _paper.img->getFrameHeight());
	_paper.count = 0;
	_paper.isOn = false;
	_paper.zOrder = 1;
	_paper.tileIndex = 0;
	_paper.objectIndex = 0;
	_paper.propsIndex = 0;
	_paper.monsterIndex = 0;
	_paper.itemIndex = 0;
	//옆에 버튼 init
	_notice[0].img = IMAGEMANAGER->addFrameImage("tileNotice","image/tilesPaper/tileNotice.bmp", 210, 81,2,1, true, RGB(255, 0, 255));
	_notice[1].img = IMAGEMANAGER->addFrameImage("objectNotice", "image/tilesPaper/objectNotice.bmp", 210, 81, 2, 1, true, RGB(255, 0, 255));
	_notice[2].img = IMAGEMANAGER->addFrameImage("propstNotice", "image/tilesPaper/propstNotice.bmp", 210, 81, 2, 1, true, RGB(255, 0, 255));
	_notice[3].img = IMAGEMANAGER->addFrameImage("monsterNotice", "image/tilesPaper/monsterNotice.bmp", 210, 81, 2, 1, true, RGB(255, 0, 255));
	_notice[4].img = IMAGEMANAGER->addFrameImage("itemNotice", "image/tilesPaper/itemNotice.bmp", 210, 81, 2, 1, true, RGB(255, 0, 255));
	_notice[5].img = IMAGEMANAGER->addFrameImage("optionNotice", "image/tilesPaper/optionNotice.bmp", 210, 81, 2, 1, true, RGB(255, 0, 255));
	for (int i = 0; i < 3; i++)
	{
		_notice[i].x = _paper.x - _paper.img->getWidth() / 2 +30;
		_notice[i].y = _paper.y - _paper.img->getFrameHeight() / 3 + i * 100;
		_notice[i].rc = RectMakeCenter(_notice[i].x, _notice[i].y, _notice[i].img->getFrameWidth(), _notice[i].img->getFrameHeight());
		if (i == 0) _notice[i].currentX = 1;
		else _notice[i].currentX = 0;
	}
	for (int i = 3; i < 6; i++)
	{
		_notice[i].x = _paper.x - _paper.img->getWidth() / 2 + 30;
		_notice[i].y = _paper.y - _paper.img->getFrameHeight() / 3 + 320 + (i - 3) * 100;
		_notice[i].rc = RectMakeCenter(_notice[i].x, _notice[i].y, _notice[i].img->getFrameWidth(), _notice[i].img->getFrameHeight());
		_notice[i].currentX = 0;
	}
	//상점 모드
	_shopMode.img = IMAGEMANAGER->addFrameImage("shopButton", "image/tilesPaper/shopButton.bmp", 230, 64, 2, 1, true, RGB(255, 0, 255));
	_shopMode.x = _paper.x;
	_shopMode.y = _paper.y + _paper.img->getFrameHeight() / 2 - _shopMode.img->getFrameHeight() * 1.8f;
	_shopMode.rc = RectMakeCenter(_shopMode.x, _shopMode.y, _shopMode.img->getFrameWidth(), _shopMode.img->getFrameHeight());
	_shopMode.currentX = 0;
	_shopMode.isOn = false;

	//드래그 모드 init
	_dragMode.img = IMAGEMANAGER->addFrameImage("dragNotice", "image/tilesPaper/dragNotice.bmp", 230, 64, 2, 1, true, RGB(255, 0, 255));
	_dragMode.x = _shopMode.x - _dragMode.img->getWidth() ;
	_dragMode.y = _shopMode.y;
	_dragMode.rc = RectMakeCenter(_dragMode.x, _dragMode.y, _dragMode.img->getFrameWidth(), _dragMode.img->getFrameHeight());
	_dragMode.currentX = 0;
	_dragMode.isOn = false;

	//지우개 모드 init
	_eraseMode.img = IMAGEMANAGER->addFrameImage("eraseNotice", "image/tilesPaper/eraseNotice.bmp", 230, 64, 2, 1, true, RGB(255, 0, 255));
	_eraseMode.x = _shopMode.x + _eraseMode.img->getWidth();
	_eraseMode.y = _shopMode.y;
	_eraseMode.rc = RectMakeCenter(_eraseMode.x, _eraseMode.y, _eraseMode.img->getFrameWidth(), _eraseMode.img->getFrameHeight());
	_eraseMode.currentX = 0;
	_eraseMode.isOn = false;

	//화살표 init
	_arrow[0].img = IMAGEMANAGER->addImage("leftArrow", "image/tilesPaper/leftArrow.bmp", 64, 48, true, RGB(255, 0, 255));
	_arrow[0].rc = RectMakeCenter(_paper.rc.left + _arrow[0].img->getWidth(), _paper.y , _arrow[0].img->getWidth(), _arrow[0].img->getHeight());
	_arrow[1].img = IMAGEMANAGER->addImage("rightArrow", "image/tilesPaper/rightArrow.bmp", 64, 48, true, RGB(255, 0, 255));
	_arrow[1].rc = RectMakeCenter(_paper.rc.right - _arrow[1].img->getWidth(), _paper.y, _arrow[1].img->getWidth(), _arrow[1].img->getHeight());

	//로드
	_load.img = IMAGEMANAGER->addImage("load", "image/tilesPaper/load.bmp", 192, 192, true, RGB(255, 0, 255));
	_load.x = _paper.x;
	_load.y = _paper.y;
	_load.rc = RectMakeCenter(_load.x, _load.y, _load.img->getWidth(), _load.img->getHeight());
	_load.isOn = false;

	//세이브
	_save.img = IMAGEMANAGER->addImage("save", "image/tilesPaper/save.bmp", 192, 192, true, RGB(255, 0, 255));
	_save.x = _load.rc.left - _save.img->getWidth() / 2;
	_save.y = _paper.y;
	_save.rc = RectMakeCenter(_save.x, _save.y, _save.img->getWidth(), _save.img->getHeight());
	_save.isOn = false;
	
	//뒤로가기
	_back.img = IMAGEMANAGER->addImage("back", "image/tilesPaper/back.bmp", 192, 192, true, RGB(255, 0, 255));
	_back.x = _load.rc.right + _back.img->getWidth() / 2 ;
	_back.y = _paper.y;
	_back.rc = RectMakeCenter(_back.x, _back.y, _back.img->getWidth(), _back.img->getHeight());

	_tileSize = tileSize;
	_objectSize = objectSize;
	_propsSize = propsSize;
	_tileStyle = TILESTYLE_TERRAIN;
	return S_OK;
}

void tilesPaper::release(void)
{
}

void tilesPaper::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_paper.isOn) _paper.isOn = true;
		else
		{
			_paper.currentFrameY = 0;
			_paper.isOn = false;
		}
	}
	if (_paper.isOn) paperOn();
}

void tilesPaper::render(void)
{
	if (_paper.isOn) _paper.img->frameRender(getMemDC(), _paper.rc.left, _paper.rc.top, 0, _paper.currentFrameY);
	if (_paper.currentFrameY == _paper.img->getMaxFrameY())
	{
		for (int i = 0; i < 6; i++)
		{
			_notice[i].img->frameRender(getMemDC(), _notice[i].rc.left, _notice[i].rc.top, _notice[i].currentX, 0);
		}
		if (_tileStyle == TILESTYLE_TERRAIN)
		{
			_dragMode.img->frameRender(getMemDC(), _dragMode.rc.left, _dragMode.rc.top, _dragMode.currentX, 0);
			_shopMode.img->frameRender(getMemDC(), _shopMode.rc.left, _shopMode.rc.top, _shopMode.currentX, 0);
			if (_paper.tileIndex > 0) _arrow[0].img->render(getMemDC(), _arrow[0].rc.left, _arrow[0].rc.top);
			if (_paper.tileIndex < _tileSize - 1) _arrow[1].img->render(getMemDC(), _arrow[1].rc.left, _arrow[1].rc.top);
		}
		else if (_tileStyle == TILESTYLE_OBJECT)
		{
			if (_paper.objectIndex > 0) _arrow[0].img->render(getMemDC(), _arrow[0].rc.left, _arrow[0].rc.top);
			if (_paper.objectIndex < _objectSize - 1) _arrow[1].img->render(getMemDC(), _arrow[1].rc.left, _arrow[1].rc.top);
		}
		else if (_tileStyle == TILESTYLE_PROPS)
		{
			if (_paper.propsIndex > 0) _arrow[0].img->render(getMemDC(), _arrow[0].rc.left, _arrow[0].rc.top);
			if (_paper.propsIndex < _propsSize - 1) _arrow[1].img->render(getMemDC(), _arrow[1].rc.left, _arrow[1].rc.top);
		}
		if(_tileStyle != TILESTYLE_NONE) _eraseMode.img->frameRender(getMemDC(), _eraseMode.rc.left, _eraseMode.rc.top, _eraseMode.currentX, 0);
		else
		{
			_save.img->render(getMemDC(), _save.rc.left, _save.rc.top);
			_load.img->render(getMemDC(), _load.rc.left, _load.rc.top);
			_back.img->render(getMemDC(), _back.rc.left, _back.rc.top);
		}
	}
}

void tilesPaper::paperOn(void)
{
	_paper.count++;
	if (_paper.count % 7 == 0)
	{
		_paper.currentFrameY++;
		if (_paper.currentFrameY >= _paper.img->getMaxFrameY())
		{
			_paper.currentFrameY = _paper.img->getMaxFrameY();
		}
	}
}

void tilesPaper::arrowClick(void)
{
	//왼쪽 화살표
	if (!_paper.isOn || _tileStyle == TILESTYLE_NONE || _tileStyle == TILESTYLE_MONSTER || _tileStyle == TILESTYLE_ITEM)return;
	if (_paper.isOn && _tileStyle == TILESTYLE_TERRAIN)
	{
		if (PtInRect(&_arrow[0].rc, _ptMouse))
		{
			if (_paper.tileIndex > 0)
			{
				_paper.tileIndex--;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
		//오른쪽 화살표
		else if (PtInRect(&_arrow[1].rc, _ptMouse))
		{
			if (_paper.tileIndex < _tileSize - 1)
			{
				_paper.tileIndex++;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
	}
	else if (_paper.isOn && _tileStyle == TILESTYLE_OBJECT)
	{
		if (PtInRect(&_arrow[0].rc, _ptMouse))
		{
			if (_paper.objectIndex > 0)
			{
				_paper.objectIndex--;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
		//오른쪽 화살표
		else if (PtInRect(&_arrow[1].rc, _ptMouse))
		{
			if (_paper.objectIndex < _objectSize - 1)
			{
				_paper.objectIndex++;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
	}
	else if (_paper.isOn && _tileStyle == TILESTYLE_PROPS)
	{
		if (PtInRect(&_arrow[0].rc, _ptMouse))
		{
			if (_paper.propsIndex > 0)
			{
				_paper.propsIndex--;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
		//오른쪽 화살표
		else if (PtInRect(&_arrow[1].rc, _ptMouse))
		{
			if (_paper.propsIndex < _propsSize - 1)
			{
				_paper.propsIndex++;
				_paper.currentFrameY = 0;
				this->paperOn();
			}
		}
	}
}

void tilesPaper::dragMode(void)
{
	if (_tileStyle != TILESTYLE_TERRAIN)
	{
		_dragMode.currentX = 0;
		_dragMode.isOn = false;
		return;
	}
	if (PtInRect(&_dragMode.rc, _ptMouse) && _paper.isOn)
	{
		if (_eraseMode.isOn)
		{
			_eraseMode.currentX = 0;
			_eraseMode.isOn = false;
		}
		if (_shopMode.isOn)
		{
			_shopMode.currentX = 0;
			_shopMode.isOn = false;
		}
		if (!_dragMode.isOn)
		{
			_dragMode.currentX = 1;
			_dragMode.isOn = true;
		}
		else
		{
			_dragMode.currentX = 0;
			_dragMode.isOn = false;
		}
	}
}

void tilesPaper::usingErase(void)
{
	if (PtInRect(&_eraseMode.rc, _ptMouse) && _paper.isOn)
	{
		if (_dragMode.isOn)
		{
			_dragMode.currentX = 0;
			_dragMode.isOn = false;
		}
		if (_shopMode.isOn)
		{
			_shopMode.currentX = 0;
			_shopMode.isOn = false;
		}
		if (!_eraseMode.isOn)
		{
			_eraseMode.currentX = 1;
			_eraseMode.isOn = true;
		}
		else
		{
			_eraseMode.currentX = 0;
			_eraseMode.isOn = false;
		}
	}
}

void tilesPaper::saveLoad(void)
{
	if (PtInRect(&_save.rc, _ptMouse) && _paper.isOn)
	{
		_save.isOn = true;
	}
	else if (PtInRect(&_load.rc, _ptMouse) && _paper.isOn)
	{
		_load.isOn = true;
	}
}

void tilesPaper::shopMode(void)
{
	if (_tileStyle != TILESTYLE_TERRAIN)
	{
		_shopMode.currentX = 0;
		_shopMode.isOn = false;
		return;
	}
	if (PtInRect(&_shopMode.rc, _ptMouse) && _paper.isOn)
	{
		if (_eraseMode.isOn)
		{
			_eraseMode.currentX = 0;
			_eraseMode.isOn = false;
		}
		if (_dragMode.isOn)
		{
			_dragMode.currentX = 0;
			_dragMode.isOn = false;
		}
		if (!_shopMode.isOn)
		{
			_shopMode.currentX = 1;
			_shopMode.isOn = true;
		}
		else
		{
			_shopMode.currentX = 0;
			_shopMode.isOn = false;
		}
	}
}

void tilesPaper::back(void)
{
	if (_tileStyle == TILESTYLE_NONE)
	{
		if (PtInRect(&_back.rc, _ptMouse) && _paper.isOn)
		{
			SCENEMANAGER->changeScene("메뉴");
		}
	}
}

//처음으로 다시 초기화
void tilesPaper::paperUp(void)
{
	_paper.currentFrameY = 0;
	//_paper.isOn = false;
	_paper.tileIndex = 0;
	_paper.objectIndex = 0;
	_dragMode.currentX = 0;
	_dragMode.isOn = false;
	_eraseMode.currentX = 0;
	_eraseMode.isOn = false;
	_shopMode.currentX = 0;
	_shopMode.isOn = false;
	_save.isOn = false;
	_load.isOn = false;
	_notice[0].currentX = 1;
	for (int i = 1; i < 6; i++)
	{
		_notice[i].currentX = 0;
	}
	_tileStyle = TILESTYLE_TERRAIN;
}

void tilesPaper::selectStyle(void)
{
	if (PtInRect(&_notice[0].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_TERRAIN)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[0].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 0) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_TERRAIN;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
	else if (PtInRect(&_notice[1].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_OBJECT)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[1].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 1) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_OBJECT;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
	else if (PtInRect(&_notice[2].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_PROPS)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[2].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 2) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_PROPS;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
	else if (PtInRect(&_notice[3].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_MONSTER)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[3].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 3) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_MONSTER;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
	else if (PtInRect(&_notice[4].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_ITEM)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[4].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 4) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_ITEM;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
	else if (PtInRect(&_notice[5].rc, _ptMouse) && _paper.isOn)
	{
		if (_tileStyle != TILESTYLE_NONE)
		{
			_paper.currentFrameY = 0;
			this->paperOn();
		}
		_notice[5].currentX = 1;
		for (int i = 0; i < 6; i++)
		{
			if (i == 5) continue;
			_notice[i].currentX = 0;
		}
		_tileStyle = TILESTYLE_NONE;
		_eraseMode.currentX = 0;
		_eraseMode.isOn = false;
	}
}
