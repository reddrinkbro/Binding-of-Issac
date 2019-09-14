#include "stdafx.h"
#include "itemManager.h"
#include "dungeonMap.h"

void itemManager::objectExplosionCollision(int arrNum)
{
	RECT rcCollision;
	RECT rc;
	int tileIndex[9];
	int tileX, tileY;
	rcCollision = _vBomb[arrNum].bomb->getStruct().rc;
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	tileIndex[0] = tileX + tileY * TILEX;
	tileIndex[1] = tileX + tileY * TILEX - 1;
	tileIndex[2] = tileX + tileY * TILEX + 1;
	tileIndex[3] = tileX + tileY * TILEX + TILEX;
	tileIndex[4] = tileX + tileY * TILEX - TILEX;
	tileIndex[5] = tileX + (tileY + 1) * TILEX - 1;
	tileIndex[6] = tileX + (tileY + 1) *  TILEX + 1;
	tileIndex[7] = tileX + (tileY - 1) * TILEX - 1;
	tileIndex[8] = tileX + (tileY + 1) * TILEX + 1;
	for (int i = 0; i < 9; i++)
	{
		if (_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_NO_BREAK)
		{
			_map->objectDelete(tileIndex[i]);
		}
	}
}