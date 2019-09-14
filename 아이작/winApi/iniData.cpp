#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release(void)
{
}

void iniData::addData(char * section, char * key, char * value)
{
	//ini 데이터 구조체 선언 후 초기화
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//ini데이터 구조체 벡터에 담기
	arrIniData vIniData;
	vIniData.push_back(iniData);

	//모든 데이터는 _vIniData에 구조체를 담은 벡터를 담기
	_vIniData.push_back(vIniData);
}

void iniData::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	//현재 폴더 명 가져오자
	GetCurrentDirectory(356, str);
	//폴더명 + 파일명
	strcat(str, dir);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		//파일쓰기
		WritePrivateProfileString(
			vData[0].section,	//대제목
			vData[0].key,		//구성요소
			vData[0].value,		//구성요소에 작성할 정보
			str);				//ini파일경로
		vData.clear();
	}
	_vIniData.clear();
}

char * iniData::loadDataString(char * fileName, char * section, char * key)
{

	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(356, str);
	strcat(str, dir);

	char data[64] = { NULL };
	//가져온 파일에서 섹션과 키로 검색한 후 data안에 넣는다
	GetPrivateProfileString(
		section,
		key,
		"",		//섹션이름이나 키이름을 찾지 못하면 디폴트로 출력할 스트링
		data,	//키값에서 가르키는 값을 저장할 버퍼
		64,		//키값을 저장할 버퍼 사이즈
		str);

	return data;
}

int iniData::loadDataIntrger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	return GetPrivateProfileInt(section, key, 0, str);
}
