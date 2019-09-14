#include "stdafx.h"
#include "txtDataManager.h"

HRESULT txtDataManager::init(void)
{
	return S_OK;
}

void txtDataManager::release(void)
{
}

void txtDataManager::save(const char * fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVEBUFFER];
	DWORD write;

	strncpy_s(str, SAVEBUFFER, vectorArrayCombine(vStr), SAVEBUFFER - 1);

	file = CreateFile(fileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

char * txtDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVEBUFFER];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, SAVEBUFFER, vArray[i].c_str(), SAVEBUFFER - 1);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

vector<string> txtDataManager::load(const char * fileName)
{
	HANDLE file;
	char str[LOADBUFFER];
	DWORD read;

	memset(str, 0, LOADBUFFER);
	file = CreateFile(fileName, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, str, LOADBUFFER, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = ",";
	char* token;
	char* token2;

	token = strtok_s(charArray, separator, &token2);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &token2)))
	{
		vArray.push_back(token);
	}
	return vArray;
}
