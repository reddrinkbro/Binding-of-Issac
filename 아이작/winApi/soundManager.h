#pragma once
#include "singletonbase.h"
//fmod.hpp �߰�
#include "inc/fmod.hpp"
//lib ��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

//���� ������ŭ ����
#define SOUND_BUFFER 40
//������ ä�� ���� (����)
#define EXTRA_SOUND_CHANNEL 6
//�� ���� ����
#define TOTAL_SOUND_CHANNEL (SOUND_BUFFER + EXTRA_SOUND_CHANNEL)

using namespace FMOD;

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
		
	void addSound(string keyName, string soundName,
		bool background, bool loop);
		
	void play(string keyName, float volume);	
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	soundManager();
	~soundManager() {}
};