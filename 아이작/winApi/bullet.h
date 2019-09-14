#pragma once
#include "gameNode.h"
#include "shadow.h"
enum BULLETDIRECTION
{
	BULLETDIRECTION_UP,
	BULLETDIRECTION_DOWN,
	BULLETDIRECTION_LEFT,
	BULLETDIRECTION_RIGHT
};

struct tagBullet
{
	image* img;
	RECT rc;
	BULLETDIRECTION diretion;
	shadow* shadow;
	float x;
	float y;
	float fireX;
	float fireY;
	float speed;
	float angle;
	float range;
	float gravity;
	float distance;
	float shadowDistance;
};

class playerBaseBullet : public gameNode
{
private:
	float _range;
	float _cooldDownTime;
	float _maxCooldDownTime;
	bool _isFire;
	bool _itemOn;
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	HRESULT init(float range, float maxCooldDownTime);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float speed, BULLETDIRECTION _direction, int itemOn);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBaseBullet(void) { return _vBullet; }
	bool getIsFire(void) { return _isFire; }
	int getCoolDownTime(void) { return _cooldDownTime; }
	playerBaseBullet(){}
	~playerBaseBullet(){}
};

class clottyBullet : public gameNode
{
private:
	float _range;
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	clottyBullet(){}
	~clottyBullet(){}
};

class horfBullet : public gameNode
{
private:
	float _range;
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y,float playerX, float playerY, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	horfBullet() {}
	~horfBullet() {}
};

class sixWayBullet : public gameNode
{
private:
	float _range;
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y,float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	sixWayBullet() {}
	~sixWayBullet() {}
};

class blubberBullet : public gameNode
{
private:
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;
public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	blubberBullet() {}
	~blubberBullet() {}
};

class familiarBullet : public gameNode
{
private:
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;	
	float _range;
public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float speed, BULLETDIRECTION _direction);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	familiarBullet() {}
	~familiarBullet() {}
};

class monstroBullet : public gameNode
{
private:
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float angle, int bulletMax ,bool isJump);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	monstroBullet() {}
	~monstroBullet() {}
};

class megamawBullet : public gameNode
{
private:
	vector <tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	int _pattern;
	int _currentX;
	int _bulletNum;
	float _count;
	float _addAngle;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fire(float x, float y, float angle, int bulletMax, int range, int pattern);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);
	vector <tagBullet> getBullet(void) { return _vBullet; }
	megamawBullet() {}
	~megamawBullet() {}
};