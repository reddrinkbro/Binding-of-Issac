#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _tank;

	RECT _rc;
	//�ȼ� �浹 Ž���� y�� ����
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

