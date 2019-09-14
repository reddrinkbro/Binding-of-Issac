#include "stdafx.h"
#include "mapTool.h"

void mapTool::tileDraw(void)
{
	if (_dIndex1 < 4 || _dIndex2 < 4)return;
	if(_xIndex1 % TILEX < _xIndex2 % TILEX)
	{ 
		for (int i = 0; i < _dIndex1 + 1; i++)
		{
			for (int j = 0; j < _dIndex2 + 1; j++)
			{
				//1번 구석
				if (i == 0 && j == 0)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 0;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 0;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(0, 0);
				}
				else if (i == 0 && j == _dIndex2)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 8;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 0;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(8, 0);
				}
				else if (i == _dIndex1 && j == 0)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 0;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 6;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(0, 6);
				}
				else if (i == _dIndex1 && j == _dIndex2)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 8;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 6;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(8, 6);
				}
				//위
				else if (i == 0 && j < _dIndex2)
				{
					if (j == 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 8;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 5;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(8, 5);
					}
					else if (j == _dIndex2 - 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 8;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 1;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(8, 1);
					}
					else
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 8;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 2;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(8, 2);
					}
				}
				//왼쪽
				else if (i < _dIndex1 && j == 0)
				{
					if (i == 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 7;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 6;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(7, 6);
					}
					else if (i == _dIndex1 - 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 6;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 6);
					}
					else
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 6;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 6;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(6, 6);
					}
				}
				//오른쪽
				else if (i < _dIndex1 && j == _dIndex2)
				{
					if (i == 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 7;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 0;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(7, 6);
					}
					else if (i == _dIndex1 - 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 0;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 0);
					}
					else
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 0;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 0);
					}
				}
				else if (i == _dIndex1 && j < _dIndex2)
				{
					if (j == 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 0;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 5;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(0, 5);
					}
					else if (j == _dIndex2 - 1)
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 0;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 1;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(0, 1);
					}
					else
					{
						_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 0;
						_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 4;
						_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(0, 4);
					}
				}
				//2번째 구석
				else if (i == 1 && j == 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 1;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 1);
				}
				else if (i == 1 && j == _dIndex2 - 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 7;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 1;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(7, 1);
				}
				else if (i == _dIndex1 - 1 && j == 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 5;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 5);
				}
				else if (i == _dIndex1 - 1 && j == _dIndex2 - 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 7;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 5;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(7, 5);
				}
				//위
				else if (i == 1 && j < _dIndex2 - 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 7;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 2;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(7, 2);
				}
				//왼쪽
				else if (i < _dIndex1 - 1 && j == 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 3;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 5;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(3, 5);
				}
				//오른쪽
				else if (i < _dIndex1 - 1 && j == _dIndex2 - 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 3;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 1;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(3, 1);
				}
				//아래
				else if (i == _dIndex1 - 1 && j < _dIndex2 - 1)
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 1;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 4;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(1, 4);
				}
				else
				{
					_tiles[i * TILEX + j + _xIndex1].terrainFrameX = 2;
					_tiles[i * TILEX + j + _xIndex1].terrainFrameY = 4;
					_tiles[i * TILEX + j + _xIndex1].tile = tileSelect(2, 4);
				}
				_tiles[i * TILEX + j + _xIndex1].terrain = terrainSelect(_paper->getPaper().tileIndex);
			}
		}
	}
	_miniMap->addMap(_xIndex1, _dIndex2, _dIndex1);
	_xIndex1 = -1;
	_xIndex2 = -1;
}