#include "stdafx.h"
#include "itemManager.h"
#include "dungeonMap.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"

HRESULT itemManager::init(void)
{
	setItem();
	return S_OK;
}

void itemManager::release(void)
{
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
		_viCoin->coin->release();
		SAFE_DELETE(_viCoin->coin);
	}
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		_viBomb->bomb->release();
		SAFE_DELETE(_viBomb->bomb);
	}
	for (_viHealthPoint = _vHealthPoint.begin(); _viHealthPoint != _vHealthPoint.end(); ++_viHealthPoint)
	{
		_viHealthPoint->healthPoint->release();
		SAFE_DELETE(_viHealthPoint->healthPoint);
	}
	for (_viPenta = _vPenta.begin(); _viPenta != _vPenta.end(); ++_viPenta)
	{
		_viPenta->pentagram->release();
		SAFE_DELETE(_viPenta->pentagram);
	}
	for (_viOuijaboard = _vOuijaboard.begin(); _viOuijaboard != _vOuijaboard.end(); ++_viOuijaboard)
	{
		_viOuijaboard->ouijaboard->release();
		SAFE_DELETE(_viOuijaboard->ouijaboard);
	}
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		_viGhost->ghostBaby->release();
		SAFE_DELETE(_viGhost->ghostBaby);
	}
	for (_viPillATKUP = _vPillATKUP.begin(); _viPillATKUP != _vPillATKUP.end(); ++_viPillATKUP)
	{
		_viPillATKUP->pillATKUP->release();
		SAFE_DELETE(_viPillATKUP->pillATKUP);
	}
	for (_viPillSPEEDUP = _vPillSPEEDUP.begin(); _viPillSPEEDUP != _vPillSPEEDUP.end(); ++_viPillSPEEDUP)
	{
		_viPillSPEEDUP->pillSPEEDUP->release();
		SAFE_DELETE(_viPillSPEEDUP->pillSPEEDUP);
	}
	for (_viPillATKDOWN = _vPillATKDOWN.begin(); _viPillATKDOWN != _vPillATKDOWN.end(); ++_viPillATKDOWN)
	{
		_viPillATKDOWN->pillATKDOWN->release();
		SAFE_DELETE(_viPillATKDOWN->pillATKDOWN);
	}
	for (_viPillSPEEDDOWN = _vPillSPEEDDOWN.begin(); _viPillSPEEDDOWN != _vPillSPEEDDOWN.end(); ++_viPillSPEEDDOWN)
	{
		_viPillSPEEDDOWN->pillSPEEDDOWN->release();
		SAFE_DELETE(_viPillSPEEDDOWN->pillSPEEDDOWN);
	}
	for (_viKey = _vKey.begin(); _viKey != _vKey.end(); ++_viKey)
	{
		_viKey->key->release();
		SAFE_DELETE(_viKey->key);
	}

}

void itemManager::update(void)
{
	int bombCount = 0;
	RECT rcTemp;
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viCoin->coin->update();
	}
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); bombCount++)
	{
		
		if (_enemy->getFieldMonsterNum() <= 0 && !_viBomb->bomb->getStruct().isInstall) _viBomb->bomb->drop();
		if (_viBomb->bomb->getStruct().isInstall) _viBomb->bomb->frame();
		if (_viBomb->bomb->getStruct().time < 0)
		{
			playerExplosionCollision(bombCount);
			objectExplosionCollision(bombCount);
			enemyExplosionCollision(bombCount);
			EFFECTMANAGER->play("explosionEffect", _viBomb->bomb->getStruct().x - CAMERAMANAGER->getX(), _viBomb->bomb->getStruct().y - _viBomb->bomb->getStruct().img->getFrameHeight() / 2 - CAMERAMANAGER->getY());
			SOUNDMANAGER->play("bomb", VOLUME->getSfxVolume() / 10);
			_viBomb = _vBomb.erase(_viBomb);
		}
		else ++_viBomb;
	}
	for (_viHealthPoint = _vHealthPoint.begin(); _viHealthPoint != _vHealthPoint.end(); ++_viHealthPoint)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viHealthPoint->healthPoint->update();
	}
	for (_viPenta = _vPenta.begin(); _viPenta != _vPenta.end(); ++_viPenta)
	{
		_viPenta->pentagram->update();
	}
	for (_viOuijaboard = _vOuijaboard.begin(); _viOuijaboard != _vOuijaboard.end(); ++_viOuijaboard)
	{
		_viOuijaboard->ouijaboard->update();
	}
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		_viGhost->ghostBaby->update();
	}
	for (_viPillATKUP = _vPillATKUP.begin(); _viPillATKUP != _vPillATKUP.end(); ++_viPillATKUP)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;;
		_viPillATKUP->pillATKUP->update();
	}
	for (_viPillSPEEDUP = _vPillSPEEDUP.begin(); _viPillSPEEDUP != _vPillSPEEDUP.end(); ++_viPillSPEEDUP)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;;
		_viPillSPEEDUP->pillSPEEDUP->update();
	}
	for (_viPillATKDOWN = _vPillATKDOWN.begin(); _viPillATKDOWN != _vPillATKDOWN.end(); ++_viPillATKDOWN)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;;
		_viPillATKDOWN->pillATKDOWN->update();
	}
	for (_viPillSPEEDDOWN = _vPillSPEEDDOWN.begin(); _viPillSPEEDDOWN != _vPillSPEEDDOWN.end(); ++_viPillSPEEDDOWN)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;;
		_viPillSPEEDDOWN->pillSPEEDDOWN->update();
	}
	for (_viKey = _vKey.begin(); _viKey != _vKey.end(); ++_viKey)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;;
		_viKey->key->update();
	}
	playerItemCollision();
}

