#pragma once
#include "gameNode.h"

struct spikeStruct
{
	image * img;
	RECT rc;
	float x;
	float y;
	float count;
	float startTime;
	float endTime;
	int currentY;
};

class spikeSmall : public gameNode
{
private:
	spikeStruct _spike;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void frame(void);
	spikeStruct getStruct(void) { return _spike; }
	spikeSmall(){}
	~spikeSmall(){}
};

class spikeLarge : public gameNode
{
private:
	spikeStruct _spike;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);
	void frame(void);
	spikeStruct getStruct(void) { return _spike; }
	spikeLarge() {}
	~spikeLarge() {}
};
