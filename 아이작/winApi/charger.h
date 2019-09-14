#pragma once
#include "gameNode.h"
#include "shadow.h"
enum CHARGERSTATE
{
	CHARGERSTATE_UP,
	CHARGERSTATE_DOWN,
	CHARGERSTATE_LEFT,
	CHARGERSTATE_RIGHT
};

struct chargerStruct
{
	image * img;
	RECT rc;
	CHARGERSTATE state;
	float x;
	float y;
	float speed;
	float count;
	float hp;
	int currentX;
	int currentY;
	bool isCharge;
};
class charger : public gameNode
{
private:
	chargerStruct _charger;
	shadow* _shadow;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void charge(float x, float y);
	void bulletHit(float damage);
	chargerStruct getStruct(void) { return _charger; }
	void setChargerToFalse(void) { _charger.isCharge = false; }
	void setState(CHARGERSTATE state) { _charger.state = state; }
	void setRECT(RECT rc) { _charger.rc = rc; }
	charger(){}
	~charger(){}
};

