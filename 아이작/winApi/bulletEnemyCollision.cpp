#include "stdafx.h"
#include "enemyManager.h"
#include "dungeonMap.h"

void enemyManager::bulletEnemyCollision(void)
{
	RECT rcTemp;
	RECT rcCollision;
	RECT rc;
	int tileIndex;
	int tileX, tileY;
	for (int i = 0; i < _vClotty.size(); i++)
	{
		for (int j = 0; j < _vClotty[i].clotty->getEnemyBullet()->getBullet().size(); j++)
		{
			RECT rcCollision = _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc;
			tileX = rcCollision.left / TILESIZE;
			tileY = rcCollision.top / TILESIZE;
			tileIndex = tileX + tileY * TILEX;
			
			if (_vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc.right < CAMERAMANAGER->getX() || _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc.left > CAMERAMANAGER->getGameMaxRenderX() - 64 + CAMERAMANAGER->getX() ||
				_vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc.bottom <CAMERAMANAGER->getY() || _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc.top > CAMERAMANAGER->getGameMaxRenderY() - 64 + CAMERAMANAGER->getY())
			{
				EFFECTMANAGER->play("baseBulletEffect", _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].x - CAMERAMANAGER->getX(), _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].y - CAMERAMANAGER->getY());
				_vClotty[i].clotty->getEnemyBullet()->removeBullet(j);
				break;
			}
			if (IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_vClotty[i].clotty->getEnemyBullet()->getBullet()[j].rc, 0, 0))
				&& (_map->getAttribute()[tileIndex] == ATTR_BLOCK_NO_BREAK || _map->getAttribute()[tileIndex] == ATTR_BLOCK_BREAK))
			{
				EFFECTMANAGER->play("baseBulletEffect", _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].x - CAMERAMANAGER->getX(), _vClotty[i].clotty->getEnemyBullet()->getBullet()[j].y - CAMERAMANAGER->getY());
				_vClotty[i].clotty->getEnemyBullet()->removeBullet(j);
				break;
			}
		}
	}
}
