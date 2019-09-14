#include "stdafx.h"
#include "mapTool.h"
HRESULT mapTool::init(void)
{
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("basementTile", "image/tiles/basementTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("diceroomTile", "image/tiles/diceroomTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("caveTile", "image/tiles/caveTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("depthsTile", "image/tiles/depthsTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("necropolisTile", "image/tiles/necropolisTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_tileSampleImage.push_back(IMAGEMANAGER->addFrameImage("chestTile", "image/tiles/chestTile.bmp", 576, 448, SAMPLETILEX, SAMPLETILEY));
	_objectImage.push_back(IMAGEMANAGER->addFrameImage("object", "image/object/object1.bmp", 512, 320, OBJECTTILEX, OBJECTTILEY, true, RGB(255, 0, 255)));
	_objectImage.push_back(IMAGEMANAGER->addFrameImage("frameObject", "image/object/object2.bmp", 256, 128, FRAMEOBJECTTILEX, FRAMEOBJECTTILEY, true, RGB(255, 0, 255)));
	_objectImage.push_back(IMAGEMANAGER->addFrameImage("door", "image/object/door.bmp", 320, 256, DOORTILEX, DOORTILEY, true, RGB(255, 0, 255)));
	_propsImage.push_back(IMAGEMANAGER->addFrameImage("props1", "image/object/props1.bmp", 576, 384, 9, 6, true, RGB(255, 0, 255)));
	_propsImage.push_back(IMAGEMANAGER->addFrameImage("props2", "image/object/props2.bmp", 576, 384, 9, 6, true, RGB(255, 0, 255)));
	_monsterImage.push_back(IMAGEMANAGER->addFrameImage("monster", "image/object/monster.bmp", 256, 192, 4, 3, true, RGB(255, 0, 255)));
	_itemImage.push_back(IMAGEMANAGER->addFrameImage("item", "image/object/item.bmp", 256, 192, 4, 3, true, RGB(255, 0, 255)));
	_paper = new tilesPaper;
	_paper->init(_tileSampleImage.size(), _objectImage.size(), _propsImage.size());
	_miniMap = new miniMap;
	_miniMap->init();
	maptoolSetup();
	tileSetup();

	//현재타일 초기화(지형)
	_currentTile.x = 0;
	_currentTile.y = 0; 
	_isTileBrushOn = false;
	_dIndex1 = _dIndex2 = 0;
	_eIndex1 = _eIndex2 = 0;
	_sIndex = 0;
	this->load();
	return S_OK;
}

void mapTool::release(void)
{
	SAFE_DELETE(_paper);
}

void mapTool::update(void)
{
	_paper->update();
	if (PtInRect(&_paper->getPaper().rc, _ptMouse) &&_paper->getPaper().isOn)
	{
		_mouseInpaper = true;
	}
	else
	{
		_mouseInpaper = false;
	}
	if (_paper->getStyle() == TILESTYLE_NONE)
	{
		if (_paper->isSaveOn())
		{
			save();
			_paper->paperUp();
		}
		else if (_paper->isLoadOn())
		{
			//load();
			_paper->paperUp();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//오브젝트일때 생각 해봐야함
		_paper->selectStyle();
		_paper->arrowClick();
		_paper->dragMode();
		_paper->usingErase();
		_paper->saveLoad();
		_paper->shopMode();
		_paper->back();
		_isTileBrushOn = true;
		if (_paper->isDrawMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex1 = i;
						break;
					}
				}
			}
		}
		else if (_paper->isEraseMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex3 = i;
						break;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_paper->isDrawMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex2 = i;
						break;
					}
				}
			}
			_dIndex1 = _xIndex2 / TILEX - _xIndex1 / TILEX;
			_dIndex2 = (_xIndex2 - (_xIndex1 % TILEX) - (TILEX * _dIndex1)) % TILEX;
		}
		else if (_paper->isEraseMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex4 = i;
						break;
					}
				}
			}
			_eIndex1 = _xIndex4 / TILEX - _xIndex3 / TILEX;
			_eIndex2 = (_xIndex4 - (_xIndex3 % TILEX) - (TILEX * _eIndex1)) % TILEX;
		}
		else if (_paper->isShopMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_sIndex = i;
						break;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_paper->isDrawMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex2 = i;
						_dIndex1 = _xIndex2 / TILEX - _xIndex1 / TILEX;
						_dIndex2 = (_xIndex2 - (_xIndex1 % TILEX) - (TILEX * _dIndex1)) % TILEX;
						_isTileBrushOn = false;
						tileDraw();
						break;
					}
				}
			}
		}
		else if (_paper->isEraseMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_xIndex4 = i;
						_eIndex1 = _xIndex4 / TILEX - _xIndex3 / TILEX;
						_eIndex2 = (_xIndex4 - (_xIndex3 % TILEX) - (TILEX * _eIndex1)) % TILEX;
						_isTileBrushOn = false;
						erase();
						break;
					}
				}
			}
		}
		else if (_paper->isShopMode())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_tiles[i].rc.left > CAMERAMANAGER->getRenderX() && _tiles[i].rc.right <CAMERAMANAGER->getMaxRenderX() && _tiles[i].rc.top >CAMERAMANAGER->getRenderY() && _tiles[i].rc.bottom < CAMERAMANAGER->getMaxRenderY())
				{
					if (PtInRect(&_tiles[i].rc, PointMake(_ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY())))
					{
						_sIndex = i;
						shopMap();
						break;
					}
				}
			}
		}
	}
	
}

