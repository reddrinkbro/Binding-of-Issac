#pragma once
#include "gameNode.h"

enum progressState
{
	PROGRESSSTATE_NONE,
	PROGRESSSTATE_IN_PLAYER
};

struct progress
{
	image* img;
	int x;
	int y;
	int index;
	progressState _progressState;
};
class miniMap : public gameNode
{
private:
	image * _bgBlack;
	float _x;
	float _y;
	vector<progress> _vProgress;
	vector<progress>::iterator _viProgress;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void addMap(int index);
	void addMap(int leftTop, int rightTop , int bottom);
	void deleteMap(int index);
	miniMap(){}
	~miniMap(){}
};

