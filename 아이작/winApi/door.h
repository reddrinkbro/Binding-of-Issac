#pragma once
#include "gameNode.h"
#include "tileNode.h"

struct doorStruct
{
	image * img;
	float x;
	float y;
	float count;
	int currentX;
	int currentY;
};
class door : public gameNode
{
private:
	doorStruct _door;
public:
	HRESULT init(float x, float y, int select, DOOROBJECT state, bool isOpen);
	void release(void);
	void update(bool isOpen);
	void render(void);
	doorStruct getStruct(void) { return _door; }
	door(){}
	~door(){}
};

