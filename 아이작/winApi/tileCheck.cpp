#include "stdafx.h"
#include "mapTool.h"

void mapTool::tileCheck(int index)
{
	if (PtInRect(&_tiles[index].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
	{
		_tileBrush = CreateSolidBrush(RGB(0, 122, 0));
		_tileOldBrush = (HBRUSH)SelectObject(getMemDC(), _tileBrush);
		Rectangle(getMemDC(),
			_tiles[index].rc.left - CAMERAMANAGER->getX(), _tiles[index].rc.top - CAMERAMANAGER->getY(),
			_tiles[index].rc.right - CAMERAMANAGER->getX(), _tiles[index].rc.bottom - CAMERAMANAGER->getY());
		SelectObject(getMemDC(), _tileOldBrush);
		DeleteObject(_tileBrush);
	}

	else if (_isTileBrushOn)
	{
		if (_paper->getStyle() == TILESTYLE_OBJECT && _paper->objectIndex() == 1) return;
		if (_paper->isDrawMode())
		{
			for (int i = 0; i < _dIndex1 + 1; i++)
			{
				if (_xIndex1 % TILEX < _xIndex2 % TILEX)
				{
					if (index >= i * TILEX + _xIndex1 && index <= i * TILEX + _dIndex2 + _xIndex1)
					{
						if (_dIndex1 >= 4 && _dIndex2 >= 4)
						{
							_tileBrush = CreateSolidBrush(RGB(0, 122, 0));
							_tileOldBrush = (HBRUSH)SelectObject(getMemDC(), _tileBrush);
							Rectangle(getMemDC(), _tiles[index].rc.left - CAMERAMANAGER->getX(), _tiles[index].rc.top - CAMERAMANAGER->getY(),
								_tiles[index].rc.right - CAMERAMANAGER->getX(), _tiles[index].rc.bottom - CAMERAMANAGER->getY());
							SelectObject(getMemDC(), _tileOldBrush);
							DeleteObject(_tileBrush);
						}
						else if (_dIndex1 < 4 || _dIndex2 < 4)
						{
							_tileBrush = CreateSolidBrush(RGB(255, 0, 0));
							_tileOldBrush = (HBRUSH)SelectObject(getMemDC(), _tileBrush);
							Rectangle(getMemDC(), _tiles[index].rc.left - CAMERAMANAGER->getX(), _tiles[index].rc.top - CAMERAMANAGER->getY(),
								_tiles[index].rc.right - CAMERAMANAGER->getX(), _tiles[index].rc.bottom - CAMERAMANAGER->getY());
							SelectObject(getMemDC(), _tileOldBrush);
							DeleteObject(_tileBrush);
						}
					}
				}
			}
		}
		else if (_paper->isEraseMode())
		{
			if (_xIndex3 % TILEX < _xIndex4 % TILEX)
			{
				for (int i = 0; i < _eIndex1 + 1; i++)
				{
					if (index >= i * TILEX + _xIndex3 && index <= i * TILEX + _eIndex2 + _xIndex3)
					{
						_tileBrush = CreateSolidBrush(RGB(0, 122, 0));
						_tileOldBrush = (HBRUSH)SelectObject(getMemDC(), _tileBrush);
						Rectangle(getMemDC(), _tiles[index].rc.left - CAMERAMANAGER->getX(), _tiles[index].rc.top - CAMERAMANAGER->getY(),
							_tiles[index].rc.right - CAMERAMANAGER->getX(), _tiles[index].rc.bottom - CAMERAMANAGER->getY());
						SelectObject(getMemDC(), _tileOldBrush);
						DeleteObject(_tileBrush);
					}
				}
			}
		}
	}
}
