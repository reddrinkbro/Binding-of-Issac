#pragma once
#include "gameNode.h"

struct paper
{
	image* img;
	RECT rc;
	float x;
	float y;
	int currentFrameY;
	int count;
	bool isOn;
	int zOrder;
	int tileIndex;
	int objectIndex;
	int propsIndex;
	int monsterIndex;
	int itemIndex;
};
struct notice
{
	image* img;
	RECT rc;
	float x;
	float y;
	int currentX;
	int zOrder;
};
struct arrow
{
	image* img;
	RECT rc;
};
struct toggle
{
	image* img;
	RECT rc;
	float x;
	float y;
	int currentX;
	bool isOn;
};
struct mapToolOption
{
	image* img;
	RECT rc;
	float x;
	float y;
	bool isOn;
};
enum TILESTYLE
{
	TILESTYLE_TERRAIN,
	TILESTYLE_OBJECT,
	TILESTYLE_PROPS,
	TILESTYLE_MONSTER,
	TILESTYLE_ITEM,
	TILESTYLE_NONE
};

class tilesPaper: public gameNode
{
private:
	paper _paper;
	//1  : 타일  2 : 오브젝트 3 : 프롭스 4 : 아이템 5 : 몬스터 6 : 세이브 로드
	notice _notice[6];
	toggle _dragMode;
	toggle _eraseMode;
	toggle _shopMode;
	arrow _arrow[2];
	TILESTYLE _tileStyle;
	mapToolOption _save;
	mapToolOption _load;
	mapToolOption _back;
	int _tileSize;
	int _objectSize;
	int _propsSize;
public:
	HRESULT init(int tileSize, int objectSize, int propsSize);
	void release(void);
	void update(void);
	void render(void);

	void paperOn(void);
	void arrowClick(void);
	void dragMode(void);
	void usingErase(void);
	void saveLoad(void);
	void shopMode(void);
	void back(void);
	paper getPaper(void) { return _paper; }
	bool isDrawMode(void) { return _dragMode.isOn; }
	bool isEraseMode(void) { return _eraseMode.isOn; }
	bool isShopMode(void) { return _shopMode.isOn; }
	bool isSaveOn(void) { return _save.isOn; }
	bool isLoadOn(void) { return _load.isOn; }
	void paperUp(void);
	TILESTYLE getStyle(void) { return _tileStyle; }
	int objectIndex(void) { return _paper.objectIndex; }
	void selectStyle(void);
	tilesPaper(){}
	~tilesPaper(){}
};

