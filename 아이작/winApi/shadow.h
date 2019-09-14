#pragma once
#include "gameNode.h"

enum SHADOWSIZE
{
	SHADOWSIZE_SMALL,
	SHADOWSIZE_MEDIUM,
	SHADOWSIZE_LARGE
};

class shadow : public gameNode
{
private:
	image * _img;
	float _x;
	float _y;
	int _alpha;
public:
	HRESULT init(SHADOWSIZE size);
	void release(void);
	void update(float x, float y);
	void render(void);
	shadow(){}
	~shadow(){}
};

