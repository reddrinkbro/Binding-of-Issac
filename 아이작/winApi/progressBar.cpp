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

	//체력바 위치좌표 초기화
	_x = x;
	_y = y;
	
	//체력바 렉트 위치 및 크기 초기화
	_rc = RectMakeCenter(x, y, width, height);

	//키값으로 이미지이름(~.bmp)을 바로 초기화
	char strUpKey[128];
	char strUpName[128];
	char strDownKey[128];
	char strDownName[128];

	ZeroMemory(strUpKey, sizeof(strUpKey));
	ZeroMemory(strUpName, sizeof(strUpName));
	ZeroMemory(strDownKey, sizeof(strDownKey));
	ZeroMemory(strDownName, sizeof(strDownName));

	//~.bmp로 만들기
	sprintf(strUpKey, frontImageKey);
	sprintf(strUpName, "%s.bmp", frontImageKey);
	sprintf(strDownKey, backImageKey);
	sprintf(strDownName, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
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