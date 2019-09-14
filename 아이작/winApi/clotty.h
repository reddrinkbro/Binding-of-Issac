#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"
enum CLOTTYSTATE
{
	CLOTTYSTATE_LEFT,
	CLOTTYSTATE_RIGHT
};

struct clottyStrct
{
	image* img;
	RECT rc;
	CLOTTYSTATE state;
	float x;
	float y;
	float speed;
	float hp;
	float count;
	float distance;
	int currentX;
	int currentY;
};
class clotty : public gameNode
{
private:
	clottyStrct _clotty;
	clottyBullet* _bullet;
	shadow* _shadow;
	int _randomDirection;
	int _randomBreakTime;
	int _shottingTime;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void fire(void);
	void restTime(void);
	void bulletHit(float angle, float damage);
	clottyStrct getStruct(void) { return _clotty; }
	clottyBullet* getEnemyBullet(void) { return _bullet; }
	void setState(CLOTTYSTATE state) { _clotty.state = state; }
	void setRECT(RECT rc) { _clotty.rc = rc; }
	clotty(){}
	~clotty(){}
};

