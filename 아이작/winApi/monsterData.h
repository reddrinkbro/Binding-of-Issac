#pragma once
#include "frowningGaper.h"
#include "clotty.h"
#include "horf.h"
#include "attackFly.h"
#include "level2Fly.h"
#include "blubber.h"
#include "charger.h"
//#include "hopper.h"
#include "tumor.h"
#include "dukeofflies.h"
#include "monstro.h"
#include "megamaw.h"

enum COLLISIONMONSTER
{
	COLLISIONMONSTER_BLUBBER,
	COLLISIONMONSTER_CHARGER,
	COLLISIONMONSTER_CLOTTY,
	COLLISIONMONSTER_HOPPER,
	COLLISIONMONSTER_DUKEOFFLIES
};

struct blood
{
	image* img;
	float x;
	float y;
};

struct frowningGaperData
{
	frowningGaper* gaper;
	int pos;
};
struct clottyData
{
	clotty* clotty;
	int pos;
};
struct horfData
{
	horf* horf;
	int pos;
};
struct attackFlyData
{
	attackFly* attackFly;
	int pos;
};
struct level2FlyData
{
	level2Fly* level2Fly;
	int pos;
};
struct blubberData
{
	blubber* blubber;
	int pos;
};
struct chargerData
{
	charger* charger;
	int pos;
};

struct tumorData
{
	tumor* tumor;
	int pos;
};

struct dukeoffliesData
{
	dukeofflies* dukeofflies;
	int pos;
};

struct monstroData
{
	monstro* monstro;
	int pos;
};

struct megamawData
{
	megamaw* megamaw;
	int pos;
};