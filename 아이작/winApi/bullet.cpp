#include "stdafx.h"
#include "bullet.h"

HRESULT playerBaseBullet::init(float range, float maxCooldDownTime)
{
	_range = range;
	_cooldDownTime = maxCooldDownTime;
	_maxCooldDownTime = maxCooldDownTime;
	_isFire = false;
	//ÀÌÆåÆ® Ãß°¡
	EFFECTMANAGER->addEffect("baseBulletEffect", "image/effect/baseBulletEffect.bmp", 1704, 107, 106, 107, 14, 3);
	EFFECTMANAGER->addEffect("pukeBulletEffect", "image/effect/pukeBulletEffect.bmp", 768, 64, 64, 64, 14, 3);
	return S_OK;
}

void playerBaseBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void playerBaseBullet::update(void)
{
	if (_isFire)
	{
		_cooldDownTime--;
		if (_cooldDownTime < 0)
		{
			_isFire = false;
			_cooldDownTime = _maxCooldDownTime;
			SOUNDMANAGER->stop("tear fire");
		}
	}
	move();
	EFFECTMANAGER->update();
}

void playerBaseBullet::render(void)
{
	draw();
	EFFECTMANAGER->render();
}

void playerBaseBullet::fire(float x, float y, float speed, BULLETDIRECTION _direction, int itemOn)
{
	if (_isFire) return;
	_itemOn = itemOn;
	tagBullet _bullet;
	ZeroMemory(&_bullet, sizeof(tagBullet));
	if(!_itemOn)	_bullet.img = IMAGEMANAGER->addImage("baseBullet", "image/character/baseBullet.bmp", 25, 25, true, RGB(255, 0, 255));
	else _bullet.img = IMAGEMANAGER->addImage("pukeBullet", "image/character/pukeBullet.bmp", 25, 25, true, RGB(255, 0, 255));
	_bullet.x = _bullet.fireX = x;
	_bullet.y = _bullet.fireY = y;
	_bullet.diretion = _direction;
	_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
	_bullet.speed = speed;
	_bullet.shadow = new shadow;
	_bullet.shadow->init(SHADOWSIZE_SMALL);
	_bullet.shadowDistance = 30.0f;
	_vBullet.push_back(_bullet);
	_isFire = true;
	SOUNDMANAGER->play("tear fire", VOLUME->getSfxVolume() / 10);
}

void playerBaseBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(),_viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top- CAMERAMANAGER->getY());
	}
}

void playerBaseBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->diretion == BULLETDIRECTION_UP)
		{
			_viBullet->y -= _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_DOWN)
		{
			_viBullet->y += _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_LEFT)
		{
			if (getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _range - 50)
			{
				_viBullet->y += _viBullet->speed / 2;
				_viBullet->shadowDistance -= 2.6f;
			}
			_viBullet->x -= _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_RIGHT)
		{
			if (getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _range - 50)
			{
				_viBullet->y += _viBullet->speed / 2;
				_viBullet->shadowDistance -=2.6f;
			}
			_viBullet->x += _viBullet->speed;
		}
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			if (!_itemOn) EFFECTMANAGER->play("baseBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			else EFFECTMANAGER->play("pukeBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void playerBaseBullet::removeBullet(int arrNum)
{
	if (!_itemOn) EFFECTMANAGER->play("baseBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	else EFFECTMANAGER->play("pukeBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT clottyBullet::init(float range)
{
	_range = range;
	EFFECTMANAGER->addEffect("redBulletEffect", "image/effect/redBulletEffect.bmp", 1712, 107, 107, 107, 14, 3);
	return S_OK;
}

void clottyBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void clottyBullet::update(void)
{
	move();
}

void clottyBullet::render(void)
{
	draw();
}

void clottyBullet::fire(float x, float y, float speed)
{
	if (!_vBullet.empty()) return;

	for (int i = 0; i < 4; i++)
	{
		tagBullet _bullet;
		ZeroMemory(&_bullet, sizeof(tagBullet));
		_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
		_bullet.x = _bullet.fireX = x;
		_bullet.y = _bullet.fireY = y;
		_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
		_bullet.speed = speed;
		_bullet.angle = 0;
		if (i == 0) _bullet.diretion = BULLETDIRECTION_UP;
		else if(i == 1) _bullet.diretion = BULLETDIRECTION_DOWN;
		else if (i == 2) _bullet.diretion = BULLETDIRECTION_LEFT;
		else _bullet.diretion = BULLETDIRECTION_RIGHT;
		_bullet.shadow = new shadow;
		_bullet.shadow->init(SHADOWSIZE_SMALL);
		_bullet.shadowDistance = 30.0f;
		_vBullet.push_back(_bullet);
	}
}

void clottyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
	}
}

void clottyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (64 < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			if (_viBullet->angle < PI / 2 || _viBullet->angle >PI + PI / 2)	_viBullet->angle -= 0.007f;
			else _viBullet->angle += 0.007f;
			_viBullet->shadowDistance -= 0.2f;
		}
		else
		{
			if (_viBullet->angle < PI / 2 || _viBullet->angle >PI + PI / 2)	_viBullet->angle += 0.007f;
			else _viBullet->angle -= 0.007f;

		}
		if (_viBullet->diretion == BULLETDIRECTION_UP)
		{
			_viBullet->y +=  _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_DOWN)
		{
			_viBullet->y -=  _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_LEFT)
		{
			_viBullet->x += cosf(_viBullet->angle + PI) * _viBullet->speed;
			_viBullet->y += sinf(_viBullet->angle + PI) * _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_RIGHT)
		{
			_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle)*_viBullet->speed;
		}
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void clottyBullet::removeBullet(int arrNum)
{

	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT horfBullet::init(void)
{
	EFFECTMANAGER->addEffect("redBulletEffect", "image/effect/redBulletEffect.bmp", 1712, 107, 107, 107, 14, 3);
	return S_OK;
}

void horfBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void horfBullet::update(void)
{
	move();
}

void horfBullet::render(void)
{
	draw();
}

void horfBullet::fire(float x, float y, float playerX, float playerY, float speed)
{
	if (_vBullet.size() > 0)return;

	tagBullet _bullet;
	ZeroMemory(&_bullet, sizeof(tagBullet));
	_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
	_bullet.x = _bullet.fireX = x;
	_bullet.y = _bullet.fireY = y;
	_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
	_bullet.speed = speed;
	_bullet.angle = getAngle(_bullet.x, _bullet.y, playerX, playerY);
	_range = getDistance(_bullet.x, _bullet.y, playerX, playerY);
	_bullet.shadow = new shadow;
	_bullet.shadow->init(SHADOWSIZE_SMALL);
	_bullet.shadowDistance = 30.0f;
	_vBullet.push_back(_bullet);

}

void horfBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
	}
}

void horfBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (64 < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) )
		{
			if(_viBullet->angle < PI/2 || _viBullet->angle >PI + PI/2)	_viBullet->angle -= 0.007f;
			else _viBullet->angle += 0.007f;
			_viBullet->shadowDistance -= 0.2f;
		}
		else
		{
			if (_viBullet->angle < PI / 2 || _viBullet->angle >PI + PI / 2)	_viBullet->angle += 0.007f;
			else _viBullet->angle -= 0.007f;

		}

		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) *_viBullet->speed;
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void horfBullet::removeBullet(int arrNum)
{
	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT sixWayBullet::init(float range)
{
	EFFECTMANAGER->addEffect("redBulletEffect", "image/effect/redBulletEffect.bmp", 1712, 107, 107, 107, 14, 3);
	_range = range;
	return S_OK;
}

void sixWayBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void sixWayBullet::update(void)
{
	move();
}

void sixWayBullet::render(void)
{
	draw();
}

void sixWayBullet::fire(float x, float y, float speed)
{
	if (!_vBullet.empty()) return;

	for (int i = 0; i < 6; i++)
	{
		tagBullet _bullet;
		ZeroMemory(&_bullet, sizeof(tagBullet));
		_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
		_bullet.x = _bullet.fireX = x;
		_bullet.y = _bullet.fireY = y;
		_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
		_bullet.speed = speed;
		_bullet.angle = PI / 3 * i;
		_bullet.shadow = new shadow;
		_bullet.shadow->init(SHADOWSIZE_SMALL);
		_bullet.shadowDistance = 30.0f;
		_vBullet.push_back(_bullet);
	}
}

void sixWayBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
	}
}

void sixWayBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void sixWayBullet::removeBullet(int arrNum)
{
	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT blubberBullet::init(float range)
{
	_range = range;
	return S_OK;
}

void blubberBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void blubberBullet::update(void)
{
	move();
}

void blubberBullet::render(void)
{
	draw();
}

void blubberBullet::fire(float x, float y, float speed)
{
	if (!_vBullet.empty()) return;

	for (int i = 0; i < 3; i++)
	{
		int randomValuve = RND->getInt(2);
		tagBullet _bullet;
		ZeroMemory(&_bullet, sizeof(tagBullet));
		_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
		_bullet.x = _bullet.fireX = x;
		_bullet.y = _bullet.fireY = y;
		_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
		_bullet.speed = RND->getFromFloatTo(speed, speed + 2.0f);
		_bullet.gravity = -2.0f;
		if (randomValuve == 0) _bullet.diretion = BULLETDIRECTION_LEFT;
		else _bullet.diretion = BULLETDIRECTION_RIGHT;
		_bullet.angle = RND->getFromFloatTo(0, PI);
		_bullet.shadow = new shadow;
		_bullet.shadow->init(SHADOWSIZE_SMALL);
		_bullet.shadowDistance = 30.0f;
		_vBullet.push_back(_bullet);
	}
}

void blubberBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
	}
}

void blubberBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->gravity += 0.09f;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed - _viBullet->gravity ;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void blubberBullet::removeBullet(int arrNum)
{
	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT familiarBullet::init(float range)
{
	_range = range;
	return S_OK;
}

void familiarBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void familiarBullet::update(void)
{
	move();
}

void familiarBullet::render(void)
{
	draw();
}

void familiarBullet::fire(float x, float y, float speed, BULLETDIRECTION _direction)
{
	if (!_vBullet.empty()) return;
	
	tagBullet _bullet;
	ZeroMemory(&_bullet, sizeof(tagBullet));
	_bullet.img = IMAGEMANAGER->addImage("pukeBulletSmall", "image/character/pukeBulletSmall.bmp", 20, 20, true, RGB(255, 0, 255));
	_bullet.x = _bullet.fireX = x;
	_bullet.y = _bullet.fireY = y;
	_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
	_bullet.diretion = _direction;
	_bullet.speed = speed;
	_bullet.shadow = new shadow;
	_bullet.shadow->init(SHADOWSIZE_SMALL);
	_bullet.shadowDistance = 30.0f;
	_vBullet.push_back(_bullet);
	
}

void familiarBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
	}
}

void familiarBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->diretion == BULLETDIRECTION_UP)
		{
			_viBullet->y -= _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_DOWN)
		{
			_viBullet->y += _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_LEFT)
		{
			_viBullet->x -= _viBullet->speed;
		}
		else if (_viBullet->diretion == BULLETDIRECTION_RIGHT)
		{
			_viBullet->x +=  _viBullet->speed;
			
		}
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_range)
		{
			EFFECTMANAGER->play("pukeBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void familiarBullet::removeBullet(int arrNum)
{
	EFFECTMANAGER->play("pukeBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT monstroBullet::init(void)
{
	EFFECTMANAGER->addEffect("redBulletEffect", "image/effect/redBulletEffect.bmp", 1712, 107, 107, 107, 14, 3);
	return S_OK;
}

void monstroBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void monstroBullet::update(void)
{
	move();
}

void monstroBullet::render(void)
{
	draw();
}

void monstroBullet::fire(float x, float y, float angle , int bulletMax, bool isJump)
{
	if (!_vBullet.empty()) return;
	
	if (!isJump)
	{
		for (int i = 0; i < bulletMax; i++)
		{
			tagBullet _bullet;
			ZeroMemory(&_bullet, sizeof(tagBullet));
			_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
			_bullet.x = _bullet.fireX = x;
			_bullet.y = _bullet.fireY = y;
			_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
			_bullet.speed = RND->getFromFloatTo(3.0f, 4.0f);
			_bullet.angle = RND->getFromFloatTo(angle - PI / 4, angle + PI / 4);
			_bullet.range = RND->getFromFloatTo(200, 300);
			_bullet.gravity = -2.0f;
			_bullet.shadow = new shadow;
			_bullet.shadow->init(SHADOWSIZE_SMALL);
			_bullet.shadowDistance = 30.0f;
			_vBullet.push_back(_bullet);
		}
	}
	else
	{
		for (int i = 0; i < bulletMax; i++)
		{
			tagBullet _bullet;
			ZeroMemory(&_bullet, sizeof(tagBullet));
			_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
			_bullet.x = _bullet.fireX = x;
			_bullet.y = _bullet.fireY = y;
			_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
			_bullet.speed = RND->getFromFloatTo(3.0f, 4.0f);
			_bullet.angle = 2 * PI / bulletMax * i;
			_bullet.range = RND->getFromFloatTo(200, 300);
			_bullet.gravity = -2.0f;
			_bullet.shadow = new shadow;
			_bullet.shadow->init(SHADOWSIZE_SMALL);
			_bullet.shadowDistance = 30.0f;
			_vBullet.push_back(_bullet);
		}
	}
}

void monstroBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
		_viBullet->shadow->render();
	}
}

void monstroBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->gravity += 0.01f;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed - _viBullet->gravity;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_viBullet->range)
		{
			EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void monstroBullet::removeBullet(int arrNum)
{
	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT megamawBullet::init(void)
{
	EFFECTMANAGER->addEffect("redBulletEffect", "image/effect/redBulletEffect.bmp", 1712, 107, 107, 107, 14, 9);
	EFFECTMANAGER->addEffect("megamawBulletEffect", "image/enemy/effect/megamawBulletEffect.bmp", 2890, 172, 192, 172, 14, 10);
	_count = 0.0f;
	_addAngle = 0.0f;
	_bulletNum = 0;
	return S_OK;
}

void megamawBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
		SAFE_DELETE(_viBullet->shadow);
	}

	_vBullet.clear();
}

void megamawBullet::update(void)
{
	move();
}

void megamawBullet::render(void)
{
	draw();
}

void megamawBullet::fire(float x, float y, float angle, int bulletMax, int range, int pattern)
{
	if (!_vBullet.empty()) return;
	_pattern = pattern;
	_currentX = 0;
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet _bullet;
		ZeroMemory(&_bullet, sizeof(tagBullet));
		if (_pattern == 0)
		{
			_bullet.img = IMAGEMANAGER->addImage("redBullet", "image/character/redBullet.bmp", 25, 25, true, RGB(255, 0, 255));
			_bullet.angle = RND->getFromFloatTo(angle - PI / 36, angle + PI / 36);
			_bullet.speed = RND->getFromFloatTo(3.0f, 4.0f);
			_bullet.range = RND->getFromFloatTo(range - 100, range - 50);
		}
		else
		{
			_bullet.img = IMAGEMANAGER->addFrameImage("megamawBullet", "image/enemy/boss/megamawBullet.bmp", 680, 100, 6, 1, true, RGB(255, 0, 255));
			if (_pattern == 2)
			{
				_bullet.angle = 2 * PI / (bulletMax / 2) * i;
				if (i < bulletMax / 2)
				{
					_bullet.diretion = BULLETDIRECTION_LEFT;
					_bullet.range = 175;
				}
				else
				{
					_bullet.diretion = BULLETDIRECTION_RIGHT;
					_bullet.range = 350;
				}
			}
			else
			{
				_bullet.angle = 2 * PI / bulletMax * i;
				_bullet.range = 350;
			}
			_bullet.speed = 6.2f;
		}
		_bullet.x = _bullet.fireX = x;
		_bullet.y = _bullet.fireY = y;
		_bullet.rc = RectMakeCenter(_bullet.x, _bullet.y, _bullet.img->getWidth(), _bullet.img->getHeight());
		_bullet.shadow = new shadow;
		_bullet.shadow->init(SHADOWSIZE_SMALL);
		_bullet.shadowDistance = 30.0f;
		_vBullet.push_back(_bullet);
	}
}

void megamawBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->shadow->render();
		if(_pattern == 0) _viBullet->img->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY());
		else _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getX(), _viBullet->rc.top - CAMERAMANAGER->getY(), _currentX, 0);
	}
}

void megamawBullet::move(void)
{
	_addAngle += 0.035f;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _bulletNum++)
	{
		if (_pattern != 0)
		{
			_currentX++;
			if (_count + FRAMECOUNT < TIMEMANAGER->getWorldTime())
			{
				_count = TIMEMANAGER->getWorldTime();
				_currentX++;
				if (_currentX > 5)
				{
					_currentX = 0;
				}
			}
		}
		if (_pattern == 0)
		{
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getWidth(), _viBullet->img->getHeight());
		}
		else
		{
			if (_pattern == 1)
			{
				_viBullet->x += cosf(_viBullet->angle + _addAngle) * _viBullet->speed;
				_viBullet->y -= sinf(_viBullet->angle + _addAngle) * _viBullet->speed;
			}
			else if (_pattern == 2)
			{
				if (_viBullet->diretion == BULLETDIRECTION_LEFT)
				{
					_viBullet->x -= cosf(_viBullet->angle + _addAngle) * _viBullet->speed / 2;
					_viBullet->y -= sinf(_viBullet->angle + _addAngle) * _viBullet->speed / 2;
				}
				else
				{
					_viBullet->x += cosf(_viBullet->angle + _addAngle) * _viBullet->speed;
					_viBullet->y -= sinf(_viBullet->angle + _addAngle) * _viBullet->speed;
				}
				
			}
			else if (_pattern == 3)
			{
				_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
				_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;
			}
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		}
		_viBullet->shadow->update(_viBullet->x - 20, _viBullet->y + _viBullet->shadowDistance);
		_viBullet->distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_viBullet->distance >_viBullet->range)
		{
			if(_pattern == 0) EFFECTMANAGER->play("redBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			else EFFECTMANAGER->play("megamawBulletEffect", _viBullet->x - CAMERAMANAGER->getX(), _viBullet->y - CAMERAMANAGER->getY());
			_viBullet = _vBullet.erase(_viBullet);
			_bulletNum = 0;
		}
		else
		{
			++_viBullet;
			_bulletNum ++;
			if (_viBullet == _vBullet.end() - 1)
			{
				_bulletNum = 0;
			}
		}
		
	}
}

void megamawBullet::removeBullet(int arrNum)
{
	if(_pattern == 0)	EFFECTMANAGER->play("redBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	else EFFECTMANAGER->play("megamawBulletEffect", _vBullet[arrNum].x - CAMERAMANAGER->getX(), _vBullet[arrNum].y - CAMERAMANAGER->getY());
	_vBullet.erase(_vBullet.begin() + arrNum);
}
