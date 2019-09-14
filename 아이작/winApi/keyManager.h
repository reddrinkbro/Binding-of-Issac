#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];

public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init();

	//Ű�� �ѹ��� ���ȴ���
	bool isOnceKeyDown(int key);
	//������ �������
	bool isOnceKeyUp(int key);
	//������ Ű
	bool isStayKeyDown(int key);
	//���Ű
	bool isToggleKey(int key);

	keyManager() {}
	~keyManager() {}
};

