#include "stdafx.h"
#include "enemyManager.h"
#include "dungeonMap.h"
#include "minion.h"

void enemyManager::setMinion(void)
{
	SOUNDMANAGER->stop("monster die");
	for (int i = 0; i <TILEX * TILEY; i++)
	{
		if (_map->getTiles()[i].rc.left >  CAMERAMANAGER->getX() && _map->getTiles()[i].rc.right <CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_map->getTiles()[i].rc.top  > CAMERAMANAGER->getY() && _map->getTiles()[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
		{
			switch (_map->getAttribute()[i])
			{
				case ATTR_MONSTER_ATTACKFLY:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					attackFlyData _attackFlyData;
					ZeroMemory(&_attackFlyData, sizeof(attackFlyData));
					_attackFlyData.attackFly = new attackFlyMinion;
					_attackFlyData.attackFly->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_attackFlyData.pos = i;
					_vAttackFly.push_back(_attackFlyData);
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_BLUBBER:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					blubberData _blubberData;
					ZeroMemory(&_blubberData, sizeof(blubberData));
					_blubberData.blubber = new blubberMinion;
					_blubberData.blubber->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_blubberData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vBlubber.push_back(_blubberData);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_CHARGER:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					chargerData _chargerData;
					ZeroMemory(&_chargerData, sizeof(chargerData));
					_chargerData.charger = new chargerMinion;
					_chargerData.charger->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_chargerData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vCharger.push_back(_chargerData);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_CLOTTY:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					clottyData _clottydata;
					ZeroMemory(&_clottydata, sizeof(clottyData));
					_clottydata.clotty = new clotty;
					_clottydata.clotty->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_clottydata.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vClotty.push_back(_clottydata);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_GAPER:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					if (_vGaper.size() == 0) SOUNDMANAGER->play("zombie walker kid", VOLUME->getSfxVolume());
					frowningGaperData _frowningGaperData;
					ZeroMemory(&_frowningGaperData, sizeof(frowningGaperData));
					_frowningGaperData.gaper = new frowningGaperMinion;
					_frowningGaperData.gaper->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_frowningGaperData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vGaper.push_back(_frowningGaperData);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_HORF:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					horfData _horfData;
					ZeroMemory(&_horfData, sizeof(horfData));
					_horfData.horf = new horfMinion;
					_horfData.horf->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_horfData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vHorf.push_back(_horfData);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_LEVEL2FLY:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					level2FlyData _level2FlyData;
					ZeroMemory(&_level2FlyData, sizeof(level2FlyData));
					_level2FlyData.level2Fly = new level2FlyMinion;
					_level2FlyData.level2Fly->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_level2FlyData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vLevel2Fly.push_back(_level2FlyData);
					_fieldMonsterNum++;
					break;
				}
				case ATTR_MONSTER_TUMOR:
				{
					if (_fieldMonsterNum == 0) SOUNDMANAGER->play("summonsound", VOLUME->getSfxVolume());
					tumorData _tumorData;
					ZeroMemory(&_tumorData, sizeof(tumorData));
					_tumorData.tumor = new tumor;
					_tumorData.tumor->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
					_tumorData.pos = i;
					EFFECTMANAGER->play("monsterSpawn", _map->getTiles()[i].mosterPos.x - CAMERAMANAGER->getX(), _map->getTiles()[i].mosterPos.y - CAMERAMANAGER->getY());
					_vTumor.push_back(_tumorData);
					_fieldMonsterNum++;
					break;
				}
			}
			if (_bossSelect == BOSSSELECT_DUKEOFFLLIES && _map->getTiles()[i].monster == MONSTER_DUKEOFFLIES && _bossInit)
			{
				_dukeoffliesData.dukeofflies = new dukeofflies;
				_dukeoffliesData.dukeofflies->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
				_dukeoffliesData.pos = i;
				_fieldMonsterNum++;
			}
			else if (_bossSelect == BOSSSELECT_MONSTRO && _map->getTiles()[i].monster == MONSTER_MONSTRO && _bossInit)
			{
				_monstroData.monstro = new monstro;
				_monstroData.monstro->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
				_monstroData.pos = i;
				_fieldMonsterNum++;
			}
			else if (_bossSelect == BOSSSELECT_MEGAMAW && _map->getTiles()[i].monster == MONSTER_MEGAMAW && _bossInit)
			{
				_megamawData.megamaw = new megamaw;
				_megamawData.megamaw->init(_map->getTiles()[i].mosterPos.x, _map->getTiles()[i].mosterPos.y);
				_megamawData.pos = i;
				_fieldMonsterNum++;
			}
		}
	}
}