void mapTool::render(void)
{
	tileRender();
	_paper->render();
	if (_paper->getPaper().currentFrameY == _paper->getPaper().img->getMaxFrameY())
	{
		if (_paper->getStyle() == TILESTYLE_TERRAIN)
		{
			if(_paper->isDrawMode()) _sampleRoom[_paper->getPaper().tileIndex].img->render(getMemDC(),
				_sampleRoom[_paper->getPaper().tileIndex].rc.left,
				_sampleRoom[_paper->getPaper().tileIndex].rc.top);
			else _tileSampleImage[_paper->getPaper().tileIndex]->render(getMemDC(),
				_paper->getPaper().x - _tileSampleImage[_paper->getPaper().tileIndex]->getWidth() / 2,
				_paper->getPaper().y - _tileSampleImage[_paper->getPaper().tileIndex]->getHeight() / 2 - 32);
		}
		else if (_paper->getStyle() == TILESTYLE_OBJECT)
		{
			if (_paper->objectIndex() == 2)
			{
				IMAGEMANAGER->findImage("door")->render(getMemDC(),
					_paper->getPaper().x - IMAGEMANAGER->findImage("door")->getWidth() / 2,
					_paper->getPaper().y - IMAGEMANAGER->findImage("door")->getHeight() / 2 - 10);
			}
			else
			{
				_objectImage[_paper->getPaper().objectIndex]->render(getMemDC(), _paper->getPaper().x - _objectImage[_paper->getPaper().objectIndex]->getWidth() / 2,
					_paper->getPaper().y - _objectImage[_paper->getPaper().objectIndex]->getHeight() / 2);
			}
		}
		else if (_paper->getStyle() == TILESTYLE_PROPS)
		{
			_propsImage[_paper->getPaper().propsIndex]->render(getMemDC(),
				_paper->getPaper().x - _propsImage[_paper->getPaper().propsIndex]->getWidth() / 2 ,
				_paper->getPaper().y - _propsImage[_paper->getPaper().propsIndex]->getHeight() /2  );
		}
		else if (_paper->getStyle() == TILESTYLE_MONSTER)
		{
			_monsterImage[_paper->getPaper().monsterIndex]->render(getMemDC(),
				_paper->getPaper().x - _monsterImage[_paper->getPaper().monsterIndex]->getWidth() / 2,
				_paper->getPaper().y - _monsterImage[_paper->getPaper().monsterIndex]->getHeight() / 2);
		}
		else if (_paper->getStyle() == TILESTYLE_ITEM)
		{
			
			_itemImage[_paper->getPaper().itemIndex]->render(getMemDC(),
				_paper->getPaper().x - _itemImage[_paper->getPaper().itemIndex]->getWidth() / 2,
				_paper->getPaper().y - _itemImage[_paper->getPaper().itemIndex]->getHeight() / 2);
		}
	}
	if (KEYMANAGER->isToggleKey('M'))
	{
		_miniMap->render();
	}
}

