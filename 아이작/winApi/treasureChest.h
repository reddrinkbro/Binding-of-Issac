#pragma once
#include "gameNode.h"

enum CHESTSTATE
{
	CHESTSTATE_CLOSE,
	CHESTSTATE_OPEN
};

struct treasureChestStruct
{
	image* img;
	RECT rc;
	CHESTSTATE state;
	float x;
	float y;
	float count;
	int currentX;
	int currentY;
};

class treasureChest : public gameNode
{
private:
	treasureChestStruct _chest;
	int _time;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void frame(void);
	void setOpen(void) { _chest.state = CHESTSTATE_OPEN; }
	treasureChestStruct getStruct(void) { return _chest; }
	int getTime(void) { return _time; }
	treasureChest(){}
	~treasureChest(){}
};

