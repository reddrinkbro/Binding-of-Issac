#include "stdafx.h"
#include "enemyManager.h"
#include "minion.h"
#include "player.h"
#include "dungeonMap.h"
HRESULT enemyManager::init(BOSSSELECT bossSelect)
{
	EFFECTMANAGER->addEffect("monsterDieEffect", "image/enemy/effect/monsterDieEffect.bmp", 960, 80, 80, 80, 14, 8);
	EFFECTMANAGER->addEffect("flyDieEffect", "image/enemy/effect/flyDieEffect.bmp", 1536, 128, 128, 128, 14, 8);
	EFFECTMANAGER->addEffect("monsterSpawn", "image/enemy/effect/monsterSpawn.bmp", 3060, 170, 204, 170, 15, 10);
	EFFECTMANAGER->addEffect("monsterSpawnLarge", "image/enemy/effect/monsterSpawnLarge.bmp", 4590, 255, 306, 255, 15, 10);
	_bossSelect = bossSelect;
	_bossInit = false;
	tileSetUp();
	setMinion();
	_sixWayBullet = new sixWayBullet;
	_sixWayBullet->init(300);
	_fieldMonsterNum = 0;
	return S_OK;
}

void enemyManager::release(void)
{
	for (_viBlood = _vBlood.begin(); _viBlood != _vBlood.end(); ++_viBlood)
	{
		SAFE_DELETE(_viBlood->img);
	}
	for (_viGaper = _vGaper.begin(); _viGaper != _vGaper.end(); ++_viGaper)
	{
		_viGaper->gaper->release();
		SAFE_DELETE(_viGaper->gaper);
	}
	for (_viClotty = _vClotty.begin(); _viClotty != _vClotty.end(); ++_viClotty)
	{
		_viClotty->clotty->release();
		SAFE_DELETE(_viClotty->clotty);
	}
	for (_viHorf = _vHorf.begin(); _viHorf != _vHorf.end(); ++_viHorf)
	{
		_viHorf->horf->release();
		SAFE_DELETE(_viHorf->horf);
	}
	for (_viAttackFly = _vAttackFly.begin(); _viAttackFly != _vAttackFly.end(); ++_viAttackFly)
	{
		_viAttackFly->attackFly->release();
		SAFE_DELETE(_viAttackFly->attackFly);
	}
	for (_viLevel2Fly = _vLevel2Fly.begin(); _viLevel2Fly != _vLevel2Fly.end(); ++_viLevel2Fly)
	{
		_viLevel2Fly->level2Fly->release();
		SAFE_DELETE(_viLevel2Fly->level2Fly);
	}
	for (_viBlubber = _vBlubber.begin(); _viBlubber != _vBlubber.end(); ++_viBlubber)
	{
		_viBlubber->blubber->release();
		SAFE_DELETE(_viBlubber->blubber);
	}
	for (_viCharger = _vCharger.begin(); _viCharger != _vCharger.end(); ++_viCharger)
	{
		_viCharger->charger->release();
		SAFE_DELETE(_viCharger->charger);
	}

	for (_viTumor = _vTumor.begin(); _viTumor != _vTumor.end(); ++_viTumor)
	{
		_viTumor->tumor->release();
		SAFE_DELETE(_viTumor->tumor);
	}
	if (_bossSelect == BOSSSELECT_DUKEOFFLLIES && _bossInit)
	{
		_dukeoffliesData.dukeofflies->release();
		SAFE_DELETE(_dukeoffliesData.dukeofflies);
	}
	else if (_bossSelect == BOSSSELECT_MONSTRO && _bossInit)
	{
		_monstroData.monstro->release();
		SAFE_DELETE(_monstroData.monstro);
	}
	else if (_bossSelect == BOSSSELECT_MEGAMAW && _bossInit)
	{
		_megamawData.megamaw->release();
		SAFE_DELETE(_megamawData.megamaw);
	}
	_sixWayBullet->release();
	SAFE_DELETE(_sixWayBullet);
}

