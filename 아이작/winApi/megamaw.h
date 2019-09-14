#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "shadow.h"
#include "progressBar.h"
enum MEGAMAWSTATE
{
	MEGAMAWSTATE_NONE,
	MEGAMAWSTATE_START,
	MEGAMAWSTATE_PATTERN1,
	MEGAMAWSTATE_PATTERN2,
	MEGAMAWSTATE_DIE
};

struct megamawStruct
{
	image* img;
	RECT rc;
	MEGAMAWSTATE state;
	float x;
	float y;
	float targetX;
	float targetY;
	float speed;
	float hp;
	float maxHp;
	float count;
	float angle;
	float moveDistance;
	float targetDistance;
	int currentX;
	int currentY;
	int randomPattern;
	int restTime;
	int shakeTime;
	bool isLeft;
};

class megamaw : public gameNode
{
private:
	megamawStruct _megamaw;
	megamawBullet* _bullet;
	shadow* _shadow;
	progressBar* _hpBar;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(float x, float y);
	void render(void);
	void draw(void);
	void frame(void);
	void shake(void);
	void selectPattern(void);
	void bulletHit(float damage);
	megamawStruct getStruct(void) { return _megamaw; }
	megamawBullet* getEnemyBullet(void) { return _bullet; }
	megamaw(){}
	~megamaw(){}
};

