#pragma once
#include "gameNode.h"
#include "shadow.h"

struct keyStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float speed;
	float distance;
	bool isMove;
};

class key : public gameNode
{
private:
	keyStruct _key;
	shadow* _shadow;
	float _gravity;
	float _currnetAnlgeValue;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	keyStruct getStruct(void) { return _key; }
	key(){}
	~key(){}
};

