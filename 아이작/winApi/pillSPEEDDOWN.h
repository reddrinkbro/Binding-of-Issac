#pragma once
#include "gameNode.h"
#include "shadow.h"
struct pillspeedDown
{
	image* img;
	RECT rc;
	float x;
	float y;
	float speed;
	float distance;
	bool isMove;
};
class pillSPEEDDOWN : public gameNode
{
private:
	pillspeedDown _pill;
	shadow* _shadow;
	float _gravity;
	float _currnetAnlgeValue;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void move(void);
	pillspeedDown getStruct(void) { return _pill; }
	pillSPEEDDOWN(){}
	~pillSPEEDDOWN(){}
};

