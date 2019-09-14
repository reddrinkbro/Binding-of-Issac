#include "stdafx.h"
#include "player.h"
#include "dungeonMap.h"
#include "itemManager.h"
#include "objectManager.h"
#include "enemyManager.h"
void player::objectCollision(void)
{
	RECT rcCollision;
	RECT rc;
	int tileIndex[2];
	int tileX, tileY;
	rcCollision = _body.rc;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_body.bodyState)
	{
	case BODYSTATE_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
	case BODYSTATE_RIGHT:
		tileIndex[0] = tileX + tileY * TILEX + 1;
		tileIndex[1] = tileX + (tileY + 1) * TILEX + 1;
		break;
	case BODYSTATE_UP:
		tileIndex[0] = tileX + tileY * TILEY;
		tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
	case BODYSTATE_DOWN:
		tileIndex[0] = (tileX + tileY * TILEY) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}
	for (int i = 0; i < 2; i++)
	{
		if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_NO_BREAK) &&
			IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &CollisionAreaResizing(rcCollision,15,20,20,-8)))
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				break;

			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				break;

			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				break;

			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				break;
			}
		}
		else if ((_map->getAttribute()[tileIndex[i]] == ATTR_BLOCK_BREAK) &&
			IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &CollisionAreaResizing(rcCollision, 15, 20, 20, -8)))
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				break;
			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				break;
			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				break;
			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				break;
			}
		}
		else if ((_map->getAttribute()[tileIndex[i]] == ATTR_STONE) &&
			IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &CollisionAreaResizing(rcCollision, 15, 20, 20, 10)))
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				break;

			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				break;

			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				break;

			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				break;
			}
			if (_playerUI->getCoinUI().size() < 5) return;
			coinGetUsing(true, 5);
			if (_map->getTiles()[tileIndex[i]].item == ITEM_PENTAGRAM)
			{
				_state = ISAACSTATE_ITEMGET;
				_item->getPentagram()[0].pentagram->stop();
				_item->getPentagram()[0].pentagram->gainPentagram(_head.x- 20, _head.y - 32);
			}
			else if (_map->getTiles()[tileIndex[i]].item == ITEM_OUIJABOARD)
			{
				_state = ISAACSTATE_ITEMGET;
				_item->getOuijaboard()[0].ouijaboard->stop();
				_item->getOuijaboard()[0].ouijaboard->gainOuijaboard(_head.x - 20, _head.y - 32);
			}
			else if (_map->getTiles()[tileIndex[i]].item == ITEM_FAMILIAR)
			{
				_state = ISAACSTATE_ITEMGET;
				_item->getGhostBaby()[0].ghostBaby->stop();
				_item->getGhostBaby()[0].ghostBaby->gainGhostBaby(_head.x - 20, _head.y - 32);
			}
		}
		else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP1) &&
			IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &CollisionAreaResizing(rcCollision, 15, 20, 20, -8)))
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				break;
			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				break;
			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				break;
			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				break;
			}
		}
		else if ((_map->getAttribute()[tileIndex[i]] == ATTR_POOP2) &&
			IntersectRect(&rc, &_map->getTiles()[tileIndex[i]].rc, &CollisionAreaResizing(rcCollision, 15, 20, 20, -8)))
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				break;
			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				break;
			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				break;
			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				break;
			}
		}
	}
	
	rcCollision = RectMakeCenter(_body.x, _body.y, _body.img->getFrameWidth(), _body.img->getFrameHeight());
	_body.rc = rcCollision;
	for (int i = 0; i < _object->getChest().size(); i++)
	{
		if (IntersectRect(&rcCollision, &_body.rc, &CollisionAreaResizing(_object->getChest()[i].chest->getStruct().rc, 30, 50, 30, 20))
			&& _object->getChest()[i].chest->getStruct().state != CHESTSTATE_OPEN)
		{
			switch (_body.bodyState)
			{
			case BODYSTATE_LEFT:
				_body.x += _body.currentSpeed;
				if (_playerUI->getKeyUI().size() != 0)
				{
					SOUNDMANAGER->play("chest open", VOLUME->getSfxVolume() / 10);
					int randomPill = RND->getInt(4);
					_object->getChest()[i].chest->setOpen();
					_playerUI->decreaseKey();
					_item->bombSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->coinSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->hpSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->pillSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y, randomPill);
				}
				break;

			case BODYSTATE_RIGHT:
				_body.x -= _body.currentSpeed;
				if (_playerUI->getKeyUI().size() != 0)
				{
					SOUNDMANAGER->play("chest open", VOLUME->getSfxVolume() / 10);
					int randomPill = RND->getInt(4);
					_object->getChest()[i].chest->setOpen();
					_playerUI->decreaseKey();
					_item->bombSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->coinSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->hpSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->pillSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y, randomPill);
				}
				break;

			case BODYSTATE_UP:
				_body.y += _body.currentSpeed;
				if (_playerUI->getKeyUI().size() != 0)
				{
					SOUNDMANAGER->play("chest open", VOLUME->getSfxVolume() / 10);
					int randomPill = RND->getInt(4);
					_object->getChest()[i].chest->setOpen();
					_playerUI->decreaseKey();
					_item->bombSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->coinSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->hpSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->pillSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y, randomPill);
				}
				break;

			case BODYSTATE_DOWN:
				_body.y -= _body.currentSpeed;
				if (_playerUI->getKeyUI().size() != 0)
				{
					SOUNDMANAGER->play("chest open", VOLUME->getSfxVolume() / 10);
					int randomPill = RND->getInt(4);
					_object->getChest()[i].chest->setOpen();
					_playerUI->decreaseKey();
					_item->bombSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->coinSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->hpSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y);
					_item->pillSet(_object->getChest()[i].chest->getStruct().x, _object->getChest()[i].chest->getStruct().y, randomPill);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _object->getSpikeLarge().size(); i++)
	{
		if (IntersectRect(&rc, &CollisionAreaResizing(_object->getSpikeLarge()[i].spike->getStruct().rc, 15, 10, 15, 40) , &_body.rc) &&
			_object->getSpikeLarge()[i].spike->getStruct().currentY == _object->getSpikeLarge()[i].spike->getStruct().img->getMaxFrameY())
		{
			playerHit();
		}
	}
	for (int i = 0; i < _object->getSpikeSmall().size(); i++)
	{
		if (IntersectRect(&rc, &CollisionAreaResizing(_object->getSpikeSmall()[i].spike->getStruct().rc, 15, 10, 15, 40), &_body.rc) &&
			_object->getSpikeSmall()[i].spike->getStruct().currentY == _object->getSpikeSmall()[i].spike->getStruct().img->getMaxFrameY())
		{
			playerHit();
		}
	}
	int index;
	switch (_body.bodyState)
	{
	case BODYSTATE_LEFT:
		index = tileX + tileY * TILEX + TILEX;
		break;
	case BODYSTATE_RIGHT:
		index = tileX + tileY * TILEX + TILEX;
		break;
	case BODYSTATE_UP:
		tileY = rcCollision.bottom / TILESIZE;
		index = tileX + tileY * TILEX;
		break;
	case BODYSTATE_DOWN:
		tileY = rcCollision.bottom / TILESIZE;
		index = tileX + tileY * TILEX;
		break;
	}
	if ((_map->getAttribute()[index] == ATTR_SPIKE) &&
		IntersectRect(&rc, &_map->getTiles()[index].rc, &rcCollision))
	{
		playerHit();
	}
	else if ((_map->getAttribute()[index] == ATTR_SPIDERWEB) &&
		IntersectRect(&rc, &_map->getTiles()[index].rc, &rcCollision))
	{
		_body.currentSpeed = _body.currentSpeed / 1.2f;
	}
	for (int i = 0; i < _object->getExit().size(); i++)
	{
		if (_enemy->getFieldMonsterNum() > 0) return;
		if (IntersectRect(&rcCollision, &_body.rc, &CollisionAreaResizing(_object->getExit()[i]->getStruct().rc, 50, 50, 50, 70)))
		{
			_state = ISAACSTATE_MAPMOVE;
			_body.x = _object->getExit()[i]->getStruct().x - 25;
			_body.y = _object->getExit()[i]->getStruct().y - 100;
			SOUNDMANAGER->stop("boss die");
		}
	}

	
}