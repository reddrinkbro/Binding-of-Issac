#pragma once

class animation;

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ��� �ε� (������)
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//���ҽ� ID
		HDC			hMemDC;			//�޸� DC
		HBITMAP		hBit;			//��Ʈ��
		HBITMAP		hOBit;			//�õ��Ʈ��
		float		x;				//�̹��� x��ǥ(����Ʈ)
		float		y;				//�̹��� y��ǥ(ž)
		int			width;			//�̹��� ����ũ��
		int			height;			//�̹��� ����ũ��
		int			currentFrameX;	//���������� x��ǥ
		int			currentFrameY;	//���������� y��ǥ
		int			maxFrameX;		//�ִ������� x����
		int			maxFrameY;		//�ִ������� y����
		int			frameWidth;		//1������ ����ũ��
		int			frameHeight;	//1������ ����ũ��
		BYTE		loadType;		//�̹��� �ε�Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;
	typedef struct tagGDI
	{
		HDC			hMemDC;				//�޸� DC
		HBITMAP		hBit;				//��Ʈ��
		HBITMAP		hOBit;				//�õ��Ʈ��
		float		x;					//�̹��� x��ǥ(����Ʈ)
		float		y;					//�̹��� y��ǥ(ž)
		int			width;				//�̹��� ����ũ��
		int			height;				//�̹��� ����ũ��
		int			currentFrameX;		//���������� x��ǥ
		int			currentFrameY;		//���������� y��ǥ
		int			maxFrameX;			//�ִ������� x����
		int			maxFrameY;			//�ִ������� y����
		int			frameWidth;			//1������ ����ũ��
		int			frameHeight;		//1������ ����ũ��

										// �߰� ( 2017 06 03  �ѻ� )
		int finalWidth; // �̹��� ���� ���� ũ��
		int finalHeight; // �̹��� ���� ���� ũ��
		int finalAngle; // �̹��� ���� ���� 
		int finalCenterX; // �̹��� ���� ������ x ��ǥ
		int finalCenterY; // �̹��� ���� ������ y ��ǥ
		RECT finalRect; // �ޱ� 0 �� �� ��Ʈ �浹��

		tagGDI()
		{
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}GDI_INFO, *LPGDI_INFO;

private:
	LPGDI_INFO		_gdiInfo;		//GDI����
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸�
	BOOL			_isTrans;		//���� ���ٰ���
	COLORREF		_transColor;	//���� ���� RGB�� (����Ÿ = RGB(255, 0, 255))

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ���
	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���

	Graphics*		_gdi;
	Graphics*		_gdiRender;
	Image*			_gdiImg;
public:
	image();
	~image();

	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ��� �ʱ�ȭ(������)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ(�� ���)
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
		
	//���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	//���� �÷�Ű ���� (���� ��������?, �����)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//����
	void release(void);
	
	//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���� ���� (���� ������ ��ǥ�� ���İ��� �Բ� �̹��� ����Ѵ�)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//������ ���� 
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	
	
	//��������
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	
	//�ִϷ���
	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//==================
	//	## �ζ����Լ� ## 
	//==================

	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� x��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//�̹��� ����, ����ũ��
	inline int getWidth(void) { return _imageInfo->width; }
 	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ���ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}

	//�ٿ���ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//������ X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//�̹��� 1������ ����, ����ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ִ������� x, y����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
};

