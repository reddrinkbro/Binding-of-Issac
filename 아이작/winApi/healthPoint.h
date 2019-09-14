#pragma once
#include "gameNode.h"
#include "shadow.h"
struct healthPointStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float speed;
	float distance;
	float angle;
	bool isInChest;
	bool isMove;
};

class healthPoint : public gameNode
{
private:
	healthPointStruct _healthPoint;
	shadow* _shadow;
	float _gravity;
	float _currnetAnlgeValue;
public:
	HRESULT init(float x, float y, bool isInChest);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(float x,float y, float speed);
	void drop(void);
	healthPointStruct getStruct(void) { return _healthPoint; }
	healthPoint(){}
	~healthPoint(){}
};

