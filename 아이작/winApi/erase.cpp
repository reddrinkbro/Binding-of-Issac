#include "stdafx.h"
#include "mapTool.h"

void mapTool::erase()
{
	for (int i = 0; i < _eIndex1 + 1; i++)
	{
		for (int j = 0; j < _eIndex2 + 1; j++)
		{
			if (_paper->getStyle() == TILESTYLE_TERRAIN)
			{
				_tiles[i * TILEX + j + _xIndex3].terrainFrameX = 0;
				_tiles[i * TILEX + j + _xIndex3].terrainFrameY = 0;

				_tiles[i * TILEX + j + _xIndex3].terrain = TR_NONE_BASE;
				_tiles[i * TILEX + j + _xIndex3].tile = T_NONE;
			}
		}
	}
	_miniMap->deleteMap(_xIndex3);
	_xIndex3 = -1;
	_xIndex4 = -1;
}