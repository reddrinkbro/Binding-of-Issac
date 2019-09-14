#pragma once
#include "gameNode.h"
#include "mapTool.h"

class mapToolScene : public gameNode
{
private:
	mapTool* _mapTool;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	mapToolScene(){}
	~mapToolScene(){}
};

