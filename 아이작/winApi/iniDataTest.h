#pragma once
#include "gameNode.h"

class iniDataTest : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	iniDataTest() {}
	~iniDataTest() {}
};

