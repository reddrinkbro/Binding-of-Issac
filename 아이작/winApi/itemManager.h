#pragma once
#include "gameNode.h"
#include "itemData.h"

class dungeonMap;
class player;
class enemyManager;
class objectManager;

class itemManager : public gameNode
{
private:
	typedef vector<coinData> coinVector;
	typedef vector<coinData>::iterator coinVectoriter;
	typedef vector<bombData> bombVector;
	typedef vector<bombData>::iterator bombVectoriter;
	typedef vector<healthPointData> healthPointVector;
	typedef vector<healthPointData>::iterator healthPointVectoriter;
	typedef vector<pentagramData> pentagramVector;
	typedef vector<pentagramData>::iterator pentagramVectoriter;
	typedef vector<ouijaboardData> ouijaboardVector;
	typedef vector<ouijaboardData>::iterator ouijaboardVectoriter;
	typedef vector<ghostBabyData> harleQuinVector;
	typedef vector<ghostBabyData>::iterator harleQuinVectoriter;
	typedef vector<pillATKUPData> pillATKUPVector;
	typedef vector<pillATKUPData>::iterator pillATKUPVectoriter;
	typedef vector<pillSPEEDUPData> pillSPEEDUPVector;
	typedef vector<pillSPEEDUPData>::iterator pillSPEEDUPVectoriter;
	typedef vector<pillATKDOWNData> pillATKDOWNVector;
	typedef vector<pillATKDOWNData>::iterator pillATKDOWNVectoriter;
	typedef vector<pillSPEEDDOWNData> pillSPEEDDOWNVector;
	typedef vector<pillSPEEDDOWNData>::iterator pillSPEEDDOWNVectoriter;
	typedef vector<keyData> keyVector;
	typedef vector<keyData>::iterator keyVectoriter;
private:
	coinVector _vCoin;
	coinVectoriter _viCoin;
	bombVector _vBomb;
	bombVectoriter _viBomb;
	healthPointVector _vHealthPoint;
	healthPointVectoriter _viHealthPoint;
	pentagramVector _vPenta;
	pentagramVectoriter _viPenta;
	ouijaboardVector _vOuijaboard;
	ouijaboardVectoriter _viOuijaboard;
	harleQuinVector _vGhost;
	harleQuinVectoriter _viGhost;
	pillATKUPVector _vPillATKUP;
	pillATKUPVectoriter _viPillATKUP;
	pillSPEEDUPVector _vPillSPEEDUP;
	pillSPEEDUPVectoriter _viPillSPEEDUP;
	pillATKDOWNVector _vPillATKDOWN;
	pillATKDOWNVectoriter _viPillATKDOWN;
	pillSPEEDDOWNVector _vPillSPEEDDOWN;
	pillSPEEDDOWNVectoriter _viPillSPEEDDOWN;
	keyVector _vKey;
	keyVectoriter _viKey;
private:
	dungeonMap* _map;
	player* _player;
	enemyManager* _enemy;
	objectManager* _object;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setItem(void);
	void bombSet(float x,float y);
	void coinSet(float x, float y);
	void hpSet(float x, float y);
	void pillSet(float x, float y, int num);
public:
	void removeCoin(int arrNum);
	void removeBomb(int arrNum);
	void removeHealthPoint(int arrNum);
	void removePentagram(void);
	void removeOuijaboard(void);
	void removeHarleQuinBaby(void);
	void removePillAtkUp(int arrNum);
	void removepillSpeedUp(int arrNum);
	void removePillAtkDown(int arrNum);
	void removePillSpeedDown(int arrNum);
	void removeKey(int arrNum);
public:
	void playerItemCollision(void);
	void playerExplosionCollision(int arrNum);
	void objectExplosionCollision(int arrNum);
	void enemyExplosionCollision(int arrNum);
public:
	vector<coinData> getCoin(void) { return _vCoin; }
	vector<bombData> getBomb(void) { return _vBomb; }
	vector<healthPointData> getHealthPoint(void) { return _vHealthPoint; }
	vector<pentagramData> getPentagram(void) { return _vPenta; }
	vector<ouijaboardData> getOuijaboard(void) { return _vOuijaboard; }
	vector<ghostBabyData> getGhostBaby(void) { return _vGhost; }
	vector<pillATKUPData> getPillAtkUp(void) { return _vPillATKUP; }
	vector<pillSPEEDUPData> getpillSpeedUp(void) { return _vPillSPEEDUP; }
	vector<pillATKDOWNData> getpillAtkDown(void) { return _vPillATKDOWN; }
	vector<pillSPEEDDOWNData> getpillSpeedDOWN(void) { return _vPillSPEEDDOWN; }
	vector<keyData> getKey(void) { return _vKey; }
public:
	void setDungeonMapMemoryLink(dungeonMap* map) { _map = map; }
	void setPlayerMemoryLink(player* player) { _player = player; }
	void setEnemyMemoryLink(enemyManager* enemy) { _enemy = enemy; }
	void setObjectMemoryLink(objectManager* object) { _object = object; }
	itemManager(){}
	~itemManager(){}
};