void itemManager::render(void)
{
	RECT rcTemp;
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end(); ++_viCoin)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viCoin->coin->render();
	}
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (_enemy->getFieldMonsterNum() <= 0 || _viBomb->bomb->getStruct().isInstall)
		_viBomb->bomb->render();
	}
	for (_viHealthPoint = _vHealthPoint.begin(); _viHealthPoint != _vHealthPoint.end(); ++_viHealthPoint)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viHealthPoint->healthPoint->render();
	}
	for (_viPenta = _vPenta.begin(); _viPenta != _vPenta.end(); ++_viPenta)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viPenta->pentagram->render();
	}
	for (_viOuijaboard = _vOuijaboard.begin(); _viOuijaboard != _vOuijaboard.end(); ++_viOuijaboard)
	{
		_viOuijaboard->ouijaboard->render();
	}
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		_viGhost->ghostBaby->render();
	}
	for (_viPillATKUP = _vPillATKUP.begin(); _viPillATKUP != _vPillATKUP.end(); ++_viPillATKUP)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viPillATKUP->pillATKUP->render();
	}
	for (_viPillSPEEDUP = _vPillSPEEDUP.begin(); _viPillSPEEDUP != _vPillSPEEDUP.end(); ++_viPillSPEEDUP)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viPillSPEEDUP->pillSPEEDUP->render();
	}
	for (_viPillATKDOWN = _vPillATKDOWN.begin(); _viPillATKDOWN != _vPillATKDOWN.end(); ++_viPillATKDOWN)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viPillATKDOWN->pillATKDOWN->render();
	}
	for (_viPillSPEEDDOWN = _vPillSPEEDDOWN.begin(); _viPillSPEEDDOWN != _vPillSPEEDDOWN.end(); ++_viPillSPEEDDOWN)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viPillSPEEDDOWN->pillSPEEDDOWN->render();
	}
	for (_viKey = _vKey.begin(); _viKey != _vKey.end(); ++_viKey)
	{
		if (_enemy->getFieldMonsterNum() > 0) break;
		_viKey->key->render();
	}
}

void itemManager::bombSet(float x, float y)
{
	bombData _bombData;
	ZeroMemory(&_bombData, sizeof(bombData));
	_bombData.bomb = new bomb;
	_bombData.bomb->init(x, y, true);
	_vBomb.push_back(_bombData);
}

void itemManager::coinSet(float x, float y)
{
	coinData _coinData;
	ZeroMemory(&_coinData, sizeof(coinData));
	_coinData.coin = new coin;
	_coinData.coin->init(x, y);
	_vCoin.push_back(_coinData);
}

void itemManager::hpSet(float x, float y)
{
	healthPointData _healthPointData;
	ZeroMemory(&_healthPointData, sizeof(healthPointData));
	_healthPointData.healthPoint = new healthPoint;
	_healthPointData.healthPoint->init(x, y, true);
	_vHealthPoint.push_back(_healthPointData);
}

