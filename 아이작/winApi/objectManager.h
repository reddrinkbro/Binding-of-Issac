#pragma once
#include "gameNode.h"
#include "objectData.h"

class dungeonMap;
class player;
class itemManager;
class enemyManager;

class objectManager : public gameNode
{
private:
	typedef vector<treasureChestData> treasureChestVec;
	typedef vector<treasureChestData>::iterator treasureChestVecIter;
	typedef vector<spikeSmallData> spikeSmallVec;
	typedef vector<spikeSmallData>::iterator spikeSmallVecIter;
	typedef vector<spikeLargeData> spikeLargeVec;
	typedef vector<spikeLargeData>::iterator spikeLargeVecIter;
	typedef vector<doorData> doorVec;
	typedef vector<doorData>::iterator doorVecIter;
	typedef vector<exitObject*> exitVec;
	typedef vector<exitObject*>::iterator exitVecIter;
	typedef vector<basicPoopData> basicPoopVec;
	typedef vector<basicPoopData>::iterator basicPoopVecIter;
	typedef vector<redPoopData> redPoopVec;
	typedef vector<redPoopData>::iterator redPoopVecIter;
private:
	treasureChestVec _vChest;
	treasureChestVecIter _viChest;
	spikeSmallVec _vSpikeSmall;
	spikeSmallVecIter _viSpikeSmall;
	spikeLargeVec _vSpikeLarge;
	spikeLargeVecIter _viSpikeLarge;
	doorVec _vDoor;
	doorVecIter _viDoor;
	exitVec _vExit;
	exitVecIter _viExit;
	basicPoopVec _vBPoop;
	basicPoopVecIter _viBPoop;
	redPoopVec _vRPoop;
	redPoopVecIter _viRPoop;
private:
	dungeonMap* _map;
	player* _player;
	itemManager* _item;
	enemyManager* _enemy;
	bool _isDoorOpen;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setObject(void);
	void refresh(void);
	void removeChest(int arrNum);
	void removeBasicPoop(int arrNum);
	void removeRedPoop(int arrNum);
public:
	vector<treasureChestData> getChest(void) { return _vChest; }
	vector<spikeSmallData> getSpikeSmall(void) { return _vSpikeSmall; }
	vector<spikeLargeData> getSpikeLarge(void) { return _vSpikeLarge; }
	vector<doorData> getDoor(void) { return _vDoor; }
	vector<exitObject*> getExit(void) { return _vExit; }
	vector<basicPoopData> getBasicPoop(void) { return _vBPoop; }
	vector<redPoopData> getRedPoop(void) { return _vRPoop; }
public:
	void setDungeonMapMemoryLink(dungeonMap* map) { _map = map; }
	void setPlayerMemoryLink(player* player) { _player = player; }
	void setItemMemoryLink(itemManager* item) { _item = item; }
	void setEnemyMemoryLink(enemyManager* enemy) { _enemy = enemy; }
	void setDoor(bool isDoorOpen) { _isDoorOpen = isDoorOpen; }
	objectManager(){}
	~objectManager(){}
};

