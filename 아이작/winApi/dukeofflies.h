#pragma once
#include "gameNode.h"
#include "attackFly.h"
#include "shadow.h"
#include "progressBar.h"
enum DUKEOFFLIESSTATE
{
	DUKEOFFLIESSTATE_NONE,
	DUKEOFFLIESSTATE_SPAWNONE,
	DUKEOFFLIESSTATE_SPAWNTWO,
};
struct dukeoffliesStruct
{
	image* img;
	RECT rc;
	DUKEOFFLIESSTATE state;
	float x;
	float y;
	float speed;
	float hp;
	float maxHp;
	float angle;
	float count;
	int currentX;
	int currentY;
	int randomPattern;
	int restTime;
	bool isSpawn;
};

class dukeofflies: public gameNode
{
private:
	dukeoffliesStruct _dukeofflies;
	shadow* _shadow;
	progressBar* _hpBar;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void angleChange(void);
	dukeoffliesStruct getStruct(void) { return _dukeofflies; }
	void setState(DUKEOFFLIESSTATE state) { _dukeofflies.state = state; }
	void setRECT(RECT rc) { _dukeofflies.rc = rc; }
	void spawnPause(void) { _dukeofflies.isSpawn = false; }
	void bulletHit(float angle, float damage);
	dukeofflies(){}
	~dukeofflies(){}
};

