#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"
enum HORFSTATE
{
	HORFSTATE_NONE,
	HORFSTATE_LEFT,
	HORFSTATE_RIGHT
};
struct horfStruct
{
	image* img;
	RECT rc;
	HORFSTATE state;
	float x;
	float y;
	float speed;
	float hp;
	float distance;
	float count;
	float targetX;
	float targetY;
	int currentX;
	bool isFire;
};
class horf : public gameNode
{
private:
	horfStruct _horf;
	horfBullet* _bullet;
	shadow* _shadow;
	int _coolDownTime;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(float x, float y);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void bulletHit(float angle, float damage);
	horfStruct getStruct(void) { return _horf; }
	horfBullet* getEnemyBullet(void) { return _bullet; }
	horf(){}
	~horf(){}
};

