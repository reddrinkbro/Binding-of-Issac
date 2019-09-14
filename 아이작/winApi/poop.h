#pragma once
#include "gameNode.h"

struct tagPoop
{
	image* img;
	float x;
	float y;
	RECT rc;
	int currentX;
};

class basicPoop : public gameNode
{
private:
	tagPoop _poop;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void hit(void);
	tagPoop getStruct(void) { return _poop; }
	basicPoop(){}
	~basicPoop(){}
};

class redPoop : public gameNode
{
private:
	tagPoop _poop;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void hit(void);
	tagPoop getStruct(void) { return _poop; }
	redPoop() {}
	~redPoop() {}
};