void enemyManager::update(void)
{
	EFFECTMANAGER->update();
	RECT rcTemp;
	int clottyNum = 0;
	int blubberNum = 0;
	int chargerNum = 0;
	int hopperNum = 0;
	for (_viGaper = _vGaper.begin(); _viGaper != _vGaper.end(); ++_viGaper)
	{
		_viGaper->gaper->move(_player->getBody().x,_player->getBody().y);
	}
	for (_viClotty = _vClotty.begin(); _viClotty != _vClotty.end(); ++_viClotty, clottyNum++)
	{
		_viClotty->clotty->update();
		objectEnemyCollision(COLLISIONMONSTER_CLOTTY, clottyNum);
		tileEnemyCollision(COLLISIONMONSTER_CLOTTY, clottyNum);
	}
	for (_viHorf = _vHorf.begin(); _viHorf != _vHorf.end(); ++_viHorf)
	{
		_viHorf->horf->update(_player->getBody().x,_player->getBody().y);
	}
	for (_viAttackFly = _vAttackFly.begin(); _viAttackFly != _vAttackFly.end(); ++_viAttackFly)
	{
		_viAttackFly->attackFly->move(_player->getBody().x, _player->getBody().y);
	}
	for (_viLevel2Fly = _vLevel2Fly.begin(); _viLevel2Fly != _vLevel2Fly.end(); ++_viLevel2Fly)
	{
		_viLevel2Fly->level2Fly->update(_player->getBody().x, _player->getBody().y);
	}
	for (_viBlubber = _vBlubber.begin(); _viBlubber != _vBlubber.end(); ++_viBlubber , blubberNum++)
	{
		_viBlubber->blubber->update();
		objectEnemyCollision(COLLISIONMONSTER_BLUBBER, blubberNum);
		tileEnemyCollision(COLLISIONMONSTER_BLUBBER, blubberNum);
	}
	for (_viCharger = _vCharger.begin(); _viCharger != _vCharger.end(); ++_viCharger, chargerNum++)
	{
		_viCharger->charger->update();
		if ((_player->getBody().x >= _viCharger->charger->getStruct().rc.left && _player->getBody().x <= _viCharger->charger->getStruct().rc.right) ||
			(_player->getBody().y >= _viCharger->charger->getStruct().rc.top && _player->getBody().y <= _viCharger->charger->getStruct().rc.bottom))
		{
			_viCharger->charger->charge(_player->getBody().x, _player->getBody().y);
		}
		else
		{	
			if (_viCharger->charger->getStruct().isCharge)
			{
				int randomDircection = RND->getInt(4);
				if (randomDircection == 0) _viCharger->charger->setState(CHARGERSTATE_UP);
				else if(randomDircection == 1) _viCharger->charger->setState(CHARGERSTATE_DOWN);
				else if (randomDircection == 2) _viCharger->charger->setState(CHARGERSTATE_LEFT);
				else if (randomDircection == 3) _viCharger->charger->setState(CHARGERSTATE_RIGHT);
			}
			_viCharger->charger->setChargerToFalse();
		}
		objectEnemyCollision(COLLISIONMONSTER_CHARGER, chargerNum);
		tileEnemyCollision(COLLISIONMONSTER_CHARGER, chargerNum);
	}

	for (_viTumor = _vTumor.begin(); _viTumor != _vTumor.end(); ++_viTumor)
	{
		_viTumor->tumor->update();
		_viTumor->tumor->move(_player->getBody().x, _player->getBody().y);
	}
	if (_bossSelect == BOSSSELECT_DUKEOFFLLIES && _bossInit)
	{
		_dukeoffliesData.dukeofflies->update();
		tileEnemyCollision(COLLISIONMONSTER_DUKEOFFLIES, 0);
		if (_dukeoffliesData.dukeofflies->getStruct().state == DUKEOFFLIESSTATE_SPAWNONE && _dukeoffliesData.dukeofflies->getStruct().currentX == 4 && _dukeoffliesData.dukeofflies->getStruct().isSpawn)
		{
			spawnAttackFly(1);
			_dukeoffliesData.dukeofflies->spawnPause();
		}
		else if (_dukeoffliesData.dukeofflies->getStruct().state == DUKEOFFLIESSTATE_SPAWNTWO && _dukeoffliesData.dukeofflies->getStruct().currentX == 4 && _dukeoffliesData.dukeofflies->getStruct().isSpawn)
		{
			spawnAttackFly(2);
			_dukeoffliesData.dukeofflies->spawnPause();
		}
	}
	else if (_bossSelect == BOSSSELECT_MONSTRO && _bossInit)
	{
		_monstroData.monstro->update(_player->getBody().x, _player->getBody().y);
	}
	else if (_bossSelect == BOSSSELECT_MEGAMAW && _bossInit)
	{
		_megamawData.megamaw->update(_player->getBody().x, _player->getBody().y);
	}
	_sixWayBullet->update();
	collision();
	bulletEnemyCollision();
}

