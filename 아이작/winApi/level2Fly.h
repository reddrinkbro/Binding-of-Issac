#pragma once
#include "gameNode.h"
#include "shadow.h"
struct level2FlyStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float speed;
	float angle;
	float hp;
	float randCount;
	float wolrdCount;
	int currentX;
	
};
class level2Fly :public gameNode
{
private:
	level2FlyStruct _level2Fly;
	shadow* _shadow;
	float _playerX, _playerY;
	bool _isfireEnd;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(float x, float y);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void bulletHit(float angle, float damage);
	level2FlyStruct getStruct(void) { return _level2Fly; }
	level2Fly(){}
	~level2Fly(){}
};

