#include "stdafx.h"
#include "player.h"
#include "dungeonMap.h"
#include "objectManager.h"

void player::bulletCollision(void)
{
	vector<tagBullet> playerBullet;
	vector<tagBullet> familiarBullet;

	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		playerBullet.push_back(_baseBullet->getBaseBullet()[i]);
	}

	RECT rcTemp;
	for (int i = 0; i < playerBullet.size(); i++)
	{
		if (playerBullet[i].rc.right < CAMERAMANAGER->getX() || playerBullet[i].rc.left > CAMERAMANAGER->getGameMaxRenderX() -64 + CAMERAMANAGER->getX() ||
			playerBullet[i].rc.bottom <CAMERAMANAGER->getY() || playerBullet[i].rc.top > CAMERAMANAGER->getGameMaxRenderY() -64 + CAMERAMANAGER->getY())
		{
			EFFECTMANAGER->play("baseBulletEffect", playerBullet[i].x - CAMERAMANAGER->getX(), playerBullet[i].y - CAMERAMANAGER->getY());
			_baseBullet->removeBullet(i);
			break;
		}
		if (!_ouijaboardOn)
		{
			for (int j = 0; j < tileVec.size(); j++)
			{
				if (tileVec[j].rc.left > -TILESIZE + CAMERAMANAGER->getX() && tileVec[j].rc.right < CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
					tileVec[j].rc.top >-TILESIZE + CAMERAMANAGER->getY() && tileVec[j].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
				{
					if (IntersectRect(&rcTemp, &tileVec[j].rc, &CollisionAreaResizing(playerBullet[i].rc, 0, 0))
						&& (attributeVec[j] == ATTR_BLOCK_NO_BREAK || attributeVec[j] == ATTR_BLOCK_BREAK || attributeVec[j] == ATTR_STONE))
					{
						EFFECTMANAGER->play("baseBulletEffect", playerBullet[i].x - CAMERAMANAGER->getX(), playerBullet[i].y - CAMERAMANAGER->getY());
						_baseBullet->removeBullet(i);
						break;
					}
				}
			}
			for (int j = 0; j < _object->getBasicPoop().size(); j++)
			{
				if (IntersectRect(&rcTemp, &CollisionAreaResizing(_object->getBasicPoop()[j].poop->getStruct().rc, 5, 20, 5, 15), &CollisionAreaResizing(playerBullet[i].rc, 0, 0)))
				{
					EFFECTMANAGER->play("baseBulletEffect", playerBullet[i].x - CAMERAMANAGER->getX(), playerBullet[i].y - CAMERAMANAGER->getY());
					_object->getBasicPoop()[j].poop->hit();
					if (_object->getBasicPoop()[j].poop->getStruct().currentX > _object->getBasicPoop()[j].poop->getStruct().img->getMaxFrameX())
					{
						_object->removeBasicPoop(j);
					}
					_baseBullet->removeBullet(i);
					break;
				}
			}
			for (int j = 0; j < _object->getRedPoop().size(); j++)
			{
				if (IntersectRect(&rcTemp, &CollisionAreaResizing(_object->getRedPoop()[j].poop->getStruct().rc, 5, 20, 5, 15), &CollisionAreaResizing(playerBullet[i].rc, 0, 0)))
				{
					EFFECTMANAGER->play("baseBulletEffect", playerBullet[i].x - CAMERAMANAGER->getX(), playerBullet[i].y - CAMERAMANAGER->getY());
					_object->getRedPoop()[j].poop->hit();
					if (_object->getRedPoop()[j].poop->getStruct().currentX > _object->getRedPoop()[j].poop->getStruct().img->getMaxFrameX())
					{
						_object->removeRedPoop(j);
					}
					_baseBullet->removeBullet(i);
					break;
				}
			}
		}
	}
	if (_familiarOn)
	{
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			familiarBullet.push_back(_familiar->getFamiliarBullet()->getBullet()[i]);
		}
		for (int i = 0; i < familiarBullet.size(); i++)
		{
			if (familiarBullet[i].rc.right < CAMERAMANAGER->getX() || familiarBullet[i].rc.left > CAMERAMANAGER->getGameMaxRenderX() - 64 + CAMERAMANAGER->getX() ||
				familiarBullet[i].rc.bottom <CAMERAMANAGER->getY() || familiarBullet[i].rc.top > CAMERAMANAGER->getGameMaxRenderY() - 64 + CAMERAMANAGER->getY())
			{
				_familiar->getFamiliarBullet()->removeBullet(i);
				break;
			}
		}
	}
}