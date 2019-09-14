#pragma once
#include "treasureChest.h"
#include "spike.h"
#include "door.h"
#include "exitObject.h"
#include "poop.h"

struct treasureChestData
{
	treasureChest* chest;
	int pos;
};

struct spikeSmallData
{
	spikeSmall* spike;
	int pos;
};

struct spikeLargeData
{
	spikeLarge * spike;
	int pos;
};

struct doorData
{
	door* door;
	int pos;
};

struct basicPoopData
{
	basicPoop* poop;
	int pos;
};

struct redPoopData
{
	redPoop* poop;
	int pos;
};