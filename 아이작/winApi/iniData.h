#pragma once
#include "singletonBase.h"

struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase<iniData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);
	void release(void);

	//������ �߰�(����, Ű, ����)
	void addData(char* section, char* key, char* value);
	//���̺� -> �����̸��� �־ �ڵ� ����
	void iniSave(char* fileName);

	//���ڰ� �ε�
	char* loadDataString(char* fileName, char* section, char* key);
	//������ �ε�
	int loadDataIntrger(char* fileName, char* section, char* key);

	iniData() {}
	~iniData() {}
};

