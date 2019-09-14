#pragma once
#include "gameNode.h"
#include "shadow.h"
struct attackFlyStruct
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
class attackFly : public gameNode
{
private:
	attackFlyStruct _attackFly;
	shadow* _shadow;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(float x, float y);
	void draw(void);
	void frame(void);
	void bulletHit(float angle , float damage);
	attackFlyStruct getStruct(void) { return _attackFly; }
	attackFly(){}
	~attackFly(){}
};

