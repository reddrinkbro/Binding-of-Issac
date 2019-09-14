#include "stdafx.h"
#include "pixelCollision.h"

HRESULT pixelCollision::init(void)
{
	_tank = IMAGEMANAGER->addImage("tank", "tank.bmp", 70, 60, true, RGB(255, 0, 255));
	
	_x = WINSIZEX / 2 + 250;
	_y = WINSIZEY / 2 + 50;

	_rc = RectMakeCenter(_x, _y, _tank->getWidth(), _tank->getHeight());

	//y������ Ž��
	_probeY = _y + _tank->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release(void)
{
	SAFE_DELETE(_tank);
}

void pixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 1.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 1.0f;
	}

	//y������ Ž��
	_probeY = _y + _tank->getHeight() / 2;

	//Ž���� Y���� ������ ���Ʒ��� ���ϴ� ��ŭ �˻�
	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("mountain")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _tank->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _tank->getWidth(), _tank->getHeight());
}

void pixelCollision::render(void)
{
	_tank->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}
}
