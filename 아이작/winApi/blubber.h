#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"
enum BLUBBERSTATE
{
	BLUBBERSTATE_UP,
	BLUBBERSTATE_DOWN,
	BLUBBERSTATE_LEFT,
	BLUBBERSTATE_RIGHT
};

struct blubberStrct
{
	image* img;
	RECT rc;
	BLUBBERSTATE state;
	float x;
	float y;
	float speed;
	float hp;
	float count;
	float distance;
	int randDirection;
	int currentX;
	int currentY;
};
class blubber : public gameNode
{
private:
	blubberStrct _blubber;
	blubberBullet* _bullet;
	shadow* _shadow;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void randomDirection(void);
	void bulletHit(float angle, float damage);
	blubberStrct getStruct(void) { return _blubber; }
	blubberBullet* getEnemyBullet(void) { return _bullet; }
	void setState(BLUBBERSTATE state) { _blubber.state = state; }
	void setRECT(RECT rc) { _blubber.rc = rc; }
	blubber(){}
	~blubber(){}
};

