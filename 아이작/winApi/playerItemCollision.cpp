#include "stdafx.h"
#include "itemManager.h"
#include "player.h"
#include "dungeonMap.h"
void itemManager::playerItemCollision(void)
{
	RECT rcTemp;
	RECT playerRc = _player->getBody().rc;
	for (int i = 0; i < _vCoin.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vCoin[i].coin->getStruct().rc, 20, 30, 20, 0))
			&& _vCoin[i].coin->getStruct().currnetX == _vCoin[i].coin->getStruct().img->getMaxFrameX())
		{
			removeCoin(i);
			_player->coinGetUsing(false, 0);
		}
	}
	for (int i = 0; i < _vBomb.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vBomb[i].bomb->getStruct().rc, 20, 20, 30, 10)))
		{
			if (!_vBomb[i].bomb->getStruct().isMove)
			{
				removeBomb(i);
				_player->bombGetUsing(false);
			}
		}
	}
	for (int i = 0; i < _vHealthPoint.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vHealthPoint[i].healthPoint->getStruct().rc, 15, 0, 15, 0)))
		{
			if (!_vHealthPoint[i].healthPoint->getStruct().isMove)
			{
				if (_player->getBody().currentHp < _player->getBody().maxHp)
				{
					removeHealthPoint(i);
					_player->healthPointIncrease();
				}
				else
				{
					_vHealthPoint[i].healthPoint->move(_player->getBody().x, _player->getBody().y, _player->getBody().currentSpeed);
				}
			}
		}
	}
	for (int i = 0; i < _vKey.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vKey[i].key->getStruct().rc, 10, -5, 10, -20)))
		{
			if (!_vKey[i].key->getStruct().isMove)
			{
				removeKey(i);
				_player->keyGetUsing(false);
			}
		}
	}
	for (int i = 0; i < _vPillATKUP.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vPillATKUP[i].pillATKUP->getStruct().rc, 15, 0, 15, -20)))
		{
			if (!_vPillATKUP[i].pillATKUP->getStruct().isMove)
			{
				SOUNDMANAGER->play("power up1", VOLUME->getSfxVolume() / 10);
				removePillAtkUp(i);
				_player->setState(ISAACSTATE_BUFF);
				_player->atkChange(true);
			}
		}
	}
	for (int i = 0; i < _vPillSPEEDUP.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vPillSPEEDUP[i].pillSPEEDUP->getStruct().rc, 12, 0, 12, 0)))
		{
			if (!_vPillSPEEDUP[i].pillSPEEDUP->getStruct().isMove)
			{
				SOUNDMANAGER->play("power up1", VOLUME->getSfxVolume() / 10);
				removepillSpeedUp(i);
				_player->setState(ISAACSTATE_BUFF);
				_player->speedChanage(true);
			}
		}
	}
	for (int i = 0; i < _vPillATKDOWN.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vPillATKDOWN[i].pillATKDOWN->getStruct().rc, 15, 0, 15, -20)))
		{
			if (!_vPillATKDOWN[i].pillATKDOWN->getStruct().isMove)
			{
				SOUNDMANAGER->play("thumbs down", VOLUME->getSfxVolume() / 10);
				removePillAtkDown(i);
				_player->setState(ISAACSTATE_DEBUFF);
				_player->atkChange(false);
			}
		}
	}
	for (int i = 0; i < _vPillSPEEDDOWN.size(); i++)
	{
		if (IntersectRect(&rcTemp, &playerRc, &CollisionAreaResizing(_vPillSPEEDDOWN[i].pillSPEEDDOWN->getStruct().rc, 12, 0, 12, 0)))
		{
			if (!_vPillSPEEDDOWN[i].pillSPEEDDOWN->getStruct().isMove)
			{
				SOUNDMANAGER->play("thumbs down", VOLUME->getSfxVolume() / 10);
				removePillSpeedDown(i);
				_player->setState(ISAACSTATE_DEBUFF);
				_player->speedChanage(false);
			}
		}
	}
}