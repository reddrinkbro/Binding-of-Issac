#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "dungeonMap.h"
#include "itemManager.h"
HRESULT player::init(float x, float y)
{
	//머리 부분
	IMAGEMANAGER->addFrameImage("isaacHead", "image/character/isaacHead.bmp", 128, 256, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pentagramHead", "image/character/pentagramHead.bmp", 128, 256, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ouijaboardHead", "image/character/ouijaboardHead.bmp", 128, 256, 2, 4, true, RGB(255, 0, 255));
	//몸통 부분 초기화
	_body.img = IMAGEMANAGER->addFrameImage("isaacBody", "image/character/isaacBody.bmp", 640, 192, 10, 3, true, RGB(255, 0, 255));
	_body.x = x;
	_body.y = y;
	_body.currentSpeed = 0.0f;
	_body.maxSpeed = 2.5f;
	_body.count = 0;
	_body.currentX = 2;
	_body.currentY = 0;
	_body.maxHp = 6;
	_body.atk = 1.0f;
	_body.currentHp = _body.maxHp;
	_body.bodyState = BODYSTATE_DOWN;
	_body.isMove = false;
	_body.isSlow = false;
	//머리 부분 초기화
	_head.img = IMAGEMANAGER->findImage("isaacHead");
	_head.x = _body.x;
	_head.y = _body.y - _body.img->getFrameHeight() / 2 + 13;
	_head.count = 0;
	_head.currentX = 0;
	_head.currentY = 0;
	_head.headState = HEADSTATE_DOWN;
	//총알 초기화 및 선언
	_baseBullet = new playerBaseBullet;
	_baseBullet->init(350, 55);
	//UI 초기화 및 선언
	_playerUI = new playerUI;
	_playerUI->init();
	//플레이어가 공격당했을때
	IMAGEMANAGER->addImage("playerHit", "image/character/playerHit.bmp", 64, 64, true, RGB(255, 0, 255));
	//아이템을 얻었을때
	IMAGEMANAGER->addImage("itemGet", "image/character/itemGet.bmp", 64, 64, true, RGB(255, 0, 255));
	//플레이어가 죽었을때
	IMAGEMANAGER->addImage("playerDie", "image/character/playerDie.bmp", 72, 54, true, RGB(255, 0, 255));
	//버프일때
	IMAGEMANAGER->addImage("playerBuff", "image/character/playerBuff.bmp", 64, 64, true, RGB(255, 0, 255));
	//디버프일때
	IMAGEMANAGER->addImage("playerDebuff", "image/character/playerDebuff.bmp", 64, 64, true, RGB(255, 0, 255));
	//맵 이동 할때
	IMAGEMANAGER->addFrameImage("mapMove", "image/character/mapMove.bmp", 288, 96, 3, 1, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("starFlash", "image/effect/starFlash.bmp", 768, 64, 64, 64, 12, 3);
	_alpha = 100;
	_alphaCount = 200;
	_mapMoveDistance = 10.0f;
	_flightTime = 15.0f;
	_isAlphaValueIncrease = true;
	_state = ISAACSTATE_NONE;
	_itemGetCount = 100;
	_familiarOn = false;
	_ouijaboardOn = false;
	_shadow = new shadow;
	_shadow->init(SHADOWSIZE_MEDIUM);
	tileSetUp();
	_ghost.img = IMAGEMANAGER->addFrameImage("ghost", "image/character/ghost.bmp", 295, 64, 5, 1, true, RGB(255, 0, 255));
	_ghost.count = 0;
	_ghost.speed = 1.0f;
	_ghost.currentX = 0;
	_ghost.distnace = 150.0f;
	return S_OK;
}

void player::release(void)
{
	_baseBullet->release();
	SAFE_DELETE(_baseBullet);
	_playerUI->release();
	SAFE_DELETE(_playerUI);
	if (_familiarOn)
	{
		_familiar->release();
		SAFE_DELETE(_familiar);
	}
	_shadow->release();
	SAFE_DELETE(_shadow);
}

void player::update(void)
{
	//몸통 움직임
	if(_state != ISAACSTATE_DIE) this->move();
	if (_state == ISAACSTATE_HIT)
	{
		playerHit();
	}
	else if (_state == ISAACSTATE_NONE)
	{
		//총알발사
		this->fire();
	}
	else if (_state == ISAACSTATE_ITEMGET)
	{
		itemGet();
	}
	else if (_state == ISAACSTATE_BUFF)
	{
		_itemGetCount--;
		if (_itemGetCount < 0)
		{
			_state = ISAACSTATE_NONE;
			_itemGetCount = 100;
		}
	}
	else if(_state == ISAACSTATE_DEBUFF)
	{
		_itemGetCount--;
		if (_itemGetCount < 0)
		{
			_state = ISAACSTATE_NONE;
			_itemGetCount = 100;
		}
	}
	else if (_state == ISAACSTATE_DIE)
	{
		die();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_playerUI->getBombUI().size() <= 0) return;
		_item->bombSet(_body.x, _body.y);
		_item->getBomb()[_item->getBomb().size() - 1].bomb->isInstall(true);
		_playerUI->decreaseBomb();
	}
	_baseBullet->update();
	bulletCollision();
	enemyCollision();
	if (_familiarOn)
	{
		_familiar->update();
		_familiar->move(_body.x, (_body.y + _head.y) / 2,_body.currentSpeed);
	}
	_shadow->update(_body.rc.left + 5, _body.rc.top + 30);
}

