#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rc;
	int _x;
	int _y;
	float _width;

	char* _keyBarBottom;
	char* _keyBarTop;

	image* _progressBarDown;
	image* _progressBarUp;

public:
	HRESULT init(int x, int y, int width, int height);
	HRESULT init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect(void) { return _rc; }

	progressBar() {}
	virtual  ~progressBar() {}
};

