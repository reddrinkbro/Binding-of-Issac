#include "stdafx.h"
#include "mapTool.h"

void mapTool::tileRender(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
		{
			switch (_tiles[i].terrain)
			{
				case TR_BASEMENT:
				{
					_tileSampleImage[0]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_DICEROOM:
				{
					_tileSampleImage[1]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_CAVE:
				{
					_tileSampleImage[2]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_DEPTHS:
				{
					_tileSampleImage[3]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_NECROPOLIS:
				{
					_tileSampleImage[4]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_SECRETROOM:
				{
					_tileSampleImage[5]->frameRender(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].terrainFrameX,
						_tiles[i].terrainFrameY);
					break;
				}
				case TR_NONE_BASE:
				{
					
					Rectangle(getMemDC(),
						_tiles[i].rc.left - CAMERAMANAGER->getX(),
						_tiles[i].rc.top - CAMERAMANAGER->getY(),
						_tiles[i].rc.right - CAMERAMANAGER->getX(),
						_tiles[i].rc.bottom - CAMERAMANAGER->getY());
					
					break;
				}
			}
			if (_tiles[i].props == PROPS_END1)
			{
				_propsImage[0]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].propsFrameX, _tiles[i].propsFrameY);
			}
			else if (_tiles[i].props == PROPS_END2)
			{
				_propsImage[1]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].propsFrameX, _tiles[i].propsFrameY);
			}
			tileCheck(i);
			if (_tiles[i].framestate == FRAMESTATE_OFF)
			{
				_objectImage[0]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].objFrameX, _tiles[i].objFrameY);
			}
			else if (_tiles[i].framestate == FRAMESTATE_ON)
			{
				_objectImage[1]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].frameObjFrameX, _tiles[i].frameObjFrameY);
			}
			if (_tiles[i].doorObj != DOOR_NONE)
			{
				_objectImage[2]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].doorObjFrameX, _tiles[i].doorObjFrameY);
			}
			if (_tiles[i].monster != MONSTER_NONE)
			{
				_monsterImage[0]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].monsterFrameX, _tiles[i].monsterFrameY);
			}
			if (_tiles[i].item != ITEM_NONE)
			{
				_itemImage[0]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].itemFrameX, _tiles[i].itemFrameY);
			}
		}
	}
}