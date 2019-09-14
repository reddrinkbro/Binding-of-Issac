
#include "stdafx.h"
#include "dungeonMap.h"

HRESULT dungeonMap::init(BOSSSELECT bossSelect)
{
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("basementTile", "image/tiles/basementTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("diceroomTile", "image/tiles/diceroomTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("caveTile", "image/tiles/caveTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("depthsTile", "image/tiles/depthsTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("necropolisTile", "image/tiles/necropolisTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("chestTile", "image/tiles/chestTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_objectImage.push_back(IMAGEMANAGER->addFrameImage("object", "image/object/object1.bmp", 512, 320, OBJECTTILEX, OBJECTTILEY, true, RGB(255, 0, 255)));
	_objectImage.push_back(IMAGEMANAGER->addFrameImage("frameObject", "image/object/object2.bmp", 256, 128, FRAMEOBJECTTILEX, FRAMEOBJECTTILEY, true, RGB(255, 0, 255)));
	_propsImage.push_back(IMAGEMANAGER->addFrameImage("props1", "image/object/props1.bmp", 576, 384, 9, 6, true, RGB(255, 0, 255)));
	_propsImage.push_back(IMAGEMANAGER->addFrameImage("props2", "image/object/props2.bmp", 576, 384, 9, 6, true, RGB(255, 0, 255)));
	IMAGEMANAGER->addFrameImage("door", "image/object/door.bmp", 640, 512, DOORTILEX, DOORTILEY, true, RGB(255, 0, 255));
	_mapSelect = RND->getInt(3);
	this->load();
	_cutScene = new cutScene;
	_cutScene->init(bossSelect);
	return S_OK;
}

void dungeonMap::release(void)
{
	SAFE_DELETE(_cutScene);
}

void dungeonMap::update(void)
{
	if(_cutScene->getIsOn()) _cutScene->update();
}

void dungeonMap::render(void)
{
	this->tileRender();
	if (_cutScene->getIsOn()) _cutScene->render();
}

void dungeonMap::load(void)
{
	HANDLE file;
	DWORD read;
	if (_mapSelect == 0)
	{
		file = CreateFile("save/isaacMap.map",
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	else if (_mapSelect == 1)
	{
		file = CreateFile("save/isaacMap1.map",
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	else if (_mapSelect == 2)
	{
		file = CreateFile("save/isaacMap2.map",
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].tile == T_WALL1) _attribute[i] = ATTR_UNMOVE_WALL1;
		else if (_tiles[i].tile == T_WALL2) _attribute[i] = ATTR_UNMOVE_WALL2;
		if (_tiles[i].obj == OBJ_BLOCK) _attribute[i] = ATTR_BLOCK_NO_BREAK;
		else if (_tiles[i].obj == OBJ_BLOCK2) _attribute[i] = ATTR_BLOCK_BREAK;
		else if (_tiles[i].obj == OBJ_STONE) _attribute[i] = ATTR_STONE;
		else if (_tiles[i].obj == OBJ_SPIKE) _attribute[i] = ATTR_SPIKE;
		else if (_tiles[i].obj == OBJ_SPIDERWEB) _attribute[i] = ATTR_SPIDERWEB;
		if (_tiles[i].monster == MONSTER_ATTACKFLY) _attribute[i] = ATTR_MONSTER_ATTACKFLY;
		else if (_tiles[i].monster == MONSTER_GAPER) _attribute[i] = ATTR_MONSTER_GAPER;
		else if (_tiles[i].monster == MONSTER_HORF) _attribute[i] = ATTR_MONSTER_HORF;
		else if (_tiles[i].monster == MONSTER_CHARGER) _attribute[i] = ATTR_MONSTER_CHARGER;
		else if (_tiles[i].monster == MONSTER_LEVEL2FLY) _attribute[i] = ATTR_MONSTER_LEVEL2FLY;
		else if (_tiles[i].monster == MONSTER_BLUBBER) _attribute[i] = ATTR_MONSTER_BLUBBER;
		else if (_tiles[i].monster == MONSTER_CLOTTY) _attribute[i] = ATTR_MONSTER_CLOTTY;
		else if (_tiles[i].monster == MONSTER_TUMOR) _attribute[i] = ATTR_MONSTER_TUMOR;
		if (_tiles[i].doorObj == DOOR_UP || _tiles[i].doorObj == SHOP_DOOR_UP) _attribute[i] = ATTR_DOOR_UP;
		else if (_tiles[i].doorObj == DOOR_DOWN || _tiles[i].doorObj == SHOP_DOOR_DOWN) _attribute[i] = ATTR_DOOR_DOWN;
		else if (_tiles[i].doorObj == DOOR_LEFT || _tiles[i].doorObj == SHOP_DOOR_LEFT) _attribute[i] = ATTR_DOOR_LEFT;
		else if (_tiles[i].doorObj == DOOR_RIGHT || _tiles[i].doorObj == SHOP_DOOR_RIGHT) _attribute[i] = ATTR_DOOR_RIGHT;
		else if (_tiles[i].doorObj == BOSS_DOOR_UP) _attribute[i] = ATTR_BOSS_DOOR_UP;
		else if (_tiles[i].doorObj == BOSS_DOOR_DOWN) _attribute[i] = ATTR_BOSS_DOOR_DOWN;
		else if (_tiles[i].doorObj == BOSS_DOOR_LEFT) _attribute[i] = ATTR_BOSS_DOOR_LEFT;
		else if (_tiles[i].doorObj == BOSS_DOOR_RIGHT ) _attribute[i] = ATTR_BOSS_DOOR_RIGHT;
		if (_tiles[i].frameObj == FRAMEOBJ_POOP1) _attribute[i] = ATTR_POOP1;
		else if (_tiles[i].frameObj == FRAMEOBJ_POOP2) _attribute[i] = ATTR_POOP2;
	}
	CAMERAMANAGER->setCameraPos(0, 0);
}

void dungeonMap::tileRender(void)
{
	char str[128];
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left > -TILESIZE + CAMERAMANAGER->getX() && _tiles[i].rc.right <CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_tiles[i].rc.top >-TILESIZE + CAMERAMANAGER->getY() && _tiles[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
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
			if (_tiles[i].obj != OBJ_NONE)
			{
				_objectImage[0]->frameRender(getMemDC(),
					_tiles[i].rc.left - CAMERAMANAGER->getX(), _tiles[i].rc.top - CAMERAMANAGER->getY(),
					_tiles[i].objFrameX, _tiles[i].objFrameY);
			}
		}
	}
}