#include "stdafx.h"
#include "player.h"
#include "itemManager.h"


void player::itemGet(void)
{
	EFFECTMANAGER->play("starFlash", _head.x - CAMERAMANAGER->getX(), _head.y - 15 - CAMERAMANAGER->getY());
	_itemGetCount--;
	if (_itemGetCount < 0)
	{
		_state = ISAACSTATE_NONE;
		_itemGetCount = 100;
		for (int i = 0; i < _item->getPentagram().size(); i++)
		{
			if (!_item->getPentagram()[i].pentagram->getPentagram().isMove)
			{
				_item->removePentagram();
				_head.img = IMAGEMANAGER->findImage("pentagramHead");
				_body.atk += 1.0f;
			}
		}
		for (int i = 0; i < _item->getOuijaboard().size(); i++)
		{
			if (!_item->getOuijaboard()[i].ouijaboard->getOuijaboard().isMove)
			{
				_item->removeOuijaboard();
				_head.img = IMAGEMANAGER->findImage("ouijaboardHead");
				_ouijaboardOn = true;
			}
		}
		for (int i = 0; i < _item->getGhostBaby().size(); i++)
		{
			if (!_item->getGhostBaby()[i].ghostBaby->getGhostBaby().isMove)
			{
				_item->removeHarleQuinBaby();
				if (!_familiarOn)
				{
					//패밀리어 초기화 및 선언
					_familiar = new familiar;
					_familiar->init(_body.x + 40, _body.y);
					_familiarOn = true;
				}
			}
		}
	}
}
