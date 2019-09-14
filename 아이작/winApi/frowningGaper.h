#pragma once
#include "gameNode.h"
#include "shadow.h"
enum GAPERBODYSTATE
{
	GAPERBODYSTATE_CENTER,
	GAPERBODYSTATE_LEFT,
	GAPERBODYSTATE_RIGHT
};

struct frowningGaperHead
{
	image* img;
	RECT rc;
	float x;
	float y;
	float count;
	int currentX;
};

struct frowningGaperBody
{
	GAPERBODYSTATE state;
	image* img;
	RECT rc;
	float x;
	float y;
	float speed;
	float angle;
	float count;
	int currentX;
	int currentY;
	float hp;
};

class frowningGaper : public gameNode
{
private:
	frowningGaperHead _head;
	frowningGaperBody _body;
	shadow* _shadow;
	int _horfRandomSpwanValue;
	bool _playerChase;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(float x, float y);
	void draw(void);
	void frameBody(void);
	void frameHead(void);
	void bulletHit(float angle, float damage);
	int getHorfRandomSpawnValue(void) { return _horfRandomSpwanValue; }
	frowningGaperBody getBody(void) { return _body; }
	frowningGaper(){}
	~frowningGaper(){}
};

