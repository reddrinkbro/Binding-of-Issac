#pragma once

class animation 
{
private:
	//������ ����Ʈ
	typedef vector<POINT> _vFrameList;	
	//������ �÷��� ����Ʈ
	typedef vector<int> _vPlayList;	

private:
	int _frameNum;			//������ ��

	_vFrameList _frameList;	//������ ��ġ ����Ʈ
	_vPlayList _playList;	//�÷��� ����Ʈ

	int _frameWidth;		//������ ����ũ��
	int _frameHeight;		//������ ����ũ��

	int _frameNumWidth;		//���� ������ �� ����
	int _frameNumHeight;	//���� ������ �� ����

	BOOL _loop;				//����?
	float _frameUpdateSec;	//�ʴ� ������ ������Ʈ��
	float _elapsedSec;		//�����Ӱ� ������ ������ �ð�

	DWORD _nowPlayIdx;		//���� �÷��� �ε���
	BOOL _isPlay;			//�÷��� ���̳�?
	
public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setDefPlayFrame(BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(int* playArr = NULL, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(int start, int end, BOOL reverse = NULL, BOOL loop = NULL);

	//�ʴ� ������ ���� Ƚ��
	void setFPS(int framePerSec);

	//������ ������Ʈ
	void frameUpdate(float elpasedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	//�÷��� ���̳�?
	inline BOOL isPlay(void) { return _isPlay; }

	//��������ġ ���´�
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	//���� �ִϸ��̼� ������ ��ġ ������ ���´�
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;
		return frameX + frameY * _frameNumWidth;
	}

	//������ ����ũ�⸦ ���´�
	inline int getFrameWidth(void) { return _frameWidth; }

	//������ ����ũ�⸦ ���´�
	inline int getFrameHeight(void) { return _frameHeight; }

	//���� ����� ������ �������� ��´�
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	animation(void);
	~animation() {}
};

