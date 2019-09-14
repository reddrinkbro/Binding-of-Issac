#include "stdafx.h"
#include "mapTool.h"

void mapTool::setMap()
{
	//드래그 그리기 모드랑 상점모드에선 타일 선택 불가능
	if (_paper->isDrawMode() || _paper->isShopMode())return;
	if (_paper->getPaper().isOn && !_paper->isDrawMode() && _paper->getStyle() == TILESTYLE_TERRAIN)
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
			{
				_currentTile.x = _sampleTiles[i].terrainFrameX;
				_currentTile.y = _sampleTiles[i].terrainFrameY;
				break;
			}
		}
	}
	else if (_paper->getPaper().isOn && _paper->getStyle() == TILESTYLE_PROPS)
	{
		for (int i = 0; i < PROPSTILEX * PROPSTILEY; i++)
		{
			if (PtInRect(&_sampleProps[i].rcTile, _ptMouse))
			{
				_currentTile.x = _sampleProps[i].terrainFrameX;
				_currentTile.y = _sampleProps[i].terrainFrameY;
				break;
			}
		}
	}
	else if (_paper->getPaper().isOn && _paper->getStyle() == TILESTYLE_OBJECT)
	{
		if (_paper->objectIndex() == 0)
		{
			for (int i = 0; i < OBJECTTILEX * OBJECTTILEY; i++)
			{
				if (PtInRect(&_sampleObject[i].rcTile, _ptMouse))
				{
					_currentTile.x = _sampleObject[i].terrainFrameX;
					_currentTile.y = _sampleObject[i].terrainFrameY;
					break;
				}
			}
		}
		else if (_paper->objectIndex() == 1)
		{
			for (int i = 0; i < FRAMEOBJECTTILEX * FRAMEOBJECTTILEY; i++)
			{
				if (PtInRect(&_sampleFrameObject[i].rcTile, _ptMouse))
				{
					_currentTile.x = _sampleFrameObject[i].terrainFrameX;
					_currentTile.y = _sampleFrameObject[i].terrainFrameY;
					break;
				}
			}
		}
		else if (_paper->objectIndex() == 2)
		{
			for (int i = 0; i < DOORTILEX * DOORTILEY; i++)
			{
				if (PtInRect(&_sampleDoor[i].rcTile, _ptMouse))
				{
					_currentTile.x = _sampleDoor[i].terrainFrameX;
					_currentTile.y = _sampleDoor[i].terrainFrameY;
					break;
				}
			}
		}
	}
	else if (_paper->getPaper().isOn && _paper->getStyle() == TILESTYLE_MONSTER)
	{
		for (int i = 0; i < MONSTEROBJECTTILEX * MONSTEROBJECTTILEY; i++)
		{
			if (PtInRect(&_sampleMonsterObject[i].rcTile, _ptMouse))
			{
				_currentTile.x = _sampleMonsterObject[i].terrainFrameX;
				_currentTile.y = _sampleMonsterObject[i].terrainFrameY;
				break;
			}
		}
	}
	else if (_paper->getPaper().isOn && _paper->getStyle() == TILESTYLE_ITEM)
	{
		for (int i = 0; i < ITEMOBJECTTILEX * ITEMOBJECTTILEY; i++)
		{
			if (PtInRect(&_sampleItemObject[i].rcTile, _ptMouse))
			{
				_currentTile.x = _sampleItemObject[i].terrainFrameX;
				_currentTile.y = _sampleItemObject[i].terrainFrameY;
				break;
			}
		}
	}
	//왼쪽 맵
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())) && !_mouseInpaper)
		{
			//현재 버튼이 지형에 체크되어 있으면
			if (_paper->getStyle() == TILESTYLE_TERRAIN)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;
				_tiles[i].terrain = terrainSelect(_paper->getPaper().tileIndex);
				_tiles[i].tile = tileSelect(_currentTile.x, _currentTile.y);
			}
			//현재 버튼이 오브젝트에 체크되어 있으면
			else if (_paper->getStyle() == TILESTYLE_OBJECT)
			{
				if (_paper->objectIndex() == 0)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;
					_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
					_tiles[i].framestate = FRAMESTATE_OFF;
						
				}
				else if(_paper->objectIndex() == 1)
				{
					_tiles[i].frameObjFrameX = _currentTile.x;
					_tiles[i].frameObjFrameY = _currentTile.y;
					_tiles[i].objectPos.x = (i % TILEX) * TILESIZE;
					_tiles[i].objectPos.y = (i / TILEY) * TILESIZE;
					_tiles[i].frameObj = frameObjSelect(_currentTile.x, _currentTile.y);
					_tiles[i].framestate = FRAMESTATE_ON;
				}
				else if (_paper->getStyle() == TILESTYLE_OBJECT)
				{
					_tiles[i].doorObjFrameX = _currentTile.x;
					_tiles[i].doorObjFrameY = _currentTile.y;
					_tiles[i].doorPos.x = (i % TILEX) * TILESIZE;
					_tiles[i].doorPos.y = (i / TILEY) * TILESIZE;
					_tiles[i].doorObj = doorObjSelect(_currentTile.x, _currentTile.y);
				}
			}
			else if (_paper->getStyle() == TILESTYLE_PROPS)
			{
				_tiles[i].propsFrameX = _currentTile.x;
				_tiles[i].propsFrameY = _currentTile.y;
				_tiles[i].props = propsSelect(_paper->getPaper().propsIndex);
			}
			else if (_paper->getStyle() == TILESTYLE_MONSTER)
			{
				_tiles[i].monsterFrameX = _currentTile.x;
				_tiles[i].monsterFrameY = _currentTile.y;
				_tiles[i].mosterPos.x = (i % TILEX) * TILESIZE;
				_tiles[i].mosterPos.y = (i / TILEY) * TILESIZE;
				_tiles[i].monster = monsterSelect(_currentTile.x, _currentTile.y);
			}
			else if (_paper->getStyle() == TILESTYLE_ITEM)
			{
				_tiles[i].itemFrameX = _currentTile.x;
				_tiles[i].itemFrameY = _currentTile.y;
				_tiles[i].itemPos.x = (i % TILEX) * TILESIZE;
				_tiles[i].itemPos.y = (i / TILEY) * TILESIZE;
				_tiles[i].item = itemSelect(_currentTile.x, _currentTile.y);
			}
			//현재 버튼이 지우개로 체크되어 있으면
			if (_paper->isEraseMode())
			{
				if (_paper->getStyle() == TILESTYLE_TERRAIN)
				{
					_tiles[i].terrainFrameX = 0;
					_tiles[i].terrainFrameY = 0;
					_tiles[i].terrain = TR_NONE_BASE;
					_tiles[i].tile = T_NONE;
				}
				//현재 버튼이 오브젝트에 체크되어 있으면
				else if (_paper->getStyle() == TILESTYLE_OBJECT)
				{
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].frameObjFrameX = 0;
					_tiles[i].frameObjFrameY = 0;
					_tiles[i].obj = OBJ_NONE;
					_tiles[i].frameObj = FRAMEOBJ_NONE;
					_tiles[i].framestate = FRAMESTATE_NONE;
					_tiles[i].doorObj = DOOR_NONE;
				}
				else if (_paper->getStyle() == TILESTYLE_PROPS)
				{
					_tiles[i].propsFrameX = 0;
					_tiles[i].propsFrameY = 0;
					_tiles[i].props = PROPS_NONE;
				}
				else if (_paper->getStyle() == TILESTYLE_MONSTER)
				{
					_tiles[i].monsterFrameX = 0;
					_tiles[i].monsterFrameY = 0;
					_tiles[i].monster = MONSTER_NONE;
				}
				else if (_paper->getStyle() == TILESTYLE_ITEM)
				{
					_tiles[i].itemFrameX = 0;
					_tiles[i].itemFrameY = 0;
					_tiles[i].item = ITEM_NONE;
				}
			}
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}