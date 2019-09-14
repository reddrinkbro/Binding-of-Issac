#include "stdafx.h"
#include "player.h"
#include "dungeonMap.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "objectManager.h"

void player::doorCollision(void)
{
	if (_enemy->getFieldMonsterNum() > 0)
	{
		_object->setDoor(false);
		return;
	}
	else _object->setDoor(true);
	
	int tileIndex;
	int tileX, tileY;
	RECT rcCollision = _body.rc;
	RECT rcTemp;
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;
	switch (_body.bodyState)
	{
	case BODYSTATE_UP:
		tileIndex = tileX + tileY * TILEY - TILEX;
		break;
	case BODYSTATE_DOWN:
		tileIndex = tileX + tileY * TILEY + TILEX;
		break;
	case BODYSTATE_LEFT:
		tileIndex = tileX + tileY * TILEX - 1;
		break;
	case BODYSTATE_RIGHT:
		tileIndex = tileX + tileY * TILEY + 1;
		break;
	}
	if(_map->getAttribute()[tileIndex] == ATTR_DOOR_UP && 
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, -25, 0, 0)))
	{
		_body.y -= 258;
		if(_familiarOn) _familiar->setY(_familiar->getFamiliar().y - 258);
		CAMERAMANAGER->cameraMoveY(CAMERAMOVE_UP, false);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setMinion();
		_object->setObject();
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_DOOR_DOWN &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, 0, 0, 25)))
	{
		_body.y += 258;
		if (_familiarOn)_familiar->setY(_familiar->getFamiliar().y + 258);
		CAMERAMANAGER->cameraMoveY(CAMERAMOVE_DOWN,false);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setMinion();
		_object->setObject();
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_DOOR_LEFT &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc,-40,0,0,0)))
	{
		_body.x -= 258;
		if (_familiarOn)_familiar->setX(_familiar->getFamiliar().x - 258);
		CAMERAMANAGER->cameraMoveX(CAMERAMOVE_LEFT);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setMinion();
		_object->setObject();
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_DOOR_RIGHT &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, 0, 0, 0)))
	{
		_body.x += 258;
		if (_familiarOn)_familiar->setX(_familiar->getFamiliar().x + 258);
		CAMERAMANAGER->cameraMoveX(CAMERAMOVE_RIGHT);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setMinion();
		_object->setObject();
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_BOSS_DOOR_UP &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, -25, 0, 0)))
	{
		_body.y -= 258;
		if (_familiarOn)_familiar->setY(_familiar->getFamiliar().y - 258);
		CAMERAMANAGER->cameraMoveY(CAMERAMOVE_UP, false);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setBossInit(true);
		_enemy->setMinion();
		_object->setObject();
		_map->getCutScene()->setIsOn(true);
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_BOSS_DOOR_DOWN &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, 0, 0, 25)))
	{
		_body.y += 258;
		if (_familiarOn)_familiar->setY(_familiar->getFamiliar().y + 258);
		CAMERAMANAGER->cameraMoveY(CAMERAMOVE_DOWN, false);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setBossInit(true);
		_enemy->setMinion();
		_object->setObject();
		_map->getCutScene()->setIsOn(true);
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_BOSS_DOOR_LEFT &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, -40, 0, 0, 0)))
	{
		_body.x -= 258;
		if (_familiarOn)_familiar->setX(_familiar->getFamiliar().x - 258);
		CAMERAMANAGER->cameraMoveX(CAMERAMOVE_LEFT);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setBossInit(true);
		_enemy->setMinion();
		_object->setObject();
		_map->getCutScene()->setIsOn(true);
	}
	else if (_map->getAttribute()[tileIndex] == ATTR_BOSS_DOOR_RIGHT &&
		IntersectRect(&rcTemp, &_map->getTiles()[tileIndex].rc, &CollisionAreaResizing(_body.rc, 0, 0, 0, 0)))
	{
		_body.x += 258;
		if (_familiarOn)_familiar->setX(_familiar->getFamiliar().x + 258);
		CAMERAMANAGER->cameraMoveX(CAMERAMOVE_RIGHT);
		_object->refresh();
		_item->setItem();
		this->tileSetUp();
		_enemy->tileSetUp();
		_enemy->setBossInit(true);
		_enemy->setMinion();
		_object->setObject();
		_map->getCutScene()->setIsOn(true);
	}
}