void itemManager::pillSet(float x, float y, int num)
{
	if (num == 0)
	{
		pillATKUPData _pillATKUPData;
		ZeroMemory(&_pillATKUPData, sizeof(pillATKUPData));
		_pillATKUPData.pillATKUP = new pillATKUP;
		_pillATKUPData.pillATKUP->init(x, y);
		_vPillATKUP.push_back(_pillATKUPData);
	}
	else if (num == 1)
	{
		pillSPEEDUPData _pillSPEEDUPData;
		ZeroMemory(&_pillSPEEDUPData, sizeof(pillSPEEDUPData));
		_pillSPEEDUPData.pillSPEEDUP = new pillSPEEDUP;
		_pillSPEEDUPData.pillSPEEDUP->init(x, y);
		_vPillSPEEDUP.push_back(_pillSPEEDUPData);
	}
	else if (num == 2)
	{
		pillSPEEDDOWNData _pillSPEEDDOWNData;
		ZeroMemory(&_pillSPEEDDOWNData, sizeof(pillSPEEDDOWNData));
		_pillSPEEDDOWNData.pillSPEEDDOWN = new pillSPEEDDOWN;
		_pillSPEEDDOWNData.pillSPEEDDOWN->init(x, y);
		_vPillSPEEDDOWN.push_back(_pillSPEEDDOWNData);
	}
	else if (num == 3)
	{
		pillSPEEDDOWNData _pillSPEEDDOWNData;
		ZeroMemory(&_pillSPEEDDOWNData, sizeof(pillSPEEDDOWNData));
		_pillSPEEDDOWNData.pillSPEEDDOWN = new pillSPEEDDOWN;
		_pillSPEEDDOWNData.pillSPEEDDOWN->init(x, y);
		_vPillSPEEDDOWN.push_back(_pillSPEEDDOWNData);
	}
}

void itemManager::removeCoin(int arrNum)
{
	EFFECTMANAGER->play("coinGet", _vCoin[arrNum].coin->getStruct().x - CAMERAMANAGER->getX(), _vCoin[arrNum].coin->getStruct().y - CAMERAMANAGER->getY());
	SAFE_DELETE(_vCoin[arrNum].coin);
	SOUNDMANAGER->stop("coin pickup");
	_vCoin.erase(_vCoin.begin() + arrNum);
}

void itemManager::removeBomb(int arrNum)
{
	SAFE_DELETE(_vBomb[arrNum].bomb);
	SOUNDMANAGER->stop("bomb pickup");
	SOUNDMANAGER->stop("bomb");
	_vBomb.erase(_vBomb.begin() + arrNum);
}

void itemManager::removeHealthPoint(int arrNum)
{
	SAFE_DELETE(_vHealthPoint[arrNum].healthPoint);
	SOUNDMANAGER->stop("hp up");
	_vHealthPoint.erase(_vHealthPoint.begin() + arrNum);
}

void itemManager::removePentagram(void)
{
	_map->itemDelete(_vPenta[0].pos);
	SAFE_DELETE(_vPenta[0].pentagram);
	_vPenta.erase(_vPenta.begin());
}

void itemManager::removeOuijaboard(void)
{
	_map->itemDelete(_vOuijaboard[0].pos);
	SAFE_DELETE(_vOuijaboard[0].ouijaboard);
	_vOuijaboard.erase(_vOuijaboard.begin());
}

void itemManager::removeHarleQuinBaby(void)
{
	_map->itemDelete(_vGhost[0].pos);
	SAFE_DELETE(_vGhost[0].ghostBaby);
	_vGhost.erase(_vGhost.begin());
}

void itemManager::removePillAtkUp(int arrNum)
{
	SAFE_DELETE(_vPillATKUP[arrNum].pillATKUP);
	_vPillATKUP.erase(_vPillATKUP.begin() + arrNum);
}

void itemManager::removepillSpeedUp(int arrNum)
{
	SAFE_DELETE(_vPillSPEEDUP[arrNum].pillSPEEDUP);
	_vPillSPEEDUP.erase(_vPillSPEEDUP.begin() + arrNum);
}

void itemManager::removePillAtkDown(int arrNum)
{
	SAFE_DELETE(_vPillATKDOWN[arrNum].pillATKDOWN);
	_vPillATKDOWN.erase(_vPillATKDOWN.begin() + arrNum);
}

void itemManager::removePillSpeedDown(int arrNum)
{
	SAFE_DELETE(_vPillSPEEDDOWN[arrNum].pillSPEEDDOWN);
	_vPillSPEEDDOWN.erase(_vPillSPEEDDOWN.begin() + arrNum);
}

void itemManager::removeKey(int arrNum)
{ 
	SAFE_DELETE(_vKey[arrNum].key);
	SOUNDMANAGER->stop("key pickup");
	SOUNDMANAGER->stop("key drop");
	_vKey.erase(_vKey.begin() + arrNum);
}


