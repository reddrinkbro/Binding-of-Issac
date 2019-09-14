#pragma once
#include "gameNode.h"
#include "shadow.h"
struct coinStruct
{
	image* img;
	RECT rc;
	float x;
	float y;
	float count;
	float currnetX;
};
class coin : public gameNode
{
private:
	coinStruct _coin;
	shadow* _shadow;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void frame(void);
	coinStruct getStruct(void) { return _coin; }
	coin(){}
	~coin(){}
};

