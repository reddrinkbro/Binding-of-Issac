#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "playerUI.h"
#include "familiar.h"
#include "tileNode.h"
#include "shadow.h"

class dungeonMap;
class enemyManager;
class itemManager;
class objectManager;

enum ISAACSTATE
{
	ISAACSTATE_NONE,
	ISAACSTATE_HIT,
	ISAACSTATE_ITEMGET,
	ISAACSTATE_BUFF,
	ISAACSTATE_DEBUFF,
	ISAACSTATE_DIE,
	ISAACSTATE_MAPMOVE
};

enum HEADSTATE
{
	HEADSTATE_LEFT,
	HEADSTATE_RIGHT,
	HEADSTATE_UP,
	HEADSTATE_DOWN
};

enum BODYSTATE
{
	BODYSTATE_LEFT,
	BODYSTATE_RIGHT,
	BODYSTATE_UP,
	BODYSTATE_DOWN
};

struct isaacHead
{
	image* img;
	RECT rc;
	HEADSTATE headState;
	float x;
	float y;
	float count;
	int currentX;
	int currentY;
};

struct isaacBody
{
	image* img;
	RECT rc;
	BODYSTATE bodyState;
	float x;
	float y;
	float currentSpeed;
	float maxSpeed;
	float count;
	float atk;
	int currentHp;
	int maxHp;
	int currentX;
	int currentY;
	bool isMove;
	bool isSlow;
};
struct ghost
{
	image* img;
	RECT rc;
	float x;
	float y;
	float count;
	float speed;
	float distnace;
	int currentX;
};

class player : public gameNode
{
private:
	ISAACSTATE _state;
	isaacHead _head;
	isaacBody _body;
	playerBaseBullet* _baseBullet;
	dungeonMap* _map;
	playerUI* _playerUI;
	enemyManager* _enemy;
	itemManager * _item;
	objectManager* _object;
	familiar* _familiar;
	shadow* _shadow;
	ghost _ghost;
	int _alpha;
	int _alphaCount;			//���İ� �ݺ�Ƚ��
	int _itemGetCount;			//�̹��� �׸��� �ð�
	float _mapMoveDistance;		
	float _flightTime;
	bool _isAlphaValueIncrease; //���İ� ��� �ϰ� ����
	bool _familiarOn;			
	bool _ouijaboardOn;
	vector<tagTile> tileVec;
	vector<DWORD> attributeVec;
public:
	HRESULT init(float x ,float y);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void move(void);
	void fire(void);											//�Ѿ� �߻�
	void die(void);
public:
	void objectCollision(void);									//������Ʈ �浹
	void doorCollision(void);									//�� �浹
	void bulletCollision(void);									//�Ѿ� �浹(����x)
	void enemyCollision(void);									//���� �浹
public:
	void playerSpeed(void);										//ĳ���� ���ǵ�
	void playerBodyFrame(void);									//���� ������
	void playerHeadFrame(void);									//�Ӹ� ������
	void playerHit(void);										//�÷��̾ ���� ��������
public:
	void coinGetUsing(bool isUsing ,int size);					//���� ȹ��, ���
	void bombGetUsing(bool isUsing);							//��ź ȹ��, ���
	void healthPointIncrease(void);								//ü�� ȸ��
	void keyGetUsing(bool isUsing);								//���� ȹ��, ���
	void itemGet(void);											//������ ȹ��� ���
	void tileSetUp(void);										//Ÿ�� ���� ����
	void atkChange(bool isUp);									//���ݷ� ����
	void speedChanage(bool isUp);								//���ǵ� ����
public:
	isaacHead getHead(void) { return _head; }
	isaacBody getBody(void) { return _body; }
	playerBaseBullet* getBullt(void) { return _baseBullet; }
	void setState(ISAACSTATE state) { _state = state; }			//�÷��̾� ���� ��ȭ
public:
	void setDungeonMapMemoryLink(dungeonMap* map) { _map = map; }
	void setEnemyManagerMemoryLink(enemyManager *em) { _enemy = em; }
	void setItemManagerMemoryLink(itemManager *item) { _item = item; }
	void setObjectManagerMemoryLink(objectManager* object) { _object = object; }
	player(){}
	~player(){}
};

