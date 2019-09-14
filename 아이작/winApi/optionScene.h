#pragma once
#include "gameNode.h"

struct optionArrow
{
	image* img;
	RECT rc;
	float x;
	float y;
	int volumeSelect;
};
struct option
{
	image* img;
	RECT rc;
	float x;
	float y;
};
struct volume
{
	image* img;
	RECT rc;
	float x;
	float y;
};
class optionScene : public gameNode
{
private:
	image * _image;
	optionArrow _arrow;
	option _option[3];
	volume _volume[2];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void volumeSelect(void);
	void save(void);
	optionScene(){}
	~optionScene(){}
};

