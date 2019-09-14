#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "cutScene.h"
class dungeonMap : public gameNode
{
private:
	vector<image*>_tileSampleImage;
	//¹® Á¦¿Ü
	vector<image*> _objectImage;
	vector<image*> _propsImage;
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];
	cutScene* _cutScene;
	int _mapSelect;
public:
	HRESULT init(BOSSSELECT bossSelect);
	void release(void);
	void update(void);
	void render(void);
	void load(void);
	void tileRender(void);
	
public:
	tagTile* getTiles() { return _tiles; }
	DWORD* getAttribute() { return _attribute; }
	void monsterDelete(int arrNum) { _attribute[arrNum] = ATTR_NONE; }
	void itemDelete(int arrNum) { _tiles[arrNum].item = ITEM_NONE;	}
	void objectDelete(int arrNum) {
		_attribute[arrNum] = ATTR_NONE;
		_tiles[arrNum].obj = OBJ_NONE;
		_tiles[arrNum].frameObj = FRAMEOBJ_NONE;
	}
	cutScene* getCutScene(void) { return _cutScene; }
	int getMapSelect(void) { return _mapSelect; }
	dungeonMap(){}
	~dungeonMap(){}
};

