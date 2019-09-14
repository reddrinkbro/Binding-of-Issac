#pragma once
#include "gameNode.h"
#include "monsterData.h"
#include "tileNode.h"

class player;
class dungeonMap;

class enemyManager : public gameNode
{
private:
	typedef vector<frowningGaperData> vEnemyGaper;
	typedef vector<frowningGaperData>::iterator viEnemyGaper;
	typedef vector<clottyData> vEnemyClotty;
	typedef vector<clottyData>::iterator viEnemyClotty;
	typedef vector<horfData> vEnemyHorf;
	typedef vector<horfData>::iterator viEnemyHorf;
	typedef vector<attackFlyData> vEnemyAttackFly;
	typedef vector<attackFlyData>::iterator viEnemyAttackFly;
	typedef vector<level2FlyData> vEnemyLevel2Fly;
	typedef vector<level2FlyData>::iterator viEnemyLevel2Fly;
	typedef vector<blubberData> vEnemyBlubber;
	typedef vector<blubberData>::iterator viEnemyBlubber;
	typedef vector<chargerData> vEnemyCharger;
	typedef vector<chargerData>::iterator viEnemyCharger;
	typedef vector<tumorData> vEnemyTumor;
	typedef vector<tumorData>::iterator viEnemyTumor;
	typedef vector<blood> bloodVec;
	typedef vector<blood>::iterator bloodVecIter;
private:
	vEnemyGaper _vGaper;
	viEnemyGaper _viGaper;
	vEnemyClotty _vClotty;
	viEnemyClotty _viClotty;
	vEnemyHorf _vHorf;
	viEnemyHorf _viHorf;
	vEnemyAttackFly _vAttackFly;
	viEnemyAttackFly _viAttackFly;
	vEnemyLevel2Fly _vLevel2Fly;
	viEnemyLevel2Fly _viLevel2Fly;
	vEnemyBlubber _vBlubber;
	viEnemyBlubber _viBlubber;
	vEnemyCharger _vCharger;
	viEnemyCharger _viCharger;
	vEnemyTumor _vTumor;
	viEnemyTumor _viTumor;
	bloodVec _vBlood;
	bloodVecIter _viBlood;
private:
	sixWayBullet* _sixWayBullet;
	player* _player;
	dungeonMap* _map;
	COLLISIONMONSTER _collisionMonster;
	BOSSSELECT _bossSelect;
	dukeoffliesData _dukeoffliesData;
	monstroData _monstroData;
	megamawData _megamawData;
	vector<tagTile> tileVec;
	vector<DWORD> attributeVec;
	int _fieldMonsterNum;
	bool _bossInit;
public:
	HRESULT init(BOSSSELECT bossSelect);
	void release(void);
	void update(void);
	void render(void);
	void setMinion(void);
	void spawnAttackFly(int num);
public:
	void removeGaper(int arrNum);
	void removeClotty(int arrNum);
	void removeHorf(int arrNum);
	void removeAttackFly(int arrNum);
	void removeLevel2Fly(int arrNum);
	void removeBlubber(int arrNum);
	void removeCharger(int arrNum);
	void removeTumor(int arrNum);
	void removeDukeOfflies(void);
	void removeMonstro(void);
	void removeMegamaw(void);
public:
	void collision(void);
	void bulletEnemyCollision(void);
	void objectEnemyCollision(COLLISIONMONSTER collisionMonster, int arrNum);
	void tileEnemyCollision(COLLISIONMONSTER collisionMonster, int arrNum);
	void addBlood(float x, float y);
public:
	vector<frowningGaperData> getFrowningGaper(void) { return _vGaper; }
	vector<clottyData> getClotty(void) { return _vClotty; }
	vector<horfData> getHorf(void) { return _vHorf; }
	vector<attackFlyData> getAttackFly(void) { return _vAttackFly; }
	vector<level2FlyData> getLevel2Fly(void) { return _vLevel2Fly; }
	vector<blubberData> getBlubber(void) { return _vBlubber; }
	vector<chargerData> getCharger(void) { return _vCharger; }
	vector<tumorData> getTumor(void) { return _vTumor; }
	dukeoffliesData getDukeOfflies(void) { return _dukeoffliesData; }
	monstroData getMonstro(void) { return _monstroData; }
	megamawData getMegamaw(void) { return _megamawData; }

	BOSSSELECT getBossSelect(void) { return _bossSelect; }
	void tileSetUp(void);
	int getFieldMonsterNum(void) { return _fieldMonsterNum; }
	bool getBossInit(void) { return _bossInit; }
	void setBossInit(bool bossInit) { _bossInit = bossInit; }
public:
	void setPlayerMemoryLink(player* player) { _player = player; }
	void setDungeonMapMemoryLink(dungeonMap* map) { _map = map; }

	enemyManager() {}
	~enemyManager() {}
};

