#pragma once
#include "singletonBase.h"

class soundVolume : public singletonBase<soundVolume>
{
private:
	float _musicVolume;
	float _sfxVolume;
public:
	HRESULT init(void);
	void release(void);
	float getMusicVolume(void) { return _musicVolume; }
	float getSfxVolume(void) { return _sfxVolume; }
	void setMusicVolume(float musicVolume) { _musicVolume = musicVolume; }
	void setSfxVolume(float sfxVolume) { _sfxVolume = sfxVolume; }
	soundVolume(){}
	~soundVolume(){}
};

