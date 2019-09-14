#include "stdafx.h"
#include "playerUI.h"

HRESULT playerUI::init(void)
{
	for (int i = 0; i < 3; i++)
	{
		_playerHp.img = IMAGEMANAGER->addFrameImage("playrHp", "image/character/playrHp.bmp", 93, 28, 3, 1, true, RGB(255, 0, 255));
		_playerHp.x = 140 + i * 32;
		_playerHp.y = 50;
		_playerHp.currentX = 0;
		_playerHp.currentPoint = 1;			//플레이어 체력위치 1일때는 뒤에서 1번째 하트위치
		_vPlayerHp.push_back(_playerHp);
	}
	_coin.img = IMAGEMANAGER->addImage("coinUI", "image/item/coinUI.bmp", 18, 22, true, RGB(255, 0, 255));
	_coin.x = 50;
	_coin.y = 130;
	_bomb.img = IMAGEMANAGER->addImage("bombUI", "image/item/bombUI.bmp", 26, 26, true, RGB(255, 0, 255));
	_bomb.x = 46;
	_bomb.y = 160;
	_key.img = IMAGEMANAGER->addImage("keyUI", "image/item/keyUI.bmp", 18, 24, true, RGB(255, 0, 255));
	_key.x = 50;
	_key.y = 190;
	IMAGEMANAGER->addFrameImage("itemNum", "image/character/number.bmp", 200, 21, 10, 1, true, RGB(255, 0, 255));
	
	return S_OK;
}

void playerUI::release(void)
{
}

void playerUI::update(void)
{
}

void playerUI::render(void)
{
	for (_viPlayerHp = _vPlayerHp.begin(); _viPlayerHp != _vPlayerHp.end(); ++_viPlayerHp)
	{
		_viPlayerHp->img->frameRender(getMemDC(), _viPlayerHp->x, _viPlayerHp->y, _viPlayerHp->currentX, 0);
	}
	_coin.img->render(getMemDC(), _coin.x, _coin.y);
	_bomb.img->render(getMemDC(), _bomb.x, _bomb.y);
	_key.img->render(getMemDC(), _key.x, _key.y);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _coin.x + 20, _coin.y, _coinNum.size() / 10, 0);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _coin.x + 36, _coin.y, _coinNum.size() % 10, 0);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _bomb.x + 26, _bomb.y, _bombNum.size() / 10, 0);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _bomb.x + 42, _bomb.y, _bombNum.size() % 10, 0);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _key.x + 20, _key.y, _keyNum.size() / 10, 0);
	IMAGEMANAGER->findImage("itemNum")->frameRender(getMemDC(), _key.x + 36, _key.y, _keyNum.size() % 10, 0);
}

void playerUI::increaseHp()
{
	_viPlayerHp = _vPlayerHp.end() - _playerHp.currentPoint;
	if (_viPlayerHp->currentX == 0)
	{
		if (_playerHp.currentPoint == 1) return;
		_playerHp.currentPoint--;
		_viPlayerHp = _vPlayerHp.end() - _playerHp.currentPoint;
		_viPlayerHp->currentX = 0;
	}
	else if(_viPlayerHp->currentX == 1)
	{
		if (_playerHp.currentPoint != 1)
		{
			_viPlayerHp->currentX = 0;
			_playerHp.currentPoint--;
			_viPlayerHp = _vPlayerHp.end() - _playerHp.currentPoint;
			_viPlayerHp->currentX = 1;
		}
		else
		{
			_viPlayerHp->currentX = 0;
		}
	}
	else
	{
		_viPlayerHp->currentX = 0;
	}
	
}

void playerUI::decreaseHp(void)
{
	_viPlayerHp = _vPlayerHp.end() - _playerHp.currentPoint;
	if (_viPlayerHp->currentX == 0)
	{
		_viPlayerHp->currentX = 1;
	}
	else if(_viPlayerHp->currentX == 1)
	{
		_viPlayerHp->currentX = 2;
	}
	else
	{
		if (_viPlayerHp == _vPlayerHp.begin()) return;
		_playerHp.currentPoint++;
		_viPlayerHp = _vPlayerHp.end() - _playerHp.currentPoint;
		_viPlayerHp->currentX = 1;
	}
}

void playerUI::increaseCoin(void)
{
	if (_coinNum.size() > 100) return;
	_coinNum.push_back(1);
}

void playerUI::decreaseCoin(void)
{
	if (_coinNum.size() < 0) return;
	_coinNum.pop_back();
}

void playerUI::increaseBomb(void)
{
	if (_bombNum.size() > 100) return;
	_bombNum.push_back(1);
}

void playerUI::decreaseBomb(void)
{
	if (_bombNum.size() < 0) return;
	_bombNum.pop_back();
}

void playerUI::increaseKey(void)
{
	if (_keyNum.size() > 100) return;
	_keyNum.push_back(1);
}

void playerUI::decreaseKey(void)
{
	if (_keyNum.size() < 0) return;
	_keyNum.pop_back();
}
