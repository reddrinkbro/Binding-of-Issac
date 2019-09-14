#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _tank;

	RECT _rc;
	//픽셀 충돌 탐지할 y값 센서
	int _probeY;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollision() {}
	~pixelCollision() {}
};

