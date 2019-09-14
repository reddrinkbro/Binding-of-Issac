#include "StdAfx.h"
#include "effectManager.h"
#include "effect.h"

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	vIter = _vTotalEffects.begin();
	for (vIter; vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (mIter; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					SAFE_DELETE(*vArrIter);
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}

	_vTotalEffects.clear();
}

void effectManager::update(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update(TIMEMANAGER->getElapsedTime());
			}
		}
	}
}

void effectManager::render(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{				
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(string effectName, const char* imageName,
	int imageWidth, int imageHeight, int effectWidth, int effectHeight,
	int fps, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;		//����Ʈ ���۸� ��´�
	arrEffect mArrEffect;			//Ű���� ���� ����Ʈ�� ��´�


	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else	//�̹��� ������ �߰�
	{
		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	//����Ʈ ���ͷ� Ǫ��
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps);
	}

	//����Ʈ ���۸� �ʿ� ��´�
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));

	_vTotalEffects.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y);
				return;
			}
		}
	}
}

bool effectManager::isRunning(string effectName)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				return (*vArrIter)->getIsRunning();
			}
		}
	}
}
