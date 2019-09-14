#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#include "player.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "objectManager.h"

class dungeonGameScene : public gameNode
{
private:
	image* _sceneChangScene;
	image* _control;
	player* _player;
	enemyManager* _enemy;
	dungeonMap* _map;
	itemManager* _item;
	objectManager* _object;
	int _randomBossSelect;
	float _controlImageX;
	float _controlImageY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	dungeonGameScene(){}
	~dungeonGameScene(){}
};

