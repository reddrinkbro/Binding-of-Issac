#include "stdafx.h"
#include "itemManager.h"
#include "player.h"

void itemManager::playerExplosionCollision(int arrNum)
{
	RECT rcCollision;
	RECT rc;
	rcCollision = _vBomb[arrNum].bomb->getStruct().rc;
	RECT rcPlayer = _player->getBody().rc;
	int tileIndex[9];
	int tileX, tileY;

	if (IntersectRect(&rc, &rcPlayer, &CollisionAreaResizing(rcCollision, -20, -20, -20, -20)))
	{
		_player->playerHit();
	}
}