void enemyManager::render(void)
{
	for (_viBlood = _vBlood.begin(); _viBlood != _vBlood.end(); ++_viBlood)
	{
		_viBlood->img->render(getMemDC(), _viBlood->x - CAMERAMANAGER->getX(), _viBlood->y - CAMERAMANAGER->getY());
	}
	if (_bossSelect == BOSSSELECT_DUKEOFFLLIES && _bossInit)
	{
		_dukeoffliesData.dukeofflies->render();
	}
	else if (_bossSelect == BOSSSELECT_MONSTRO && _bossInit)
	{
		_monstroData.monstro->render();
	}
	else if (_bossSelect == BOSSSELECT_MEGAMAW && _bossInit)
	{
		_megamawData.megamaw->render();
	}
	_sixWayBullet->render();
	for (_viGaper = _vGaper.begin(); _viGaper != _vGaper.end(); ++_viGaper)
	{
		_viGaper->gaper->render();
	}
	for (_viClotty = _vClotty.begin(); _viClotty != _vClotty.end(); ++_viClotty)
	{
		_viClotty->clotty->render();
	}
	for (_viHorf = _vHorf.begin(); _viHorf != _vHorf.end(); ++_viHorf)
	{
		_viHorf->horf->render();
	}
	for (_viAttackFly = _vAttackFly.begin(); _viAttackFly != _vAttackFly.end(); ++_viAttackFly)
	{
		_viAttackFly->attackFly->render();
	}
	for (_viLevel2Fly = _vLevel2Fly.begin(); _viLevel2Fly != _vLevel2Fly.end(); ++_viLevel2Fly)
	{
		_viLevel2Fly->level2Fly->render();
	}
	for (_viBlubber = _vBlubber.begin(); _viBlubber != _vBlubber.end(); ++_viBlubber)
	{
		_viBlubber->blubber->render();
	}
	for (_viCharger = _vCharger.begin(); _viCharger != _vCharger.end(); ++_viCharger)
	{
		_viCharger->charger->render();
	}
	for (_viTumor = _vTumor.begin(); _viTumor != _vTumor.end(); ++_viTumor)
	{
		_viTumor->tumor->render();
	}
	EFFECTMANAGER->render();
}

