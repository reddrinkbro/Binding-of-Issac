#include "stdafx.h"
#include "effect.h"
#include "image.h"
#include "animation.h"

effect::effect() : _image(NULL),
				   _animation(NULL),
				   _isRunning(false),
				   _x(0), _y(0)
{
}

HRESULT effect::init(image * img, int frameW, int frameH, int fps)
{
	if (!img) return E_FAIL;

	//Ȱ��ȭ ����
	_isRunning = false;

	_image = img;

	//�ִϸ��̼� ��ü�� ������ ����
	if (!_animation) _animation = new animation;

	_animation->init(_image->getWidth(), _image->getHeight(), frameW, frameH);
	_animation->setDefPlayFrame(false, false);
	_animation->setFPS(fps);
	_animation->stop();

	return S_OK;
}

void effect::release(void)
{
	_image = NULL;
	SAFE_DELETE(_animation);
}

void effect::update(float elapsedTime)
{
	//Ȱ��ȭ �Ǿ� ���� ������ ����Ұ�
	if (!_isRunning) return;
	_animation->frameUpdate(elapsedTime);

	//����Ʈ �ִϸ��̼��� ���� �Ǿ����� ����
	if (!_animation->isPlay()) stop();
}

void effect::render(void)
{
	if (!_isRunning) return;

	_image->aniRender(getMemDC(), _x, _y, _animation);
}

void effect::start(int x, int y)
{
	//�ʱ�ȭ�� �Ǿ� ���� ������ ����Ұ�
	if (!_image || !_animation) return;

	_x = x - (_animation->getFrameWidth() / 2);
	_y = y - (_animation->getFrameHeight() / 2);

	_isRunning = true;
	_animation->start();
}

void effect::stop(void)
{
	_isRunning = false;
}
