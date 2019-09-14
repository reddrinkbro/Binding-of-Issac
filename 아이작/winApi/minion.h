#pragma once
#include "frowningGaper.h"
#include "clotty.h"
#include "horf.h"
#include "attackFly.h"
#include "level2Fly.h"
#include "blubber.h"
#include "charger.h"
#include "tumor.h"

class frowningGaperMinion : public frowningGaper
{
public:
	frowningGaperMinion();
	~frowningGaperMinion();
};

class clottyMinion : public clotty
{
public:
	clottyMinion();
	~clottyMinion();
};

class horfMinion : public horf
{
public:
	horfMinion();
	~horfMinion();
};

class attackFlyMinion :public attackFly
{
public:
	attackFlyMinion();
	~attackFlyMinion();
};

class level2FlyMinion :public level2Fly
{
public:
	level2FlyMinion();
	~level2FlyMinion();
};

class blubberMinion : public blubber
{
public:
	blubberMinion();
	~blubberMinion();
};

class chargerMinion : public charger
{
public:
	chargerMinion();
	~chargerMinion();
};

class tumorMinion : public tumor
{
public:
	tumorMinion();
	~tumorMinion();
};