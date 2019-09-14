#pragma once
#include "gameNode.h"

struct ghostBabyStrct
{
	image * img;
	float x;
	float y;
	float distance;
	bool isUp;
	bool isMove;
};


class ghostBaby : public gameNode
{
private:
	ghostBabyStrct _ghost;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(void);
	void gainGhostBaby(float x, float y);
	ghostBabyStrct getGhostBaby(void) { return _ghost; }
	void stop(void) { _ghost.isMove = false; }
	ghostBaby(){}
	~ghostBaby(){}
};

