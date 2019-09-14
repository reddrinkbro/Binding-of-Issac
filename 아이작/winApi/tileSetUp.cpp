#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileSetup(void)
{
	_sampleRoom[0].img = IMAGEMANAGER->addImage("basement", "image/tiles/basement.bmp", 500, 350);
	_sampleRoom[1].img = IMAGEMANAGER->addImage("diceroom", "image/tiles/diceroom.bmp", 500, 350);
	_sampleRoom[2].img = IMAGEMANAGER->addImage("cave", "image/tiles/cave.bmp", 500, 350);
	_sampleRoom[3].img = IMAGEMANAGER->addImage("depths", "image/tiles/depths.bmp", 500, 350);
	_sampleRoom[4].img = IMAGEMANAGER->addImage("necropolis", "image/tiles/necropolis.bmp", 500, 350);
	_sampleRoom[5].img = IMAGEMANAGER->addImage("chest", "image/tiles/chest.bmp", 500, 350);
	
	for (int i = 0; i < _tileSampleImage.size(); i++)
	{
		_sampleRoom[i].x = _paper->getPaper().x - _sampleRoom[i].img->getWidth() /2;
		_sampleRoom[i].y = _paper->getPaper().y;
		_sampleRoom[i].rc = RectMakeCenter(_sampleRoom[i].x, _sampleRoom[i].y, _sampleRoom[i].img->getFrameX(), _sampleRoom[i].img->getHeight());
	}
	//타일 설정
	//오른쪽 샘플 맵 셋팅
	
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(_paper->getPaper().x - _tileSampleImage[_paper->getPaper().tileIndex]->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - _tileSampleImage[_paper->getPaper().tileIndex]->getHeight() / 2 -32 + i * TILESIZE,
				(_paper->getPaper().x - _tileSampleImage[_paper->getPaper().tileIndex]->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - _tileSampleImage[_paper->getPaper().tileIndex]->getHeight() / 2 -32 + i * TILESIZE + TILESIZE);
		}
	}
	
	
	for (int i = 0; i < PROPSTILEY; i++)
	{
		for (int j = 0; j < PROPSTILEX; j++)
		{
			_sampleProps[i * PROPSTILEX + j].terrainFrameX = j;
			_sampleProps[i * PROPSTILEX + j].terrainFrameY = i;

			SetRect(&_sampleProps[i * PROPSTILEX + j].rcTile,
				(_paper->getPaper().x - _propsImage[_paper->getPaper().propsIndex]->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - _propsImage[_paper->getPaper().propsIndex]->getHeight() / 2 + i * TILESIZE,
				(_paper->getPaper().x - _propsImage[_paper->getPaper().propsIndex]->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - _propsImage[_paper->getPaper().propsIndex]->getHeight() / 2 + i * TILESIZE + TILESIZE);
		}
	}
	
	for (int i = 0; i < OBJECTTILEY; i++)
	{
		for (int j = 0; j < OBJECTTILEX; j++)
		{
			_sampleObject[i * OBJECTTILEX + j].terrainFrameX = j;
			_sampleObject[i * OBJECTTILEX + j].terrainFrameY = i;

			SetRect(&_sampleObject[i * OBJECTTILEX + j].rcTile,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("object")->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("object")->getHeight() / 2 + i * TILESIZE,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("object")->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("object")->getHeight() / 2 + i * TILESIZE + TILESIZE);
		}
	}
	//_objectImage[_paper->getPaper().objectIndex]
	for (int i = 0; i < FRAMEOBJECTTILEY; i++)
	{
		for (int j = 0; j < FRAMEOBJECTTILEX; j++)
		{
			_sampleFrameObject[i * FRAMEOBJECTTILEX + j].terrainFrameX = j;
			_sampleFrameObject[i * FRAMEOBJECTTILEX + j].terrainFrameY = i;

			SetRect(&_sampleFrameObject[i * FRAMEOBJECTTILEX + j].rcTile,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("frameObject")->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("frameObject")->getHeight() / 2 + i * TILESIZE,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("frameObject")->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("frameObject")->getHeight() / 2 + i * TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < MONSTEROBJECTTILEY; i++)
	{
		for (int j = 0; j < MONSTEROBJECTTILEX; j++)
		{
			_sampleMonsterObject[i * MONSTEROBJECTTILEX + j].terrainFrameX = j;
			_sampleMonsterObject[i * MONSTEROBJECTTILEX + j].terrainFrameY = i;

			SetRect(&_sampleMonsterObject[i * MONSTEROBJECTTILEX + j].rcTile,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("monster")->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("monster")->getHeight() / 2 + i * TILESIZE,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("monster")->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("monster")->getHeight() / 2 + i * TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < ITEMOBJECTTILEY; i++)
	{
		for (int j = 0; j < ITEMOBJECTTILEX; j++)
		{
			_sampleItemObject[i * ITEMOBJECTTILEX + j].terrainFrameX = j;
			_sampleItemObject[i * ITEMOBJECTTILEX + j].terrainFrameY = i;

			SetRect(&_sampleItemObject[i * MONSTEROBJECTTILEX + j].rcTile,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("item")->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("item")->getHeight() / 2 + i * TILESIZE,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("item")->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("item")->getHeight() / 2 + i * TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < DOORTILEY; i++)
	{
		for (int j = 0; j < DOORTILEX; j++)
		{
			_sampleDoor[i * DOORTILEX + j].terrainFrameX = j;
			_sampleDoor[i * DOORTILEX + j].terrainFrameY = i;

			SetRect(&_sampleDoor[i * DOORTILEX + j].rcTile,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("door")->getWidth() / 2) + j * TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("door")->getHeight() / 2 - 10 + i * TILESIZE,
				(_paper->getPaper().x - IMAGEMANAGER->findImage("door")->getWidth() / 2) + j * TILESIZE + TILESIZE,
				_paper->getPaper().y - IMAGEMANAGER->findImage("door")->getHeight() / 2 - 10 + i * TILESIZE + TILESIZE);
		}
	}
}
