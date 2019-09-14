#include "StdAfx.h"
#include "progressBar.h"

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, width, height);

	_progressBarDown = IMAGEMANAGER->addImage("barDown", "hpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_progressBarUp = IMAGEMANAGER->addImage("barUp", "hpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();

	return S_OK;
}

HRESULT progressBar::init(char * frontImageKey, char * backImageKey, int x, int y, int width, int height)
{
	_keyBarTop = frontImageKey;
	_keyBarBottom = backImageKey;

	//ü�¹� ��ġ��ǥ �ʱ�ȭ
	_x = x;
	_y = y;
	
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rc = RectMakeCenter(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ
	char strUpKey[128];
	char strUpName[128];
	char strDownKey[128];
	char strDownName[128];

	ZeroMemory(strUpKey, sizeof(strUpKey));
	ZeroMemory(strUpName, sizeof(strUpName));
	ZeroMemory(strDownKey, sizeof(strDownKey));
	ZeroMemory(strDownName, sizeof(strDownName));

	//~.bmp�� �����
	sprintf(strUpKey, frontImageKey);
	sprintf(strUpName, "%s.bmp", frontImageKey);
	sprintf(strDownKey, backImageKey);
	sprintf(strDownName, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarDown = IMAGEMANAGER->addImage(strDownKey, strDownName, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarUp = IMAGEMANAGER->addImage(strUpKey, strUpName, x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(),
		_progressBarDown->getHeight());
}

void progressBar::render(void)
{
	_progressBarDown->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2 ,
		_y + _progressBarDown->getHeight() / 2 , 0, 0, _progressBarDown->getWidth(),
		_progressBarDown->getHeight());

	_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2 ,
		_y + _progressBarDown->getHeight() / 2 , 0, 0, _width,
		_progressBarDown->getHeight());
}

void progressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}