#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"

enum FAMILIARSTATE
{
	FAMILIARSTATE_UP,
	FAMILIARSTATE_DOWN,
	FAMILIARSTATE_LEFT,
	FAMILIARSTATE_RIGHT
};

struct familiarStruct
{
	image* img;
	FAMILIARSTATE state;
	float x;
	float y;
	float centerX;
	float centerY;
	float count;
	float speed;
	int currentX;
	int currentY;
	bool isFire;
};

class familiar : public gameNode
{
private:
	familiarStruct _familiar;
	familiarBullet* _bullet;
	shadow* _shadow;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(float x , float y, float speed);
	void fire(void);
	void frame(void);
	familiarStruct getFamiliar(void) { return _familiar; }
	familiarBullet* getFamiliarBullet(void) { return _bullet; }
	void setX(float x) { _familiar.x = x; }
	void setY(float y) { _familiar.y = y; }
	void setFamilarState(FAMILIARSTATE state) { _familiar.state = state; }
	familiar(){}
	~familiar(){}
};

