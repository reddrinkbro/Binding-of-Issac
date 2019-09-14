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

	//이펙트를 모두 넣어둔 벡터 검사
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

	//이펙트를 모두 넣어둔 벡터 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키 검사
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

	//이펙트를 모두 넣어둔 벡터 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키 검사
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
	arrEffects vEffectBuffer;		//이펙트 버퍼를 담는다
	arrEffect mArrEffect;			//키값과 벡터 이펙트를 담는다


	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else	//이미지 없으면 추가
	{
		img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	//이펙트 벡터로 푸쉬
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps);
	}

	//이펙트 버퍼를 맵에 담는다
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));

	_vTotalEffects.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어둔 벡터 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키 검사
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트 이름을 비교해서 같지 않으면 다음 맵으로 넘어간다
			if (!(effectName == mIter->first)) break;

			//이펙트 키와 일치하면 이펙트를 실행
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

	//이펙트를 모두 넣어둔 벡터 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키 검사
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트 이름을 비교해서 같지 않으면 다음 맵으로 넘어간다
			if (!(effectName == mIter->first)) break;

			//이펙트 키와 일치하면 이펙트를 실행
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				return (*vArrIter)->getIsRunning();
			}
		}
	}
}
