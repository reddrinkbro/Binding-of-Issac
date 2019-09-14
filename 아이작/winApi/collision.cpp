#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "dungeonMap.h"
void enemyManager::collision(void)
{
	RECT rcTemp;

	RECT playerRc = _player->getBody().rc;
	
	for (_viGaper = _vGaper.begin(); _viGaper != _vGaper.end(); ++_viGaper)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viGaper->gaper->getBody().rc, 15, -10, 15, 0), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viClotty = _vClotty.begin(); _viClotty != _vClotty.end(); ++_viClotty)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viClotty->clotty->getStruct().rc, 50, 50, 38, 0), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viHorf = _vHorf.begin(); _viHorf != _vHorf.end(); ++_viHorf)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viHorf->horf->getStruct().rc, 15, 15, 15, -15), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viAttackFly = _vAttackFly.begin(); _viAttackFly != _vAttackFly.end(); ++_viAttackFly)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viAttackFly->attackFly->getStruct().rc,17,0,17,-15), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viLevel2Fly = _vLevel2Fly.begin(); _viLevel2Fly != _vLevel2Fly.end(); ++_viLevel2Fly)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viLevel2Fly->level2Fly->getStruct().rc, 25, 25, 23, -10), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viBlubber = _vBlubber.begin(); _viBlubber != _vBlubber.end(); ++_viBlubber)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viBlubber->blubber->getStruct().rc, 40, 0, 40, 0), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	for (_viCharger = _vCharger.begin(); _viCharger != _vCharger.end(); ++_viCharger)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viCharger->charger->getStruct().rc, 20, 10, 15, 0), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}

	for (_viTumor = _vTumor.begin(); _viTumor != _vTumor.end(); ++_viTumor)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_viTumor->tumor->getStruct().rc, 25, 10, 25, 0), &playerRc))
		{
			_player->playerHit();
			break;
		}
	}
	if (_bossSelect == BOSSSELECT_DUKEOFFLLIES && _bossInit)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_dukeoffliesData.dukeofflies->getStruct().rc, 65, 30, 65, 15), &playerRc))
		{
			_player->playerHit();
		}
	}
	if (_bossSelect == BOSSSELECT_MONSTRO && _bossInit)
	{
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_monstroData.monstro->getStruct().rc, 20, 135, 20, 0), &playerRc))
		{
			if (_monstroData.monstro->getStruct().state == MONSTROSTATE_NONE)
			{
				_player->playerHit();
					
			}
			else if (_monstroData.monstro->getStruct().state == MONSTROSTATE_MOVE)
			{
				if (_monstroData.monstro->getStruct().currentX > 3)
				{
					_player->playerHit();
				}
			}
			else if (_monstroData.monstro->getStruct().state == MONSTROSTATE_JUMP)
			{
				if (_monstroData.monstro->getStruct().currentX > 5)
				{
					_player->playerHit();
				}
			}
		}
		for (int i = 0; i < _monstroData.monstro->getEnemyBullet()->getBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_monstroData.monstro->getEnemyBullet()->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_monstroData.monstro->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	if (_bossSelect == BOSSSELECT_MEGAMAW && _bossInit)
	{
		RECT enemyBullet;
		if (IntersectRect(&rcTemp, &CollisionAreaResizing(_megamawData.megamaw->getStruct().rc, 90, 0, 90, 0), &playerRc))
		{
			
			_player->playerHit();
		}
		for (int i = 0; i < _megamawData.megamaw->getEnemyBullet()->getBullet().size(); i++)
		{
			if (_megamawData.megamaw->getStruct().state == MEGAMAWSTATE_PATTERN1)
			{
				enemyBullet = _megamawData.megamaw->getEnemyBullet()->getBullet()[i].rc;
			}
			else
			{
				enemyBullet = CollisionAreaResizing(_megamawData.megamaw->getEnemyBullet()->getBullet()[i].rc, 45, 20, 45, 20);
			}
			if (IntersectRect(&rcTemp, &enemyBullet, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_megamawData.megamaw->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	//ÃÑ¾Ë Ãæµ¹
	
	for (_viClotty = _vClotty.begin(); _viClotty != _vClotty.end(); ++_viClotty)
	{
		for (int i = 0 ; i <_viClotty->clotty->getEnemyBullet()->getBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_viClotty->clotty->getEnemyBullet()->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_viClotty->clotty->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	for (_viHorf = _vHorf.begin(); _viHorf != _vHorf.end(); ++_viHorf)
	{
		for (int i = 0; i <_viHorf->horf->getEnemyBullet()->getBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_viHorf->horf->getEnemyBullet()->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_viHorf->horf->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	for (_viBlubber = _vBlubber.begin(); _viBlubber != _vBlubber.end(); ++_viBlubber)
	{
		for (int i = 0; i <_viBlubber->blubber->getEnemyBullet()->getBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_viBlubber->blubber->getEnemyBullet()->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_viBlubber->blubber->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	for (_viTumor = _vTumor.begin(); _viTumor != _vTumor.end(); ++_viTumor)
	{
		for (int i = 0; i <_viTumor->tumor->getEnemyBullet()->getBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_viTumor->tumor->getEnemyBullet()->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
			{
				_player->playerHit();
				_viTumor->tumor->getEnemyBullet()->removeBullet(i);
				break;
			}
		}
	}
	for (int i = 0; i < _sixWayBullet->getBullet().size(); i++)
	{
		if (IntersectRect(&rcTemp, &_sixWayBullet->getBullet()[i].rc, &CollisionAreaResizing(_player->getBody().rc, 10, 0, 10, 0)))
		{
			_player->playerHit();
			_sixWayBullet->removeBullet(i);
			break;
		}
	}
}