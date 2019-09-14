#include "stdafx.h"
#include "objectManager.h"
#include "dungeonMap.h"
#include "player.h"
#include "itemManager.h"
#include "enemyManager.h"

HRESULT objectManager::init(void)
{
	setObject();
	_isDoorOpen = false;
	return S_OK;
}

void objectManager::release(void)
{
	for (_viChest = _vChest.begin(); _viChest != _vChest.end(); ++_viChest)
	{
		_viChest->chest->release();
		SAFE_DELETE(_viChest->chest);
	}
	for (_viSpikeSmall = _vSpikeSmall.begin(); _viSpikeSmall != _vSpikeSmall.end(); ++_viSpikeSmall)
	{
		_viSpikeSmall->spike->release();
	}
	for (_viSpikeLarge = _vSpikeLarge.begin(); _viSpikeLarge != _vSpikeLarge.end(); ++_viSpikeLarge)
	{
		_viSpikeLarge->spike->release();
	}
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); ++_viDoor)
	{
		_viDoor->door->release();
		SAFE_DELETE(_viDoor->door);
	}
	for (_viExit = _vExit.begin(); _viExit != _vExit.end(); ++_viExit)
	{
		(*_viExit)->release();
		SAFE_DELETE(*_viExit);
	}
	for (_viBPoop = _vBPoop.begin(); _viBPoop != _vBPoop.end(); ++_viBPoop)
	{
		_viBPoop->poop->release();
		SAFE_DELETE(_viBPoop->poop);
	}
	for (_viRPoop = _vRPoop.begin(); _viRPoop != _vRPoop.end(); ++_viRPoop)
	{
		_viRPoop->poop->release();
		SAFE_DELETE(_viRPoop->poop);
	}
}

void objectManager::update(void)
{
	int chestNum = 0;
	for (_viChest = _vChest.begin(); _viChest != _vChest.end(); ++_viChest, chestNum++)
	{
		_viChest->chest->update();
		if (_viChest->chest->getTime() < 0)
		{
			removeChest(chestNum);
			break;
		}
	}
	for (_viSpikeSmall = _vSpikeSmall.begin(); _viSpikeSmall != _vSpikeSmall.end(); ++_viSpikeSmall)
	{
		_viSpikeSmall->spike->update();
	}
	for (_viSpikeLarge = _vSpikeLarge.begin(); _viSpikeLarge != _vSpikeLarge.end(); ++_viSpikeLarge)
	{
		_viSpikeLarge->spike->update();
	}
	
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); ++_viDoor)
	{
		_viDoor->door->update(_isDoorOpen);	
	}
	for (_viExit = _vExit.begin(); _viExit != _vExit.end(); ++_viExit)
	{
		if (_enemy->getFieldMonsterNum() <= 0) (*_viExit)->update();
	}

}

void objectManager::render(void)
{
	for (_viChest = _vChest.begin(); _viChest != _vChest.end(); ++_viChest)
	{
		_viChest->chest->render();
	}
	for (_viSpikeSmall = _vSpikeSmall.begin(); _viSpikeSmall != _vSpikeSmall.end(); ++_viSpikeSmall)
	{
		_viSpikeSmall->spike->render();
	}
	for (_viSpikeLarge = _vSpikeLarge.begin(); _viSpikeLarge != _vSpikeLarge.end(); ++_viSpikeLarge)
	{
		_viSpikeLarge->spike->render();
	}
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); ++_viDoor)
	{
		_viDoor->door->render();
	}
	for (_viExit = _vExit.begin(); _viExit != _vExit.end(); ++_viExit)
	{
		if (_enemy->getFieldMonsterNum() <= 0) (*_viExit)->render();
	}
	
	for (_viBPoop = _vBPoop.begin(); _viBPoop != _vBPoop.end(); ++_viBPoop)
	{
		_viBPoop->poop->render();
	}

	for (_viRPoop = _vRPoop.begin(); _viRPoop != _vRPoop.end(); ++_viRPoop)
	{
		_viRPoop->poop->render();
	}
}

void objectManager::refresh(void)
{
	for (int i = 0; i < _vChest.size(); i++)
	{
		SAFE_DELETE(_vChest[i].chest);
		_vChest.erase(_vChest.begin() + i);
	}
	for (int i = 0; i < _vDoor.size(); i++)
	{
		SAFE_DELETE(_vDoor[i].door);
		_vDoor.erase(_vDoor.begin() + i);
	}
	for (int i = 0; i < _vBPoop.size(); i++)
	{
		SAFE_DELETE(_vBPoop[i].poop);
		_vBPoop.erase(_vBPoop.begin() + i);
	}
	for (int i = 0; i < _vRPoop.size(); i++)
	{
		SAFE_DELETE(_vRPoop[i].poop);
		_vRPoop.erase(_vRPoop.begin() + i);
	}
	for (int i = 0; i < _vExit.size(); i++)
	{
		SAFE_DELETE(_vExit[i]);
		_vExit.erase(_vExit.begin() + i);
	}
}


void objectManager::removeChest(int arrNum)
{
	_map->objectDelete(_vChest[arrNum].pos);
	SAFE_DELETE(_vChest[arrNum].chest);
	SOUNDMANAGER->stop("chest open");
	SOUNDMANAGER->stop("chest drop 1");
	_vChest.erase(_vChest.begin());
}

void objectManager::removeBasicPoop(int arrNum)
{
	int rand = RND->getInt(3);
	if (rand == 0) _item->coinSet(_vBPoop[arrNum].poop->getStruct().x, _vBPoop[arrNum].poop->getStruct().y);
	_map->objectDelete(_vBPoop[arrNum].pos);
	SAFE_DELETE(_vBPoop[arrNum].poop);
	_vBPoop.erase(_vBPoop.begin() + arrNum);
	
}

void objectManager::removeRedPoop(int arrNum)
{
	int rand = RND->getInt(3);
	if (rand == 0) _item->coinSet(_vRPoop[arrNum].poop->getStruct().x, _vRPoop[arrNum].poop->getStruct().y);
	_map->objectDelete(_vRPoop[arrNum].pos);
	SAFE_DELETE(_vRPoop[arrNum].poop);
	_vRPoop.erase(_vRPoop.begin() + arrNum);
}

