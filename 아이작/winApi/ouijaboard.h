#pragma once
#include "gameNode.h"

struct ouijaboardStrct
{
	image* _image;
	float x;
	float y;
	float distance;
	bool isUp;
	bool isMove;
};

class ouijaboard : public gameNode
{
private:
	ouijaboardStrct _ouijaboard;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(void);
	void gainOuijaboard(float x, float y);
	ouijaboardStrct getOuijaboard(void) { return _ouijaboard; }
	void stop(void) { _ouijaboard.isMove = false; }
	ouijaboard(){}
	~ouijaboard(){}
};