void player::render(void)
{
	_shadow->render();
	_baseBullet->render();
	if (_familiarOn)
	{
		_familiar->render();
	}
	draw();
	_playerUI->render();
	EFFECTMANAGER->render();

}

void player::draw(void)
{
	switch (_state)
	{
	case ISAACSTATE_NONE:
		
		_body.img->frameRender(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), _body.rc.top - CAMERAMANAGER->getY(), _body.currentX, _body.currentY);
		_head.img->frameRender(getMemDC(), _head.rc.left - CAMERAMANAGER->getX(), _head.rc.top - CAMERAMANAGER->getY(), _head.currentX, _head.currentY);
		break;
	case ISAACSTATE_HIT:
		IMAGEMANAGER->findImage("playerHit")->alphaRender(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), (_body.rc.top + _head.rc.top) / 2 - CAMERAMANAGER->getY(), _alpha);
		break;
	case ISAACSTATE_ITEMGET:
		IMAGEMANAGER->findImage("itemGet")->render(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), (_body.rc.top + _head.rc.top) / 2 - CAMERAMANAGER->getY());
		break;
	case ISAACSTATE_DIE:
		IMAGEMANAGER->findImage("playerDie")->render(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), _body.rc.top - CAMERAMANAGER->getY());
		_ghost.img->frameRender(getMemDC(), _ghost.rc.left - CAMERAMANAGER->getX(), _ghost.rc.top - CAMERAMANAGER->getY(), _ghost.currentX, 0);
		break;
	case ISAACSTATE_BUFF:
		IMAGEMANAGER->findImage("playerBuff")->render(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), (_body.rc.top + _head.rc.top) / 2 - CAMERAMANAGER->getY());
		break;
	case ISAACSTATE_DEBUFF:
		IMAGEMANAGER->findImage("playerDebuff")->render(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), (_body.rc.top + _head.rc.top) / 2 - CAMERAMANAGER->getY());
		break;
	case ISAACSTATE_MAPMOVE:
		IMAGEMANAGER->findImage("mapMove")->frameRender(getMemDC(), _body.rc.left - CAMERAMANAGER->getX(), (_body.rc.top + _head.rc.top) / 2 - CAMERAMANAGER->getY(), _body.currentX, 0);
		break;
	}
}

