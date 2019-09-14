#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"

enum TUMORSTATE
{
	TUMORSTATE_UP,
	TUMORSTATE_DOWN
};
struct tumorStruct
{
	image* img;
	RECT rc;
	TUMORSTATE state;
	float x;
	float y;
	float speed;
	float hp;
	float count;
	float distance;
	int currentX;
	int currentY;
};
class tumor : gameNode
{
private:
	tumorStruct _tumor;
	sixWayBullet* _bullet;
	shadow* _shadow;
	int _shootingTime;
	float _tumorFrame;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(float x, float y);
	void draw(void);
	void frame(void);
	void fire(void);
	void bulletHit(float angle, float damage);
	tumorStruct getStruct(void) { return _tumor; }
	sixWayBullet* getEnemyBullet(void) { return _bullet; }
	tumor(){}
	~tumor(){}
};

