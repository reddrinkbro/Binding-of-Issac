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
	int _alphaCount;			//알파값 반복횟수
	int _itemGetCount;			//이미지 그리는 시간
	float _mapMoveDistance;		
	float _flightTime;
	bool _isAlphaValueIncrease; //알파값 상승 하강 구분
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
	void fire(void);											//총알 발사
	void die(void);
public:
	void objectCollision(void);									//오브젝트 충돌
	void doorCollision(void);									//문 충돌
	void bulletCollision(void);									//총알 충돌(몬스터x)
	void enemyCollision(void);									//적과 충돌
public:
	void playerSpeed(void);										//캐릭터 스피드
	void playerBodyFrame(void);									//몸통 프레임
	void playerHeadFrame(void);									//머리 프레임
	void playerHit(void);										//플레이어가 공격 당했을때
public:
	void coinGetUsing(bool isUsing ,int size);					//코인 획득, 사용
	void bombGetUsing(bool isUsing);							//폭탄 획득, 사용
	void healthPointIncrease(void);								//체력 회복
	void keyGetUsing(bool isUsing);								//열쇠 획득, 사용
	void itemGet(void);											//아이템 획득시 모션
	void tileSetUp(void);										//타일 벡터 설정
	void atkChange(bool isUp);									//공격력 변경
	void speedChanage(bool isUp);								//스피드 변경
public:
	isaacHead getHead(void) { return _head; }
	isaacBody getBody(void) { return _body; }
	playerBaseBullet* getBullt(void) { return _baseBullet; }
	void setState(ISAACSTATE state) { _state = state; }			//플레이어 상태 변화
public:
	void setDungeonMapMemoryLink(dungeonMap* map) { _map = map; }
	void setEnemyManagerMemoryLink(enemyManager *em) { _enemy = em; }
	void setItemManagerMemoryLink(itemManager *item) { _item = item; }
	void setObjectManagerMemoryLink(objectManager* object) { _object = object; }
	player(){}
	~player(){}
};

