#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();
}

//�� ��Ʈ������ �ʱ�ȭ �� �߰�
image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

//�̹��� ���Ϸ� �ʱ�ȭ(�� ���) �� �߰�
image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//������ �̹��� ���Ϸ� �ʱ�ȭ(�� ���) �� �߰�
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//�̹��� Ű������ ã��
image * imageManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}

//�̹��� Ű������ ����
BOOL imageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);
	
		return TRUE;
	}

	return FALSE;
}

//�̹��� ��ü ����
BOOL imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �����
	mapImageIter iter = _mImageList.begin();
	//for(;;) == while(true)
	for (; iter != _mImageList.end();)
	{
		//�̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else //������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
	_mImageList.clear();
	
	return TRUE;
}

//================
//	## �Ϲݷ��� ##
//================
//�̹����� ã�Ƽ� �׳� ���� ��Ű�� ��
void imageManager::render(string strKey, HDC hdc)
{	
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//================
//	## ���ķ��� ##
//================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//=================
//	## �����ӷ��� ##
//=================	
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

//================
//	## �������� ##
//================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}
