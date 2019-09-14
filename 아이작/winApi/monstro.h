#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"
enum MONSTROSTATE
{
	MONSTROSTATE_NONE,
	MONSTROSTATE_FIRE,
	MONSTROSTATE_MOVE,
	MONSTROSTATE_JUMP,
	MONSTROSTATE_DIE
};
struct targetPos
{
	float x;
	float y;
};
struct monstroStrct
{
	image* img;
	RECT rc;
	MONSTROSTATE state;
	float x;
	float y;
	targetPos moveTargetPos;
	targetPos jumpTargetPos;
	float count;
	float speed;
	float hp;
	float maxHp;
	float angle;
	float moveDistance;
	float jumpDistance;
	int currentX;
	int currentY;
	int randomPattern;
	int restTime;
	bool isLeft;
	bool isDown;
};
class monstro : public gameNode
{
private:
	monstroStrct _monstro;
	monstroBullet* _bullet;
	progressBar* _hpBar;
	float _gravity;
public:
	HRESULT init(float x, float y);
	void release(void);
	void update(float x, float y);
	void render(void);
	void move(void);
	void draw(void);
	void frame(void);
	void jump(void);
	void findPlayerPos(void);
	void bulletHit(float damage);
	monstroStrct getStruct(void) { return _monstro; }
	monstroBullet* getEnemyBullet(void) { return _bullet; }
	monstro(){}
	~monstro(){}
};

