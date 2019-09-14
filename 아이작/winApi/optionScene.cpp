#include "stdafx.h"
#include "optionScene.h"

HRESULT optionScene::init(void)
{
	_image = IMAGEMANAGER->addImage("optionWindow", "image/UI/optionWindow.bmp", WINSIZEX, WINSIZEY);
	_option[0].img = IMAGEMANAGER->addImage("sfx", "image/UI/sfx.bmp", 70, 36, true, RGB(255, 0, 255));
	_option[1].img = IMAGEMANAGER->addImage("music", "image/UI/music.bmp", 94, 28, true, RGB(255, 0, 255));
	_option[2].img = IMAGEMANAGER->addImage("resumeMenu", "image/UI/resumeMenu.bmp", 268, 43, true, RGB(255, 0, 255));
	for (int i = 0; i < 2; i++)
	{
		_option[i].x = WINSIZEX / 2 + i * 40 - 100;
		_option[i].y = WINSIZEY / 2 - 150 + i * 175;
		_option[i].rc = RectMakeCenter(_option[i].x, _option[i].y, _option[i].img->getWidth(), _option[i].img->getHeight());
	}
	_option[2].x = WINSIZEX / 2 + 50;
	_option[2].y = WINSIZEY / 2 + 200;
	_option[2].rc = RectMakeCenter(_option[2].x, _option[2].y, _option[2].img->getWidth(), _option[2].img->getHeight());
	//화살표
	_arrow.img = IMAGEMANAGER->addImage("arrow", "image/UI/arrow.bmp", 24, 30, true, RGB(255, 0, 255));
	_arrow.x = _option[0].rc.left - 20 - _arrow.img->getWidth();
	_arrow.y = _option[0].y + _arrow.img->getHeight() / 2 - 10;
	_arrow.rc = RectMakeCenter(_arrow.x, _arrow.y, _arrow.img->getWidth(), _arrow.img->getHeight());
	_arrow.volumeSelect = 0;
	//볼륨
	for (int i = 0; i < 2; i++)
	{
		_volume[i].img = IMAGEMANAGER->addFrameImage("volume", "image/UI/volume.bmp", 116, 352, 1, 11, true, RGB(255, 0, 255));
		_volume[i].x = _option[i].rc.right + 100 + _arrow.img->getWidth() - 20 * i;
		_volume[i].y = _option[i].y;
		_volume[i].rc = RectMakeCenter(_volume[i].x, _volume[i].y, _volume[i].img->getFrameWidth(), _volume->img->getFrameHeight());
	}
	return S_OK;
}

void optionScene::release(void)
{
}

void optionScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _arrow.volumeSelect != 2)
	{
		_arrow.volumeSelect++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _arrow.volumeSelect != 0)
	{
		_arrow.volumeSelect--;
	}
	volumeSelect();
}

void optionScene::render(void)
{
	_image->render(getMemDC());
	for (int i = 0; i < 3; i++)
	{
		_option[i].img->render(getMemDC(), _option[i].rc.left, _option[i].rc.top);
	}
	_volume[0].img->frameRender(getMemDC(), _volume[0].rc.left, _volume[0].rc.top, 1, VOLUME->getSfxVolume());
	_volume[1].img->frameRender(getMemDC(), _volume[1].rc.left, _volume[1].rc.top, 1, VOLUME->getMusicVolume());
	
	_arrow.img->render(getMemDC(), _arrow.rc.left, _arrow.rc.top);
}

void optionScene::volumeSelect(void)
{
	if (_arrow.volumeSelect == 0)
	{
		_arrow.x = _option[_arrow.volumeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _option[_arrow.volumeSelect].y + _arrow.img->getHeight() / 2 - 10;
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (VOLUME->getSfxVolume() == 0) return;
			VOLUME->setSfxVolume(VOLUME->getSfxVolume() - 1);
			if (SOUNDMANAGER->isPlaySound("tear fire")) SOUNDMANAGER->stop("tear fire");
			SOUNDMANAGER->play("tear fire", VOLUME->getSfxVolume() / 10);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (VOLUME->getSfxVolume() == _volume[_arrow.volumeSelect].img->getMaxFrameY()) return;
			VOLUME->setSfxVolume(VOLUME->getSfxVolume() + 1);
			if (SOUNDMANAGER->isPlaySound("tear fire")) SOUNDMANAGER->stop("tear fire");
			SOUNDMANAGER->play("tear fire", VOLUME->getSfxVolume() / 10);
		}
	}
	else if (_arrow.volumeSelect == 1)
	{
		_arrow.x = _option[_arrow.volumeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _option[_arrow.volumeSelect].y + _arrow.img->getHeight() / 2 - 10;
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (VOLUME->getMusicVolume() == 0) return;
			VOLUME->setMusicVolume(VOLUME->getMusicVolume() - 1);
			SOUNDMANAGER->play("title screen", VOLUME->getMusicVolume() / 10);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (VOLUME->getMusicVolume() == _volume[_arrow.volumeSelect].img->getMaxFrameY()) return;
			VOLUME->setMusicVolume(VOLUME->getMusicVolume() + 1);
			SOUNDMANAGER->play("title screen", VOLUME->getMusicVolume() / 10);
		}
	}
	else if (_arrow.volumeSelect == 2)
	{
		_arrow.x = _option[_arrow.volumeSelect].rc.left - 20 - _arrow.img->getWidth();
		_arrow.y = _option[_arrow.volumeSelect].y + _arrow.img->getHeight() / 2 - 10;
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			this->save();
			SCENEMANAGER->changeScene("메뉴");
		}
	}
	_arrow.rc = RectMakeCenter(_arrow.x, _arrow.y, _arrow.img->getWidth(), _arrow.img->getHeight());
}

void optionScene::save(void)
{
	FILE* file;
	file = fopen("save/sound.txt", "w");
	fprintf(file, "%f, %f", VOLUME->getSfxVolume(), VOLUME->getMusicVolume());
	fclose(file);
}
