#include "stdafx.h"
#include "itemManager.h"
#include "dungeonMap.h"

void itemManager::setItem(void)
{
	RECT rcTemp;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map->getTiles()[i].rc.left > CAMERAMANAGER->getX() && _map->getTiles()[i].rc.right <CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_map->getTiles()[i].rc.top  > CAMERAMANAGER->getY() && _map->getTiles()[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
		{
			switch (_map->getTiles()[i].item)
			{
			case ITEM_COIN:
				coinData _coinData;
				ZeroMemory(&_coinData, sizeof(coinData));
				_coinData.coin = new coin;
				_coinData.coin->init(_map->getTiles()[i].itemPos.x + 32, _map->getTiles()[i].itemPos.y + 32);
				_vCoin.push_back(_coinData);
				_map->itemDelete(i);
				break;
			case ITEM_BOMB:
				bombData _bombData;
				ZeroMemory(&_bombData, sizeof(bombData));
				_bombData.bomb = new bomb;
				_bombData.bomb->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y, false);
				_vBomb.push_back(_bombData);
				_map->itemDelete(i);
				break;
			case ITEM_HP:
				healthPointData _healthPointData;
				ZeroMemory(&_healthPointData, sizeof(healthPointData));
				_healthPointData.healthPoint = new healthPoint;
				_healthPointData.healthPoint->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y, false);
				_vHealthPoint.push_back(_healthPointData);
				_map->itemDelete(i);
				break;
			case ITEM_PILL_ATKUP:
				pillATKUPData _pillATKUPData;
				ZeroMemory(&_pillATKUPData, sizeof(pillATKUPData));
				_pillATKUPData.pillATKUP = new pillATKUP;
				_pillATKUPData.pillATKUP->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y);
				_vPillATKUP.push_back(_pillATKUPData);
				_map->itemDelete(i);
				SOUNDMANAGER->stop("power up1");
				break;
			case ITEM_PILL_SPEEDUP:
				pillSPEEDUPData _pillSPEEDUPData;
				ZeroMemory(&_pillSPEEDUPData, sizeof(pillSPEEDUPData));
				_pillSPEEDUPData.pillSPEEDUP = new pillSPEEDUP;
				_pillSPEEDUPData.pillSPEEDUP->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y);
				_vPillSPEEDUP.push_back(_pillSPEEDUPData);
				_map->itemDelete(i);
				SOUNDMANAGER->stop("power up1");
				break;
			case ITEM_PILL_ATKDOWN:
				pillATKDOWNData _pillATKDOWNData;
				ZeroMemory(&_pillATKDOWNData, sizeof(pillATKDOWNData));
				_pillATKDOWNData.pillATKDOWN = new pillATKDOWN;
				_pillATKDOWNData.pillATKDOWN->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y);
				_vPillATKDOWN.push_back(_pillATKDOWNData);
				_map->itemDelete(i);
				SOUNDMANAGER->stop("thumbs down");
				break;
			case ITEM_PILL_SPEEDDOWN:
				pillSPEEDDOWNData _pillSPEEDDOWNData;
				ZeroMemory(&_pillSPEEDDOWNData, sizeof(pillSPEEDDOWNData));
				_pillSPEEDDOWNData.pillSPEEDDOWN = new pillSPEEDDOWN;
				_pillSPEEDDOWNData.pillSPEEDDOWN->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y);
				_vPillSPEEDDOWN.push_back(_pillSPEEDDOWNData);
				_map->itemDelete(i);
				SOUNDMANAGER->stop("thumbs down");
				break;
			case ITEM_KEY:
				keyData _keyData;
				ZeroMemory(&_keyData, sizeof(keyData));
				_keyData.key = new key;
				_keyData.key->init(_map->getTiles()[i].itemPos.x, _map->getTiles()[i].itemPos.y);
				_vKey.push_back(_keyData);
				_map->itemDelete(i);
				break;

			case ITEM_PENTAGRAM:
				if (_vPenta.size() > 0) return;
				pentagramData _pentagramData;
				ZeroMemory(&_pentagramData, sizeof(pentagramData));
				_pentagramData.pentagram = new pentagram;
				_pentagramData.pentagram->init(_map->getTiles()[i].itemPos.x + 10, _map->getTiles()[i].itemPos.y - 20);
				_pentagramData.pos = i;
				_vPenta.push_back(_pentagramData);
				break;
			case ITEM_OUIJABOARD:
				if (_vOuijaboard.size() > 0) return;
				ouijaboardData _ouijaboardData;
				ZeroMemory(&_ouijaboardData, sizeof(ouijaboardData));
				_ouijaboardData.ouijaboard = new ouijaboard;
				_ouijaboardData.ouijaboard->init(_map->getTiles()[i].itemPos.x + 10, _map->getTiles()[i].itemPos.y - 20);
				_ouijaboardData.pos = i;
				_vOuijaboard.push_back(_ouijaboardData);
				break;
			case ITEM_FAMILIAR:
				if (_vGhost.size() > 0) return;
				ghostBabyData _ghostBabyData;
				ZeroMemory(&_ghostBabyData, sizeof(ghostBabyData));
				_ghostBabyData.ghostBaby = new ghostBaby;
				_ghostBabyData.ghostBaby->init(_map->getTiles()[i].itemPos.x + 10, _map->getTiles()[i].itemPos.y - 20);
				_ghostBabyData.pos = i;
				_vGhost.push_back(_ghostBabyData);
				break;
			}
		}
	}
}