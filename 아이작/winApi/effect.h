#pragma once
#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int _x;							//����Ʈ�� ��ġ x
	int _y;							//����Ʈ�� ��ġ y

	image*		_image;				//����Ʈ �̹���
	animation*	_animation;			//����Ʈ �ִϸ��̼�
	bool		_isRunning;			//����Ʈ ����ǰ� �ִ���

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

