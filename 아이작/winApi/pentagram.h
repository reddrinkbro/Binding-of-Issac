#pragma once
#include "gameNode.h"

struct pentagramStrct
{
	image * _image;
	float x;
	float y;
	float distance;
	bool isUp;
	bool isMove;
};

class pentagram : public gameNode
{
private:
	
	pentagramStrct _penta;
	
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(void);
	void gainPentagram(float x , float y);
	pentagramStrct getPentagram(void) { return _penta; }
	void stop(void) { _penta.isMove = false; }
	pentagram(){}
	~pentagram(){}
};