void enemyManager::removeGaper(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vGaper[arrNum].gaper->getBody().x - CAMERAMANAGER->getX(), _vGaper[arrNum].gaper->getBody().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vGaper[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	if (_vGaper[arrNum].gaper->getHorfRandomSpawnValue() < 3)
	{
		horfData _horfData;
		ZeroMemory(&_horfData, sizeof(horfData));
		_horfData.horf = new horfMinion;
		_horfData.horf->init(_vGaper[arrNum].gaper->getBody().x, _vGaper[arrNum].gaper->getBody().y);
		_horfData.pos = _vGaper[arrNum].pos;
		_vHorf.push_back(_horfData);
		_fieldMonsterNum++;
	}
	SOUNDMANAGER->stop("zombie walker kid");
	SAFE_DELETE(_vGaper[arrNum].gaper);
	_vGaper.erase(_vGaper.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeClotty(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vClotty[arrNum].clotty->getStruct().x - CAMERAMANAGER->getX(), _vClotty[arrNum].clotty->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vClotty[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vClotty[arrNum].clotty);
	_vClotty.erase(_vClotty.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeHorf(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vHorf[arrNum].horf->getStruct().x - CAMERAMANAGER->getX(), _vHorf[arrNum].horf->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vHorf[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vHorf[arrNum].horf);
	_vHorf.erase(_vHorf.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeAttackFly(int arrNum)
{
	EFFECTMANAGER->play("flyDieEffect", _vAttackFly[arrNum].attackFly->getStruct().x - CAMERAMANAGER->getX(), _vAttackFly[arrNum].attackFly->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vAttackFly[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vAttackFly[arrNum].attackFly);
	_vAttackFly.erase(_vAttackFly.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeLevel2Fly(int arrNum)
{
	EFFECTMANAGER->play("flyDieEffect", _vLevel2Fly[arrNum].level2Fly->getStruct().x - CAMERAMANAGER->getX(), _vLevel2Fly[arrNum].level2Fly->getStruct().y - CAMERAMANAGER->getY());
	_sixWayBullet->fire(_vLevel2Fly[arrNum].level2Fly->getStruct().x, _vLevel2Fly[arrNum].level2Fly->getStruct().y, 5.0f);
	_map->monsterDelete(_vLevel2Fly[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vLevel2Fly[arrNum].level2Fly);
	_vLevel2Fly.erase(_vLevel2Fly.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeBlubber(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vBlubber[arrNum].blubber->getStruct().x - CAMERAMANAGER->getX(), _vBlubber[arrNum].blubber->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vBlubber[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vBlubber[arrNum].blubber);
	_vBlubber.erase(_vBlubber.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeCharger(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vCharger[arrNum].charger->getStruct().x - CAMERAMANAGER->getX(), _vCharger[arrNum].charger->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vCharger[arrNum].pos);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	SAFE_DELETE(_vCharger[arrNum].charger);
	_vCharger.erase(_vCharger.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeTumor(int arrNum)
{
	EFFECTMANAGER->play("monsterDieEffect", _vTumor[arrNum].tumor->getStruct().x - CAMERAMANAGER->getX(), _vTumor[arrNum].tumor->getStruct().y - CAMERAMANAGER->getY());
	_map->monsterDelete(_vTumor[arrNum].pos);
	SAFE_DELETE(_vTumor[arrNum].tumor);
	SOUNDMANAGER->stop("monster die");
	SOUNDMANAGER->play("monster die", VOLUME->getSfxVolume() / 10);
	_vTumor.erase(_vTumor.begin() + arrNum);
	_fieldMonsterNum--;
}

void enemyManager::removeDukeOfflies(void)
{
	EFFECTMANAGER->play("largeBloodEffect", _dukeoffliesData.dukeofflies->getStruct().x - CAMERAMANAGER->getX(), _dukeoffliesData.dukeofflies->getStruct().y - CAMERAMANAGER->getY());
	_bossSelect = BOSSSELECT_NONE;
	SOUNDMANAGER->play("boss die", VOLUME->getSfxVolume() / 10);
	_map->monsterDelete(_dukeoffliesData.pos);
	SOUNDMANAGER->stop("duke spawn one");
	SOUNDMANAGER->stop("duke spawn two");
	SAFE_DELETE(_dukeoffliesData.dukeofflies);
	_fieldMonsterNum--;
}

void enemyManager::removeMonstro(void)
{
	EFFECTMANAGER->play("largeBloodEffect", _monstroData.monstro->getStruct().x - CAMERAMANAGER->getX(), _monstroData.monstro->getStruct().y - CAMERAMANAGER->getY());
	_bossSelect = BOSSSELECT_NONE;
	SOUNDMANAGER->play("boss die", VOLUME->getSfxVolume() / 10);
	_map->monsterDelete(_monstroData.pos);
	SOUNDMANAGER->stop("monstro fire");
	SOUNDMANAGER->stop("monstro jump");
	SAFE_DELETE(_monstroData.monstro);
	_fieldMonsterNum--;
}

void enemyManager::removeMegamaw(void)
{
	EFFECTMANAGER->play("largeBloodEffect", _megamawData.megamaw->getStruct().x - CAMERAMANAGER->getX(), _megamawData.megamaw->getStruct().y - CAMERAMANAGER->getY());
	_bossSelect = BOSSSELECT_NONE;
	SOUNDMANAGER->play("boss die", VOLUME->getSfxVolume() / 10);
	_map->monsterDelete(_megamawData.pos);
	SOUNDMANAGER->stop("megamaw fire1");
	SOUNDMANAGER->stop("megamaw fire2");
	SAFE_DELETE(_megamawData.megamaw);
	_fieldMonsterNum--;
}

void enemyManager::tileSetUp(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map->getTiles()[i].rc.left > -TILESIZE + CAMERAMANAGER->getX() && _map->getTiles()[i].rc.right < CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_map->getTiles()[i].rc.top >-TILESIZE + CAMERAMANAGER->getY() && _map->getTiles()[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
		{
			tileVec.push_back(_map->getTiles()[i]);
			attributeVec.push_back(_map->getAttribute()[i]);
		}
	}
}


void enemyManager::spawnAttackFly(int num)
{
	for (int i = 0; i < num; i++)
	{
		attackFlyData _attackFlyData;
		ZeroMemory(&_attackFlyData, sizeof(attackFlyData));
		_attackFlyData.attackFly = new attackFlyMinion;
		_attackFlyData.attackFly->init(_dukeoffliesData.dukeofflies->getStruct().x - 64 + i * 100, _dukeoffliesData.dukeofflies->getStruct().y);
		_vAttackFly.push_back(_attackFlyData);
		_fieldMonsterNum++;
	}
}

