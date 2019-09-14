#include "stdafx.h"
#include "cutScene.h"

HRESULT cutScene::init(BOSSSELECT select)
{
	_isaac.isaac = IMAGEMANAGER->addImage("stage_isaac", "image/cutScene/stage_isaac.bmp", 149, 149, true, RGB(255, 0, 255));
	_isaac.name = IMAGEMANAGER->addImage("vsname_isaac", "image/cutScene/vsname_isaac.bmp", 196, 62, true, RGB(255, 0, 255));
	_isaac.celler = IMAGEMANAGER->addImage("stage_issac_cellar", "image/cutScene/stage_issac_cellar.bmp", 345, 93, true, RGB(255, 0, 255));
	_isaac.x = -_isaac.isaac->getWidth() - 100;
	_isaac.y = CAMERAMANAGER->getGameMaxRenderY() / 2;
	if (select == BOSSSELECT_DUKEOFFLLIES)
	{
		_boss.boss = IMAGEMANAGER->addImage("portrait_dukeofflies", "image/cutScene/portrait_dukeofflies.bmp", 256, 256, true, RGB(255, 0, 255));
		_boss.name = IMAGEMANAGER->addImage("vsname_dukeofflies", "image/cutScene/vsname_dukeofflies.bmp", 288, 78, true, RGB(255, 0, 255));
	}
	else if (select == BOSSSELECT_MONSTRO)
	{
		_boss.boss = IMAGEMANAGER->addImage("portrait_monstro", "image/cutScene/portrait_monstro.bmp", 256, 256, true, RGB(255, 0, 255));
		_boss.name = IMAGEMANAGER->addImage("vsname_monstro", "image/cutScene/vsname_monstro.bmp", 284, 76, true, RGB(255, 0, 255));
	}
	else if (select == BOSSSELECT_MEGAMAW)
	{
		_boss.boss = IMAGEMANAGER->addImage("portrait_megamaw", "image/cutScene/portrait_megamaw.bmp", 256, 256, true, RGB(255, 0, 255));
		_boss.name = IMAGEMANAGER->addImage("vsname_megamaw", "image/cutScene/vsname_megamaw.bmp", 322, 56, true, RGB(255, 0, 255));
	}
	_boss.celler = IMAGEMANAGER->addImage("stage_boss_cellar", "image/cutScene/stage_boss_cellar.bmp", 345, 93, true, RGB(255, 0, 255));
	
	_boss.x = CAMERAMANAGER->getGameMaxRenderX() + 80;
	_boss.y = CAMERAMANAGER->getGameMaxRenderY() / 2 -50;
	_backGround = IMAGEMANAGER->addImage("background","image/cutScene/bgblack.bmp", CAMERAMANAGER->getGameMaxRenderX(), CAMERAMANAGER->getGameMaxRenderY());
	_versus = IMAGEMANAGER->addImage("VS","image/cutScene/VS.bmp", 148, 82, true, RGB(255, 0, 255));
	_speed = 1.2f;
	_distance = 100;
	_restTime = 250;
	_alpha = 255;
	_isOn = false;
	
	return S_OK;
}

void cutScene::release(void)
{
}

void cutScene::update(void)
{
	SOUNDMANAGER->stop("basement");
	if (_distance == 100)
	{
		SOUNDMANAGER->play("boss fight intro jingle", VOLUME->getMusicVolume() / 10);
		SOUNDMANAGER->play("castleportcullis", VOLUME->getSfxVolume() / 10);
	}
	_distance--;
	if (_distance > 0)
	{
		if(_distance > 60) speedUp(true);
		else speedDown();
		_isaac.x+=_speed;
		_boss.x-=_speed;
	}
	else
	{
		_restTime --;
		if (_restTime < 0)
		{
			if (_alpha >= 0)
			{
				_alpha -= 6;
			}
			speedUp(false);
			_isaac.x -= _speed;
			_boss.x += _speed;
		}
		else
		{
			_isaac.x += _speed;
			_boss.x -= _speed;
		}
	}
	if (!SOUNDMANAGER->isPlaySound("boss fight intro jingle"))
	{
		SOUNDMANAGER->stop("castleportcullis");
		SOUNDMANAGER->play("basic boss fight", VOLUME->getMusicVolume() / 10);
		_isOn = false;
	}
}

void cutScene::render(void)
{
	_backGround->render(getMemDC());
	_isaac.celler->render(getMemDC(), _isaac.x - _isaac.isaac->getWidth()/2, _isaac.y + 100);
	_isaac.isaac->render(getMemDC(), _isaac.x, _isaac.y);
	_isaac.name->render(getMemDC(), _isaac.x, _isaac.y - 200);
	_boss.celler->render(getMemDC(), _boss.x - 50, _boss.y +_boss.boss->getHeight() - 100);
	_boss.boss->render(getMemDC(), _boss.x, _boss.y);
	_boss.name->render(getMemDC(), _boss.x - 50, _boss.y - 150);
	_versus->alphaRender(getMemDC(), (_isaac.x + _boss.x) / 2, _isaac.y - 200, _alpha);
}

void cutScene::speedUp(bool isGoNear)
{
	if(isGoNear)_speed += 0.4f;
	else _speed += 1.6f;
}

void cutScene::speedDown(void)
{
	_speed = 0.2f;
}