void mapTool::maptoolSetup()
{
	//왼쪽맵 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//기본으로 깔리는 타일 셋팅
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		_tiles[i].propsFrameX = 0;
		_tiles[i].propsFrameY = 0;

		_tiles[i].doorObjFrameX = 0;
		_tiles[i].doorObjFrameY = 0;

		_tiles[i].frameObjFrameX = 0;
		_tiles[i].frameObjFrameY = 0;

		_tiles[i].monsterFrameX = 0;
		_tiles[i].monsterFrameY = 0;
		
		_tiles[i].itemFrameX = 0;
		_tiles[i].itemFrameY = 0;

		_tiles[i].mosterPos.x = 0;
		_tiles[i].mosterPos.y = 0;

		_tiles[i].itemPos.x = 0;
		_tiles[i].itemPos.y = 0;

		_tiles[i].objectPos.x = 0;
		_tiles[i].objectPos.y = 0;

		_tiles[i].doorPos.x = 0;
		_tiles[i].doorPos.y = 0;
	
		_tiles[i].terrain = TR_NONE_BASE;
		_tiles[i].obj = OBJ_NONE;
		_tiles[i].props = PROPS_NONE;
		_tiles[i].doorObj = DOOR_NONE;
		_tiles[i].frameObj = FRAMEOBJ_NONE;
		_tiles[i].tile = T_NONE;
		_tiles[i].framestate = FRAMESTATE_NONE;
		_tiles[i].monster = MONSTER_NONE;
		_tiles[i].item = ITEM_NONE;
	}
}

void mapTool::save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile("save/isaacMap1.map",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}

void mapTool::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("save/isaacMap1.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

TERRAIN mapTool::terrainSelect(int index)
{
	//베이스
	if (index == 0)
	{
		return TR_BASEMENT;
	}

	//다이스룸
	else if (index == 1)
	{
		return TR_DICEROOM;
	}

	//케이브
	else if (index == 2)
	{
		return TR_CAVE;
	}

	//체스트
	else if (index == 3)
	{
		return TR_DEPTHS;
	}
	//네크로폴리스
	else if (index == 4)
	{
		return TR_NECROPOLIS;
	}

	//시크릿룸
	else if (index == 5)
	{
		return TR_SECRETROOM;
	}
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	//폭탄에 부숴지는 벽
	if (frameX < 8 && frameY < 2)
	{
		return OBJ_BLOCK;
	}

	//폭탄에 안부숴지는 벽
	else if (frameX < 8 && frameY >= 2 && frameY < 4)
	{
		return OBJ_BLOCK2;
	}

	//스파이크
	else if (frameX < 6 && frameY == 4)
	{
		return OBJ_SPIKE;
	}

	//거미줄
	else if (frameX ==6 && frameY == 4)
	{
		return OBJ_SPIDERWEB;
	}
	
	//돌
	else if (frameX == 7 && frameY == 4)
	{
		return OBJ_STONE;
	}
}

TERRAINTILE mapTool::tileSelect(int frameX, int frameY)
{
	if (frameX > 1 && frameX < 7 && frameY >1 && frameY <5)
	{
		return T_TILE;
	}
	else if ((frameX == 1 || frameX == 7) &&(frameY > 1 && frameY <5))
	{
		return T_WALL1;
	}
	return T_WALL2;
}

FRAMEOBJECT mapTool::frameObjSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return FRAMEOBJ_HOLE;
	}
	else if (frameX == 1 && frameY == 0)
	{
		return FRAMEOBJ_BARREL;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return FRAMEOBJ_FIREWOOD;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return FRAMEOBJ_CHEST;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return FRAMEOBJ_SPIKE1;
	}
	else if (frameX == 1 && frameY == 1)
	{
		return FRAMEOBJ_SPIKE2;
	}
	else if (frameX == 2 && frameY == 1)
	{
		return FRAMEOBJ_POOP1;
	}
	else if (frameX == 3 && frameY == 1)
	{
		return FRAMEOBJ_POOP2;
	}
}

