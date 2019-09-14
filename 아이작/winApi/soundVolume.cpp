#include "stdafx.h"
#include "soundVolume.h"

HRESULT soundVolume::init(void)
{
	FILE* file;
	file = fopen("save/sound.txt", "r");
	fscanf(file, "%f, %f", &_sfxVolume, &_musicVolume);
	fclose(file);
	return S_OK;
}

void soundVolume::release(void)
{
}