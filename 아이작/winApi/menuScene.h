#pragma once
#include "gameNode.h"

struct menuArrow
{
	image* img;
	RECT rc;
	float x;
	float y;
	int modeSelect;
};
struct menu
{
	image* img;
	RECT rc;
	float x;
	float y;
};
class menuScene : public gameNode
{
private:
	image * _image;
	image* _title;
	menuArrow _arrow;
	menu _menu[4];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void modeSelect(void);
	menuScene(){}
	~menuScene(){}
};

