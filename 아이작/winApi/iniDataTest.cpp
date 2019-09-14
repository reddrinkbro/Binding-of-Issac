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
		INIDATA->addData("º¸½Â", "¿­½É", "100");
		INIDATA->addData("±¤Á¶", "ÄÚµù½Ç·Â", "200");
		INIDATA->addData("Áö¹Î", "°«", "300");

		INIDATA->iniSave("1ÆÀ");
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		int test = INIDATA->loadDataIntrger("1ÆÀ", "Áö¹Î", "°«");
		printf("Áö¹Î: %d \n", test);
	}
}

void iniDataTest::render()
{
}