void player::move(void)
{
	playerSpeed();
	playerBodyFrame();
	if (KEYMANAGER->isStayKeyDown('A') && _state != ISAACSTATE_MAPMOVE)
	{
		objectCollision();
		_body.isMove = true;
		_body.x -= _body.currentSpeed;
		_body.bodyState = BODYSTATE_LEFT;
		_head.headState = HEADSTATE_LEFT;
		_body.currentY = 2;
		_head.currentY = 3;
		if (_body.rc.left < 100 + CAMERAMANAGER->getX())
		{
			_body.rc.left = 100 + CAMERAMANAGER->getX();
			_body.rc.right = _body.rc.left + _body.img->getFrameWidth();
			_body.x = _body.rc.left + (_body.rc.right - _body.rc.left) / 2;
		}
		doorCollision();
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_LEFT);
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_head.currentY = 0;
		_body.isMove = false;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}

	if (KEYMANAGER->isStayKeyDown('D') && _state != ISAACSTATE_MAPMOVE)
	{
		_body.isMove = true;
		objectCollision();
		_body.x += _body.currentSpeed;
		_body.bodyState = BODYSTATE_RIGHT;
		_head.headState = HEADSTATE_RIGHT;
		_body.currentY = 1;
		_head.currentY = 1;
		if (_body.rc.right > CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() - 100)
		{
			_body.rc.right = CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() - 100;
			_body.rc.left = _body.rc.right - _body.img->getFrameWidth();
			_body.x = _body.rc.left + (_body.rc.right - _body.rc.left) / 2;
		}
		doorCollision();
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_RIGHT);
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_head.currentY = 0;
		_body.isMove = false;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	if (KEYMANAGER->isStayKeyDown('W') && _state != ISAACSTATE_MAPMOVE)
	{
		_body.isMove = true;
		objectCollision();
		_body.y -= _body.currentSpeed;
		_body.bodyState = BODYSTATE_UP;
		_head.headState = HEADSTATE_UP;
		_body.currentY = 0;
		_head.currentY = 2;
		if (_body.rc.top  < 80 + CAMERAMANAGER->getY())
		{
			_body.rc.top = 80 + CAMERAMANAGER->getY();
			_body.rc.bottom = _body.rc.top + _body.img->getFrameHeight();
			_body.y = _body.rc.top + (_body.rc.bottom - _body.rc.top) / 2;
		}
		doorCollision();
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_UP);
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_head.currentY = 0;
		_body.isMove = false;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	if (KEYMANAGER->isStayKeyDown('S') && _state != ISAACSTATE_MAPMOVE)
	{
		_body.isMove = true;
		objectCollision();
		_body.y += _body.currentSpeed;
		_body.bodyState = BODYSTATE_DOWN;
		_head.headState = HEADSTATE_DOWN;
		_body.currentY = 0;
		_head.currentY = 0;
		if (_body.rc.bottom > CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY() - 130)
		{
			_body.rc.bottom = CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY() - 130;
			_body.rc.top = _body.rc.bottom - _body.img->getFrameHeight();
			_body.y = _body.rc.top + (_body.rc.bottom - _body.rc.top) / 2;
		}
		doorCollision();
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_head.currentY = 0;
		_body.isMove = false;
	}
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.img->getFrameWidth(), _body.img->getFrameHeight() / 2);
	_head.x = _body.x;
	_head.y = _body.y - _body.img->getFrameHeight() / 2 + 13;
	_head.rc = RectMakeCenter(_head.x , _head.y, _head.img->getFrameWidth(), _head.img->getFrameHeight());
}


