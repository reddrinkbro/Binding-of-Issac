#include "stdafx.h"
#include "objectManager.h"
#include "dungeonMap.h"

void objectManager::setObject(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map->getTiles()[i].rc.left > CAMERAMANAGER->getX() - TILESIZE && _map->getTiles()[i].rc.right <CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_map->getTiles()[i].rc.top  > CAMERAMANAGER->getY() - TILESIZE && _map->getTiles()[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
		{
			switch (_map->getTiles()[i].frameObj)
			{
			case FRAMEOBJ_CHEST:
				SOUNDMANAGER->play("chest drop 1", VOLUME->getSfxVolume() / 10);
				treasureChestData _treasureChestData;
				ZeroMemory(&_treasureChestData, sizeof(treasureChestData));
				_treasureChestData.chest = new treasureChest;
				_treasureChestData.chest->init(_map->getTiles()[i].objectPos.x + 32, _map->getTiles()[i].objectPos.y + 32);
				_treasureChestData.pos = i;
				_vChest.push_back(_treasureChestData);
				break;
			case FRAMEOBJ_SPIKE1:
				spikeLargeData _spikeLargeData;
				ZeroMemory(&_spikeLargeData, sizeof(spikeLargeData));
				_spikeLargeData.spike = new spikeLarge;
				_spikeLargeData.spike->init(_map->getTiles()[i].objectPos.x, _map->getTiles()[i].objectPos.y);
				_spikeLargeData.pos = i;
				_vSpikeLarge.push_back(_spikeLargeData);
				break;
			case FRAMEOBJ_SPIKE2:
				spikeSmallData _spikeSmallData;
				ZeroMemory(&_spikeSmallData, sizeof(spikeSmallData));
				_spikeSmallData.spike = new spikeSmall;
				_spikeSmallData.spike->init(_map->getTiles()[i].objectPos.x, _map->getTiles()[i].objectPos.y);
				_spikeSmallData.pos = i;
				_vSpikeSmall.push_back(_spikeSmallData);
				break;
			case FRAMEOBJ_HOLE:
				exitObject* _exitObject;
				_exitObject = new exitObject;
				_exitObject->init(_map->getTiles()[i].objectPos.x, _map->getTiles()[i].objectPos.y);
				_vExit.push_back(_exitObject);
				break;
			case FRAMEOBJ_POOP1:
				basicPoopData _basicPoopData;
				ZeroMemory(&_basicPoopData, sizeof(basicPoopData));
				_basicPoopData.poop = new basicPoop;
				_basicPoopData.poop->init(_map->getTiles()[i].objectPos.x + 32, _map->getTiles()[i].objectPos.y + 32);
				_basicPoopData.pos = i;
				_vBPoop.push_back(_basicPoopData);
				break;
			case FRAMEOBJ_POOP2:
				redPoopData _redPoopData;
				ZeroMemory(&_basicPoopData, sizeof(redPoopData));
				_redPoopData.poop = new redPoop;
				_redPoopData.poop->init(_map->getTiles()[i].objectPos.x + 32, _map->getTiles()[i].objectPos.y + 32);
				_redPoopData.pos = i;
				_vRPoop.push_back(_redPoopData);
				break;
			}

			switch (_map->getTiles()[i].doorObj)
			{
			case DOOR_UP:
				doorData _doorData1;
				ZeroMemory(&_doorData1, sizeof(doorData));
				_doorData1.door = new door;
				_doorData1.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, _map->getMapSelect(), _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData1.pos = i;
				_vDoor.push_back(_doorData1);
				break;
			case DOOR_RIGHT:
				doorData _doorData2;
				ZeroMemory(&_doorData2, sizeof(doorData));
				_doorData2.door = new door;
				_doorData2.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, _map->getMapSelect(), _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData2.pos = i;
				_vDoor.push_back(_doorData2);
				break;
			case DOOR_DOWN:
				doorData _doorData3;
				ZeroMemory(&_doorData3, sizeof(doorData));
				_doorData3.door = new door;
				_doorData3.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, _map->getMapSelect(), _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData3.pos = i;
				_vDoor.push_back(_doorData3);
				break;
			case DOOR_LEFT:
				doorData _doorData4;
				ZeroMemory(&_doorData4, sizeof(doorData));
				_doorData4.door = new door;
				_doorData4.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, _map->getMapSelect(), _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData4.pos = i;
				_vDoor.push_back(_doorData4);
				break;
			case SHOP_DOOR_UP:
				doorData _doorData5;
				ZeroMemory(&_doorData5, sizeof(doorData));
				_doorData5.door = new door;
				_doorData5.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 3, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData5.pos = i;
				_vDoor.push_back(_doorData5);
				break;
			case SHOP_DOOR_RIGHT:
				doorData _doorData6;
				ZeroMemory(&_doorData6, sizeof(doorData));
				_doorData6.door = new door;
				_doorData6.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 3, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData6.pos = i;
				_vDoor.push_back(_doorData6);
				break;
			case SHOP_DOOR_DOWN:
				doorData _doorData7;
				ZeroMemory(&_doorData7, sizeof(doorData));
				_doorData7.door = new door;
				_doorData7.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 3, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData7.pos = i;
				_vDoor.push_back(_doorData7);
				break;
			case SHOP_DOOR_LEFT:
				doorData _doorData8;
				ZeroMemory(&_doorData8, sizeof(doorData));
				_doorData8.door = new door;
				_doorData8.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 3, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData8.pos = i;
				_vDoor.push_back(_doorData8);
				break;
			case BOSS_DOOR_UP:
				doorData _doorData9;
				ZeroMemory(&_doorData9, sizeof(doorData));
				_doorData9.door = new door;
				_doorData9.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 4, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData9.pos = i;
				_vDoor.push_back(_doorData9);
				break;
			case BOSS_DOOR_RIGHT:
				doorData _doorData10;
				ZeroMemory(&_doorData10, sizeof(doorData));
				_doorData10.door = new door;
				_doorData10.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 4, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData10.pos = i;
				_vDoor.push_back(_doorData10);
				break;
			case BOSS_DOOR_DOWN:
				doorData _doorData11;
				ZeroMemory(&_doorData11, sizeof(doorData));
				_doorData11.door = new door;
				_doorData11.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 4, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData11.pos = i;
				_vDoor.push_back(_doorData11);
				break;
			case BOSS_DOOR_LEFT:
				doorData _doorData12;
				ZeroMemory(&_doorData12, sizeof(doorData));
				_doorData12.door = new door;
				_doorData12.door->init(_map->getTiles()[i].doorPos.x, _map->getTiles()[i].doorPos.y, 4, _map->getTiles()[i].doorObj, _isDoorOpen);
				_doorData12.pos = i;
				_vDoor.push_back(_doorData12);
				break;
			}
		}
	}
}