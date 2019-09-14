#include "stdafx.h"
#include "dungeonGameScene.h"

HRESULT dungeonGameScene::init(void)
{
	_randomBossSelect = RND->getInt(3);

	_sceneChangScene = IMAGEMANAGER->addImage("loadimages","image/UI/loadimages.bmp", CAMERAMANAGER->getGameMaxRenderX(), CAMERAMANAGER->getGameMaxRenderY());
	_control = IMAGEMANAGER->addImage("controls", "image/mapObject/controls.bmp", 650, 170,true,RGB(255,0,255));
	_map = new dungeonMap;
	if (_randomBossSelect == 0) _map->init(BOSSSELECT_DUKEOFFLLIES);
	else if (_randomBossSelect == 1) _map->init(BOSSSELECT_MONSTRO);
	else _map->init(BOSSSELECT_MEGAMAW);

	_player = new player;
	_player->setDungeonMapMemoryLink(_map);
	
	_enemy = new enemyManager;
	_enemy->setPlayerMemoryLink(_player);
	_enemy->setDungeonMapMemoryLink(_map);
	_player->setEnemyManagerMemoryLink(_enemy);
	
	_object = new objectManager;
	_object->setDungeonMapMemoryLink(_map);
	_object->setPlayerMemoryLink(_player);
	_object->setEnemyMemoryLink(_enemy);
	_player->setObjectManagerMemoryLink(_object);

	_item = new itemManager;
	_item->setDungeonMapMemoryLink(_map);
	_item->setPlayerMemoryLink(_player);
	_item->setEnemyMemoryLink(_enemy);
	_item->setObjectMemoryLink(_object);
	_player->setItemManagerMemoryLink(_item);
	_object->setItemMemoryLink(_item);

	_player->init((WINSIZEX - 326) / 2, (WINSIZEY - 224) / 2);
	if (_randomBossSelect == 0) _enemy->init(BOSSSELECT_DUKEOFFLLIES);
	else if (_randomBossSelect == 1) _enemy->init(BOSSSELECT_MONSTRO);
	else _enemy->init(BOSSSELECT_MEGAMAW);
	_item->init();
	_object->init();
	_controlImageX = _player->getHead().x - _control->getWidth() / 2;
	_controlImageY = _player->getHead().y - 150;
	return S_OK;
}

void dungeonGameScene::release(void)
{
	SAFE_DELETE(_map);
	SAFE_DELETE(_player);
	SAFE_DELETE(_enemy);
	SAFE_DELETE(_item);
	SAFE_DELETE(_object);
}

void dungeonGameScene::update(void)
{
	_map->update();
	if (!_map->getCutScene()->getIsOn())
	{
		_player->update();
		_enemy->update();
		_item->update();
		_object->update();
	}
	if (!SOUNDMANAGER->isPlaySound("title screen jingle") && !SOUNDMANAGER->isPlaySound("basic boss fight") 
		&& !SOUNDMANAGER->isPlaySound("boss fight intro jingle") && !SOUNDMANAGER->isPlaySound("title screen"))
	{
		if (!SOUNDMANAGER->isPlaySound("basement")) SOUNDMANAGER->play("basement", VOLUME->getMusicVolume() / 10);
	}
}

void dungeonGameScene::render(void)
{
	_map->render();
	_control->render(getMemDC(), _controlImageX - CAMERAMANAGER->getX(), _controlImageY - CAMERAMANAGER->getY());
	if (!_map->getCutScene()->getIsOn())
	{
		_object->render();
		_enemy->render();
		_player->render();
		_item->render();
	}
	if (SOUNDMANAGER->isPlaySound("title screen jingle"))
	{
		_sceneChangScene->render(getMemDC());
	}
}
