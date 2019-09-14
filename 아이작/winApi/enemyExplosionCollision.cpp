#include "stdafx.h"
#include "itemManager.h"
#include "enemyManager.h"

void itemManager::enemyExplosionCollision(int arrNum)
{
	RECT rcCollision;
	RECT rcEnemy;
	RECT rc;
	rcCollision = _vBomb[arrNum].bomb->getStruct().rc;

	for (int i = 0; i < _enemy->getAttackFly().size(); i++)
	{
		rcEnemy = _enemy->getAttackFly()[i].attackFly->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeAttackFly(i);
		}
	}
	for (int i = 0; i < _enemy->getBlubber().size(); i++)
	{
		rcEnemy = _enemy->getBlubber()[i].blubber->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeBlubber(i);
		}
	}
	for (int i = 0; i < _enemy->getCharger().size(); i++)
	{
		rcEnemy = _enemy->getCharger()[i].charger->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeCharger(i);
		}
	}
	for (int i = 0; i < _enemy->getClotty().size(); i++)
	{
		rcEnemy = _enemy->getClotty()[i].clotty->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeClotty(i);
		}
	}
	for (int i = 0; i < _enemy->getFrowningGaper().size(); i++)
	{
		rcEnemy = _enemy->getFrowningGaper()[i].gaper->getBody().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeGaper(i);
		}
	}
	for (int i = 0; i < _enemy->getHorf().size(); i++)
	{
		rcEnemy = _enemy->getHorf()[i].horf->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeHorf(i);
		}
	}
	for (int i = 0; i < _enemy->getLevel2Fly().size(); i++)
	{
		rcEnemy = _enemy->getLevel2Fly()[i].level2Fly->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeLevel2Fly(i);
		}
	}
	for (int i = 0; i < _enemy->getTumor().size(); i++)
	{
		rcEnemy = _enemy->getTumor()[i].tumor->getStruct().rc;
		if (IntersectRect(&rc, &rcEnemy, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
		{
			_enemy->removeTumor(i);
		}
	}
}