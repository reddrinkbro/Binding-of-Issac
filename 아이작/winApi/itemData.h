#pragma once
#include "coin.h"
#include "bomb.h"
#include "healthPoint.h"
#include "pentagram.h"
#include "ouijaboard.h"
#include "ghostBaby.h"
#include "pillATKUP.h"
#include "pillSPEEDUP.h"
#include "pillATKDOWN.h"
#include "pillSPEEDDOWN.h"
#include "key.h"

struct coinData
{
	coin* coin;
};
struct bombData
{
	bomb* bomb;
};
struct healthPointData
{
	healthPoint* healthPoint;
};

struct pentagramData
{
	pentagram* pentagram;
	int pos;
};
struct ouijaboardData
{
	ouijaboard* ouijaboard;
	int pos;
};

struct ghostBabyData
{
	ghostBaby* ghostBaby;
	int pos;
};

struct pillATKUPData
{
	pillATKUP* pillATKUP;
};

struct pillSPEEDUPData
{
	pillSPEEDUP* pillSPEEDUP;
};

struct pillATKDOWNData
{
	pillATKDOWN* pillATKDOWN;
};

struct pillSPEEDDOWNData
{
	pillSPEEDDOWN* pillSPEEDDOWN;
};

struct keyData
{
	key* key;
};