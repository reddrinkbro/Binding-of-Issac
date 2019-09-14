#include "stdafx.h"
#include "enemyManager.h"
#include "dungeonMap.h"

void enemyManager::objectEnemyCollision(COLLISIONMONSTER collisionMonster, int arrNum)
{
	RECT rcCollision;
	RECT rc;
	int tileIndex[4];
	int tileX, tileY;
	int randomDirection = RND->getInt(3);
	if (collisionMonster == COLLISIONMONSTER_BLUBBER) rcCollision = CollisionAreaResizing(_vBlubber[arrNum].blubber->getStruct().rc, 30, 0, -20, 0);
	else if (collisionMonster == COLLISIONMONSTER_CHARGER) rcCollision = _vCharger[arrNum].charger->getStruct().rc;
	else if (collisionMonster == COLLISIONMONSTER_CLOTTY) rcCollision = _vClotty[arrNum].clotty->getStruct().rc;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;
	if (collisionMonster == COLLISIONMONSTER_BLUBBER)
	{
		switch (_vBlubber[arrNum].blubber->getStruct().state)
		{
		case BLUBBERSTATE_LEFT:
			tileIndex[0] = tileX + (tileY - 1) * TILEX;
			tileIndex[1] = tileX + tileY * TILEX;
			break;
		case BLUBBERSTATE_RIGHT:
			tileIndex[0] = tileX + tileY * TILEX + 1;
			tileIndex[1] = tileX + (tileY + 1) * TILEX;
			break;
		case BLUBBERSTATE_UP:
			tileIndex[0] = tileX + tileY * TILEY;
			tileIndex[1] = tileX + tileY * TILEY - TILEX + 1;
			break;
		case BLUBBERSTATE_DOWN:
			tileIndex[0] = tileX + tileY * TILEY + TILEX;
			tileIndex[1] = tileX + tileY * TILEY + TILEX - 1;
			break;
		}
		for (int i = 0; i < 2; i++)
		{
			if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_NO_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vBlubber[arrNum].blubber->getStruct().state)
				{
				case BLUBBERSTATE_LEFT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_RIGHT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_UP:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_DOWN:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vBlubber[arrNum].blubber->getStruct().state)
				{
				case BLUBBERSTATE_LEFT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);

					break;
				case BLUBBERSTATE_RIGHT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_UP:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_DOWN:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP1) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vBlubber[arrNum].blubber->getStruct().state)
				{
				case BLUBBERSTATE_LEFT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);

					break;
				case BLUBBERSTATE_RIGHT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_UP:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_DOWN:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP2) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vBlubber[arrNum].blubber->getStruct().state)
				{
				case BLUBBERSTATE_LEFT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);

					break;
				case BLUBBERSTATE_RIGHT:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_UP:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_DOWN);
					break;
				case BLUBBERSTATE_DOWN:
					if (randomDirection == 0)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_RIGHT);
					else if (randomDirection == 1)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_UP);
					else if (randomDirection == 2)_vBlubber[arrNum].blubber->setState(BLUBBERSTATE_LEFT);
					break;
				}
			}
		}
		rcCollision = RectMakeCenter(_vBlubber[arrNum].blubber->getStruct().x, _vBlubber[arrNum].blubber->getStruct().y, _vBlubber[arrNum].blubber->getStruct().img->getFrameWidth(), _vBlubber[arrNum].blubber->getStruct().img->getFrameHeight());
		_vBlubber[arrNum].blubber->setRECT(CollisionAreaResizing(rcCollision, -30, 0, 20, 0));
	}
	else if (collisionMonster == COLLISIONMONSTER_CHARGER)
	{
		switch (_vCharger[arrNum].charger->getStruct().state)
		{
		case CHARGERSTATE_LEFT:
			tileIndex[0] = tileX + (tileY - 1) * TILEX;
			tileIndex[1] = tileX + tileY * TILEX;
			break;
		case CHARGERSTATE_RIGHT:
			tileIndex[0] = tileX + tileY * TILEX + 1;
			tileIndex[1] = tileX + (tileY + 1) * TILEX;
			break;
		case CHARGERSTATE_UP:
			tileIndex[0] = tileX + tileY * TILEY;
			tileIndex[1] = tileX + tileY * TILEY - TILEX + 1;
			break;
		case CHARGERSTATE_DOWN:
			tileIndex[0] = tileX + tileY * TILEY + TILEX;
			tileIndex[1] = tileX + tileY * TILEY + TILEX - 1;
			break;
		}
		for (int i = 0; i < 2; i++)
		{
			if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_NO_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vCharger[arrNum].charger->getStruct().state)
				{
				case CHARGERSTATE_LEFT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_RIGHT);
					break;
				case CHARGERSTATE_RIGHT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_LEFT);
					break;
				case CHARGERSTATE_UP:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_DOWN);
					break;
				case CHARGERSTATE_DOWN:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_UP);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vCharger[arrNum].charger->getStruct().state)
				{
				case CHARGERSTATE_LEFT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_RIGHT);
					break;
				case CHARGERSTATE_RIGHT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_LEFT);
					break;
				case CHARGERSTATE_UP:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_DOWN);
					break;
				case CHARGERSTATE_DOWN:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_UP);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP1) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vCharger[arrNum].charger->getStruct().state)
				{
				case CHARGERSTATE_LEFT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_RIGHT);
					break;
				case CHARGERSTATE_RIGHT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_LEFT);
					break;
				case CHARGERSTATE_UP:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_DOWN);
					break;
				case CHARGERSTATE_DOWN:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_UP);
					break;
				}
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP2) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vCharger[arrNum].charger->getStruct().state)
				{
				case CHARGERSTATE_LEFT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_RIGHT);
					break;
				case CHARGERSTATE_RIGHT:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_LEFT);
					break;
				case CHARGERSTATE_UP:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_DOWN);
					break;
				case CHARGERSTATE_DOWN:
					_vCharger[arrNum].charger->setState(CHARGERSTATE_UP);
					break;
				}
			}
		}
		rcCollision = RectMakeCenter(_vCharger[arrNum].charger->getStruct().x, _vCharger[arrNum].charger->getStruct().y, _vCharger[arrNum].charger->getStruct().img->getFrameWidth(), _vCharger[arrNum].charger->getStruct().img->getFrameHeight());
		_vCharger[arrNum].charger->setRECT(rcCollision);
	}
	else if (collisionMonster == COLLISIONMONSTER_CLOTTY)
	{
		switch (_vClotty[arrNum].clotty->getStruct().state)
		{
		case CLOTTYSTATE_LEFT:
			tileIndex[0] = tileX + tileY * TILEX +1;
			tileIndex[1] = tileX + tileY * TILEX + TILEX +1;
			break;
		case CLOTTYSTATE_RIGHT:
			tileIndex[0] = tileX + tileY * TILEX +1;
			tileIndex[1] = tileX + tileY * TILEX+ TILEX +1;
			break;
		}
		for (int i = 0; i < 2; i++)
		{
			if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_NO_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vClotty[arrNum].clotty->getStruct().state)
				{
				case CLOTTYSTATE_LEFT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_RIGHT);
					break;
				case CLOTTYSTATE_RIGHT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_LEFT);
					break;
				}
				break;
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_BREAK) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vClotty[arrNum].clotty->getStruct().state)
				{
				case CLOTTYSTATE_LEFT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_RIGHT);
					break;
				case CLOTTYSTATE_RIGHT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_LEFT);
					break;
				}
				break;
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP1) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vClotty[arrNum].clotty->getStruct().state)
				{
				case CLOTTYSTATE_LEFT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_RIGHT);
					break;
				case CLOTTYSTATE_RIGHT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_LEFT);
					break;
				}
				break;
			}
			else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP2) &&
				IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &rcCollision))
			{
				switch (_vClotty[arrNum].clotty->getStruct().state)
				{
				case CLOTTYSTATE_LEFT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_RIGHT);
					break;
				case CLOTTYSTATE_RIGHT:
					_vClotty[arrNum].clotty->setState(CLOTTYSTATE_LEFT);
					break;
				}
				break;
			}
		}
		rcCollision = RectMakeCenter(_vClotty[arrNum].clotty->getStruct().x, _vClotty[arrNum].clotty->getStruct().y, _vClotty[arrNum].clotty->getStruct().img->getFrameWidth(), _vClotty[arrNum].clotty->getStruct().img->getFrameHeight());
		_vClotty[arrNum].clotty->setRECT(rcCollision);
	}
}
