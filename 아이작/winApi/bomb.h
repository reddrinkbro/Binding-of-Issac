#pragma once
#include "gameNode.h"
#include "shadow.h"
struct bombStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float count;
	float time;
	float speed;
	float distance;
	float angle;
	int currnetX;
	bool isInstall;
	bool isInChest;
	bool isMove;
};

class bomb : public gameNode
{
private:
	bombStruct _bomb;
	shadow* _shadow;
	float _gravity;
	float _currnetAnlgeValue;
public:
	HRESULT init(float x, float y, bool isInChest);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void frame(void);
	void drop(void);
	bombStruct getStruct(void) { return _bomb; }
	void isInstall(bool isInstall) { _bomb.isInstall = isInstall; }
	bomb(){}
	~bomb(){}
};

