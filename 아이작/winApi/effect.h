#pragma once
#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int _x;							//이펙트의 위치 x
	int _y;							//이펙트의 위치 y

	image*		_image;				//이펙트 이미지
	animation*	_animation;			//이펙트 애니메이션
	bool		_isRunning;			//이펙트 실행되고 있는지

public:
	HRESULT init(image* img, int frameW, int frameH, int fps);
	void update(float elapsedTime);
	void render(void);
	void release(void);

	void start(int x, int y);
	void stop(void);

	bool getIsRunning(void) { return _isRunning; }

	effect();
	~effect() {}
};