DOOROBJECT mapTool::doorObjSelect(int frameX, int frameY)
{
	if (frameY == 0 && frameX < 3)
	{
		return DOOR_UP;
	}
	else if (frameY == 1 && frameX < 3)
	{
		return DOOR_RIGHT;
	}
	else if (frameY == 2 && frameX < 3)
	{
		return DOOR_DOWN;
	}
	else if (frameY == 3 && frameX < 3)
	{
		return DOOR_LEFT;
	}
	else if (frameY == 0 && frameX == 3)
	{
		return SHOP_DOOR_UP;
	}
	else if (frameY == 1 && frameX == 3)
	{
		return SHOP_DOOR_RIGHT;
	}
	else if (frameY == 2 && frameX == 3)
	{
		return SHOP_DOOR_DOWN;
	}
	else if (frameY == 3 && frameX == 3)
	{
		return SHOP_DOOR_LEFT;
	}
	else if (frameY == 0 && frameX == 4)
	{
		return BOSS_DOOR_UP;
	}
	else if (frameY == 1 && frameX == 4)
	{
		return BOSS_DOOR_RIGHT;
	}
	else if (frameY == 2 && frameX == 4)
	{
		return BOSS_DOOR_DOWN;
	}
	else if (frameY == 3 && frameX == 4)
	{
		return BOSS_DOOR_LEFT;
	}
}

PROPS mapTool::propsSelect(int index)
{
	if (index == 0)
	{
		return PROPS_END1;
	}

	else if (index == 1)
	{
		return PROPS_END2;
	}
}

MONSTER mapTool::monsterSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return MONSTER_ATTACKFLY;
	}
	else if (frameX == 1 && frameY == 0)
	{
		return MONSTER_GAPER;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return MONSTER_HORF;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return MONSTER_HOPPER;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return MONSTER_CHARGER;
	}
	else if (frameX == 1 && frameY == 1)
	{
		return MONSTER_LEVEL2FLY;
	}
	else if (frameX == 2 && frameY == 1)
	{
		return MONSTER_BLUBBER;
	}
	else if (frameX == 3 && frameY == 1)
	{
		return MONSTER_CLOTTY;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return MONSTER_TUMOR;
	}
	else if (frameX == 1 && frameY == 2)
	{
		return MONSTER_DUKEOFFLIES;
	}
	else if (frameX == 2 && frameY == 2)
	{
		return MONSTER_MONSTRO;
	}
	else if (frameX == 3 && frameY == 2)
	{
		return MONSTER_MEGAMAW;
	}
}

ITEM mapTool::itemSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return ITEM_COIN;
	}
	else if (frameX == 1 && frameY == 0)
	{
		return ITEM_KEY;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return ITEM_BOMB;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return ITEM_HP;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return ITEM_PILL_ATKUP;
	}
	else if (frameX == 1 && frameY == 1)
	{
		return ITEM_PILL_SPEEDUP;
	}
	else if (frameX == 2 && frameY == 1)
	{
		return ITEM_PILL_ATKDOWN;
	}
	else if (frameX == 3 && frameY == 1)
	{
		return ITEM_PILL_SPEEDDOWN;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return ITEM_FAMILIAR;
	}
	else if (frameX == 1 && frameY == 2)
	{
		return ITEM_OUIJABOARD;
	}
	else if (frameX == 2 && frameY == 2)
	{
		return ITEM_PENTAGRAM;
	}
}
