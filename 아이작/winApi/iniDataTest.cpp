#include "stdafx.h"
#include "iniDataTest.h"

HRESULT iniDataTest::init()
{
	return S_OK;
}

void iniDataTest::release()
{
}

void iniDataTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		INIDATA->addData("����", "����", "100");
		INIDATA->addData("����", "�ڵ��Ƿ�", "200");
		INIDATA->addData("����", "��", "300");

		INIDATA->iniSave("1��");
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		int test = INIDATA->loadDataIntrger("1��", "����", "��");
		printf("����: %d \n", test);
	}
}

void iniDataTest::render()
{
}