#include "stdafx.h"
#include "mapTool.h"

void mapTool::shopMap(void)
{
	if (_mouseInpaper) return;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == 0 && j == 0)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 0;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 0;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(0, 0);
			}
			else if (i == 0 && j == 14)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 8;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 0;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(8, 0);
			}
			else if (i == 9 && j == 0)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 0;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 6;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(0, 6);
			}
			else if (i == 9 && j == 14)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 8;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 6;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(8, 6); 
			}
			else if (i == 0 && j < 14)
			{

				if (j == 1)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 8;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 5;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(8, 5);
				}
				else if (j == 13)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 8;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 1;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(8, 1);
				}
				else
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 8;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 2;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(8, 2);
				}
			}
			else if (i < 9 && j == 0)
			{
				if (i == 1)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 7;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 6;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(7, 6);
				}
				else if (i == 8)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 6;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 6);
				}
				else
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 6;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 6;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(6, 6);
				}
			}
			else if (i < 9 && j == 14)
			{
				if (i == 1)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 7;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 0;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(7, 6);
				}
				else if (i == 8)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 0;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 0);
				}
				else
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 0;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 0);
				}
			}
			else if (i == 9 && j < 14)
			{
				if (j == 1)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 0;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 5;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(0, 5);
				}
				else if (j == 13)
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 0;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 1;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(0, 1);
				}
				else
				{
					_tiles[i * TILEX + j + _sIndex].terrainFrameX = 0;
					_tiles[i * TILEX + j + _sIndex].terrainFrameY = 4;
					_tiles[i * TILEX + j + _sIndex].tile = tileSelect(0, 4);
				}
			}
			else if (i == 1 && j == 1)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 1;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 1);
			}
			else if (i == 1 && j == 13)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 7;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 1;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(7, 1);
			}
			else if (i == 8 && j == 1)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 5;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 5);
			}
			else if (i == 8 && j == 13)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 7;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 5;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(7, 5);
			}
			else if (i == 1 && j < 13)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 7;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 2;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(7, 2);
			}
			else if (i < 8 && j == 1)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 3;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 5;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(3, 5);
			}
			else if (i < 8 && j == 13)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 3;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 1;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(3, 1);
			}
			else if (i == 8 && j < 13)
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 1;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 4;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(1, 4);
			}
			else
			{
				_tiles[i * TILEX + j + _sIndex].terrainFrameX = 2;
				_tiles[i * TILEX + j + _sIndex].terrainFrameY = 4;
				_tiles[i * TILEX + j + _sIndex].tile = tileSelect(2, 4);
				if (i == 5 && (j == 4 || j == 7 || j == 10))
				{
					_tiles[i * TILEX + j + _sIndex].objFrameX = 7;
					_tiles[i * TILEX + j + _sIndex].objFrameY = 4;
					_tiles[i * TILEX + j + _sIndex].obj = objSelect(7, 4);
					_tiles[i * TILEX + j + _sIndex].framestate = FRAMESTATE_OFF;
				}
			}
			_tiles[i * TILEX + j + _sIndex].terrain = terrainSelect(_paper->getPaper().tileIndex);
		}
	}
	_miniMap->addMap(_sIndex);
}