void player::fire(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		
		_baseBullet->fire(_head.x, _head.y, 5.0f, BULLETDIRECTION_UP, _ouijaboardOn);
		_head.currentY = 2;
		_head.headState = HEADSTATE_UP;
		playerHeadFrame();
		if (_familiarOn)
		{
			_familiar->setFamilarState(FAMILIARSTATE_UP);
			_familiar->fire();
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_baseBullet->fire(_head.x, _head.y, 5.0f, BULLETDIRECTION_DOWN, _ouijaboardOn);
		_head.currentY = 0;
		_head.headState = HEADSTATE_DOWN;
		playerHeadFrame();
		if (_familiarOn)
		{
			_familiar->setFamilarState(FAMILIARSTATE_DOWN);
			_familiar->fire();
		}
	}
	
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_baseBullet->fire(_head.x, _head.y, 5.0f, BULLETDIRECTION_LEFT, _ouijaboardOn);
		_head.currentY = 3;
		_head.headState = HEADSTATE_LEFT;
		playerHeadFrame();
		if (_familiarOn)
		{
			_familiar->setFamilarState(FAMILIARSTATE_LEFT);
			_familiar->fire();
		}
	}
	
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_baseBullet->fire(_head.x, _head.y, 5.0f, BULLETDIRECTION_RIGHT, _ouijaboardOn);
		_head.currentY = 1;
		_head.headState = HEADSTATE_RIGHT;
		playerHeadFrame();
		if (_familiarOn)
		{
			_familiar->setFamilarState(FAMILIARSTATE_RIGHT);
			_familiar->fire();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP) && _head.currentX == 1)
	{
		_head.currentX = 0;
		_head.currentY = 0;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _head.currentX == 1)
	{
		_head.currentX = 0;
		_head.currentY = 0;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _head.currentX == 1)
	{
		_head.currentX = 0;
		_head.currentY = 0;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _head.currentX == 1)
	{
		_head.currentX = 0;
		_head.currentY = 0;
		if (_familiarOn) _familiar->setFamilarState(FAMILIARSTATE_DOWN);
	}
}

void player::playerSpeed(void)
{
	
	if (_body.currentSpeed < _body.maxSpeed && _body.isMove)
	{
		if (_body.isSlow) _body.currentSpeed += 0.01f;
		else _body.currentSpeed += 0.1f;
	}
	if (_body.currentSpeed > 0.1 && !_body.isMove)
	{
		 _body.currentSpeed -= 0.4f;
		
		switch (_body.bodyState)
		{
		case BODYSTATE_UP:
			_body.y -= _body.currentSpeed;
			break;
		case BODYSTATE_DOWN:
			_body.y += _body.currentSpeed;
			break;
		case BODYSTATE_LEFT:
			_body.x -= _body.currentSpeed;
			break;
		case BODYSTATE_RIGHT:
			_body.x += _body.currentSpeed;
			break;
		}
	}
}

void player::playerBodyFrame(void)
{
	if (_body.isMove)
	{
		if (_body.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_body.count = TIMEMANAGER->getWorldTime();
			_body.currentX++;
			if (_body.currentX == _body.img->getMaxFrameX())
			{
				_body.currentX = 0;
			}
		}
	}
	else
	{
		if (_state == ISAACSTATE_MAPMOVE)
		{
			if (_flightTime > 0)
			{
				_flightTime--;
				_body.currentX = 0;
			}
			if (_body.count + FRAMECOUNT < TIMEMANAGER->getWorldTime() && _flightTime <= 0)
			{
				_body.count = TIMEMANAGER->getWorldTime();
				_body.currentX++;
				if (_body.currentX > 2)
				{
					_body.currentX = 2;
				}
			}
			if (_body.currentX == 2)
			{
				_mapMoveDistance--;
				_body.y += 10;
				if (_mapMoveDistance < 0)
				{
					MoveWindow(_hWnd, WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, true);
					SCENEMANAGER->changeScene("메뉴");
				}
			}
		}
		else
		{
			_body.currentX = 2;
			_body.currentY = 0;
		}
	}
}

