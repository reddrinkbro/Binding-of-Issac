#pragma once
#include "gameNode.h"

struct exitStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float count;
	int currentX;
	bool isOn;
};

class exitObject : public gameNode
{
private:
	exitStruct _exit;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void frame(void);
	exitStruct getStruct(void) { return _exit; }
	exitObject(){}
	~exitObject(){}
};

