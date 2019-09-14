#pragma once
#include "singletonbase.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//이펙트 클래스를 담을 벡터
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	//이펙트 클래스가 담겨있는 벡터를 담을 맵
	typedef map<string, arrEffects> arrEffect;
	typedef map<string, arrEffects>::iterator iterEffect;
	typedef vector<map<string, arrEffects>> arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffects;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effectHeight,
		int fps, int buffer);

	void play(string effectName, int x, int y);

	bool isRunning(string effectName);

	effectManager() {}
	~effectManager() {}
};
