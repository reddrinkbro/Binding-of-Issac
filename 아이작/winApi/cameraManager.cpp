#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	_cameraSpeed = 3.5f;
	_minRenderX = -TILESIZE;
	_minRenderY = -TILESIZE;
	_maxRenderX = WINSIZEX+ TILESIZE;
	_maxRenderY = WINSIZEY+ TILESIZE;
	_maxGameRenderX = WINSIZEX - 326;
	_maxGameRenderY = WINSIZEY - 224;
	_cPosX = 0;
	_cPosY = 0;
	_window = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _maxGameRenderX, _maxGameRenderY);
	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
}

void cameraManager::render(void)
{
}

void cameraManager::camerMoveInMapTool()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cPosX -= _cameraSpeed;
		_minRenderX -= _cameraSpeed;
		_maxRenderX -= _cameraSpeed;
			
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cPosX += _cameraSpeed;
		_minRenderX += _cameraSpeed;
		_maxRenderX += _cameraSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cPosY -= _cameraSpeed;
		_minRenderY -= _cameraSpeed;
		_maxRenderY -= _cameraSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cPosY += _cameraSpeed;
		_minRenderY += _cameraSpeed;
		_maxRenderY += _cameraSpeed;
	}
}

void cameraManager::setCameraPos(float x, float y)
{
	_cPosX = x;
	_cPosY = y;
}

void cameraManager::cameraMoveX(CAMERAMOVE _cameraMove)
{
	if (_cameraMove == CAMERAMOVE_RIGHT)
	{
		for (int i = 0; i < 960; i++)
		{
			_cPosX++;
		}
	}
	else if (_cameraMove == CAMERAMOVE_LEFT)
	{
		for (int i = 0; i < 960; i++)
		{
			_cPosX--;
		}
	}
}

void cameraManager::cameraMoveY(CAMERAMOVE _cameraMove, bool isWall)
{
	if (!isWall)
	{
		if (_cameraMove == CAMERAMOVE_UP)
		{
			for (int i = 0; i < 640; i++)
			{
				_cPosY--;
			}
		}
		else if (_cameraMove == CAMERAMOVE_DOWN)
		{
			for (int i = 0; i < 640; i++)
			{
				_cPosY++;
			}
		}
	}
	else
	{
		if (_cameraMove == CAMERAMOVE_UP)
		{
			_cPosY--;
		}
		else if (_cameraMove == CAMERAMOVE_DOWN)
		{
			_cPosY++;
		}
	}
}
