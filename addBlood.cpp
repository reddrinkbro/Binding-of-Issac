#include "stdafx.h"
#include "enemyManager.h"

void enemyManager::addBlood(float x, float y)
{
	int rand = RND->getInt(14);
	blood _blood;
	ZeroMemory(&_blood, sizeof(blood));
	
	switch (rand)
	{
	case 0:
		_blood.img = IMAGEMANAGER->addImage("blood1", "image/enemy/effect/blood1.bmp", 78, 22, true, RGB(255, 0, 255));
		break;
	case 1:
		_blood.img = IMAGEMANAGER->addImage("blood2", "image/enemy/effect/blood2.bmp", 46, 18, true, RGB(255, 0, 255));
		break;
	case 2:
		_blood.img = IMAGEMANAGER->addImage("blood3", "image/enemy/effect/blood3.bmp", 42, 18, true, RGB(255, 0, 255));
		break;
	case 3:
		_blood.img = IMAGEMANAGER->addImage("blood4", "image/enemy/effect/blood4.bmp", 30, 12, true, RGB(255, 0, 255));
		break;
	case 4:
		_blood.img = IMAGEMANAGER->addImage("blood5", "image/enemy/effect/blood5.bmp", 80, 38, true, RGB(255, 0, 255));
		break;
	case 5:
		_blood.img = IMAGEMANAGER->addImage("blood6", "image/enemy/effect/blood6.bmp", 46, 18, true, RGB(255, 0, 255));
		break;
	case 6:
		_blood.img = IMAGEMANAGER->addImage("blood7", "image/enemy/effect/blood7.bmp", 34, 16, true, RGB(255, 0, 255));
		break;
	case 7:
		_blood.img = IMAGEMANAGER->addImage("blood8", "image/enemy/effect/blood8.bmp", 22, 14, true, RGB(255, 0, 255));
		break;
	case 8:
		_blood.img = IMAGEMANAGER->addImage("blood9", "image/enemy/effect/blood9.bmp", 97, 63, true, RGB(255, 0, 255));
		break;
	case 9:
		_blood.img = IMAGEMANAGER->addImage("blood10", "image/enemy/effect/blood10.bmp", 118, 60, true, RGB(255, 0, 255));
		break;
	case 10:
		_blood.img = IMAGEMANAGER->addImage("blood11", "image/enemy/effect/blood11.bmp", 113, 78, true, RGB(255, 0, 255));
		break;
	case 11:
		_blood.img = IMAGEMANAGER->addImage("blood12", "image/enemy/effect/blood12.bmp", 99, 55, true, RGB(255, 0, 255));
		break;
	case 12:
		_blood.img = IMAGEMANAGER->addImage("blood13", "image/enemy/effect/blood13.bmp", 98, 55, true, RGB(255, 0, 255));
		break;
	case 13:
		_blood.img = IMAGEMANAGER->addImage("blood14", "image/enemy/effect/blood14.bmp", 113, 97, true, RGB(255, 0, 255));
		break;
	}

	_blood.x = x;
	_blood.y = y;
	_vBlood.push_back(_blood);
}