void player::playerHeadFrame(void)
{
	if (_baseBullet->getIsFire())
	{
		if (_head.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
		{
			_head.count = TIMEMANAGER->getWorldTime() + 0.15f;
			if (_head.currentX == 1)
			{
				_head.currentX = 0;
			}
			else if (_head.currentX == 0)
			{
				_head.currentX = 1;
			}
		}
	}
}

void player::playerHit(void)
{
	if (_alphaCount == 200)
	{
		SOUNDMANAGER->play("isaac hit", VOLUME->getSfxVolume() / 10);
		_body.currentHp--;
		_state = ISAACSTATE_HIT;
		_playerUI->decreaseHp();
		_ghost.x = _body.x;
		_ghost.y = _body.y - 50;
	}
	_alphaCount--;
	if (_alpha <= 100)
	{
		_isAlphaValueIncrease = true;
	}
	else if (_alpha >= 255)
	{
		_isAlphaValueIncrease = false;
	}
	if (_isAlphaValueIncrease)
	{
		_alpha+=20;
	}
	else
	{
		_alpha-=20;
	}
	if (_alphaCount < 0)
	{
		_state = ISAACSTATE_NONE;
		_alphaCount = 200;
		_alpha = 255;
		SOUNDMANAGER->stop("isaac hit");
	}
	if (_body.currentHp <= 0)
	{
		_state = ISAACSTATE_DIE;
	}
}

void player::coinGetUsing(bool isUsing,int size)
{
	if (isUsing)
	{
		if (_playerUI->getCoinUI().size() < size) return;
		for (int i = 0; i < size; i++)
		{
			_playerUI->decreaseCoin();
		}
	}
	else
	{
		SOUNDMANAGER->play("coin pickup", VOLUME->getSfxVolume() / 10);
		_playerUI->increaseCoin();
	}
}

void player::bombGetUsing(bool isUsing)
{
	if (isUsing)
	{
		_playerUI->decreaseBomb();
	}
	else
	{
		SOUNDMANAGER->play("bomb pickup", VOLUME->getSfxVolume() / 10);
		_playerUI->increaseBomb();
	}
}

void player::healthPointIncrease()
{
	if(_body.currentHp == _body.maxHp - 1) _body.currentHp ++;
	else _body.currentHp += 2;
	_playerUI->increaseHp();
	SOUNDMANAGER->play("hp up", VOLUME->getSfxVolume() / 10);
}

void player::keyGetUsing(bool isUsing)
{
	if (isUsing)
	{
		_playerUI->decreaseKey();
	}
	else
	{
		SOUNDMANAGER->play("key pickup", VOLUME->getSfxVolume() / 10);
		_playerUI->increaseKey();
	}
}

void player::tileSetUp(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map->getTiles()[i].rc.left > -TILESIZE + CAMERAMANAGER->getX() && _map->getTiles()[i].rc.right < CAMERAMANAGER->getGameMaxRenderX() + CAMERAMANAGER->getX() &&
			_map->getTiles()[i].rc.top >-TILESIZE + CAMERAMANAGER->getY() && _map->getTiles()[i].rc.bottom < CAMERAMANAGER->getGameMaxRenderY() + CAMERAMANAGER->getY())
		{
			tileVec.push_back(_map->getTiles()[i]);
			attributeVec.push_back(_map->getAttribute()[i]);
		}
	}
}

void player::atkChange(bool isUp)
{
	if (isUp) _body.atk += 0.5f;
	else _body.atk -= 0.5f;
}

void player::speedChanage(bool isUp)
{
	if (isUp) _body.maxSpeed += 0.5f;
	else _body.maxSpeed -= 0.5f;
}

void player::die(void)
{
	if (_ghost.count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
	{
		_ghost.count = TIMEMANAGER->getWorldTime();
		_ghost.currentX++;
		if (_ghost.currentX > _ghost.img->getMaxFrameX())
		{
			_ghost.currentX = 0;
		}
	}
	_ghost.y -= _ghost.speed;
	if (_ghost.distnace == 150) SOUNDMANAGER->play("isaac dies", VOLUME->getSfxVolume() / 10);
	_ghost.distnace--;
	_ghost.rc = RectMakeCenter(_ghost.x, _ghost.y, _ghost.img->getFrameWidth(), _ghost.img->getFrameHeight());
	if (_ghost.distnace < 0)
	{
		SOUNDMANAGER->stop("basement");
		MoveWindow(_hWnd, WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, true);
		SCENEMANAGER->changeScene("메뉴");
	}
}
