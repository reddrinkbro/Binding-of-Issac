#pragma once
#include "singletonBase.h"
#include "image.h"

/*STL ���� �ٽ�*/
//Ű, �� �� ���� ����
//ù��° first -> Ű
//�ι�° second -> ��
//�߰��ϴ� ����� insert�� ����ϰ� Ű�� ��� �ΰ��� ���ÿ� �߰��ؾ� �ϴ� 
//pair�� make_pair�� ����Ͽ� �߰��ϸ� �ȴ�

class imageManager : public singletonBase<imageManager>
{
private:
	//������ ���� �̹������
	typedef map<string, image*> mapImageList;
	//������ ���� �̹�������� �ݺ���
	typedef map<string, image*>::iterator mapImageIter;

private:
	//���� �̹���Ŭ������ ���� ��
	mapImageList _mImageList;

public:
	//�̹����Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹����Ŵ��� ����
	void release(void);

	//�� ��Ʈ������ �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//�̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll();

	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���� ���� (���� ������ ��ǥ�� ���İ��� �Բ� �̹��� ����Ѵ�)
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//������ ���� 
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//��������	
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	
	imageManager() {}
	~imageManager() {}
};

