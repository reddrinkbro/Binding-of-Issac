#pragma once
#include "gameNode.h"

struct playerHp
{
	image* img;
	float x;
	float y;
	int currentX;
	int currentPoint;
};
struct coinUI
{
	image* img;
	float x;
	float y;
};
struct bombUI
{
	image* img;
	float x;
	float y;
};
struct keyUI
{
	image* img;
	float x;
	float y;
};
class playerUI : public gameNode
{
private:
	playerHp _playerHp;
	vector<playerHp> _vPlayerHp;
	vector<playerHp>::iterator _viPlayerHp;
	coinUI _coin;
	vector<int> _coinNum;
	bombUI _bomb;
	vector<int> _bombNum;
	keyUI _key;
	vector<int> _keyNum;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void increaseHp();
	void decreaseHp(void);
	void increaseCoin(void);
	void decreaseCoin(void);
	void increaseBomb(void);
	void decreaseBomb(void);
	void increaseKey(void);
	void decreaseKey(void);
	vector<int> getCoinUI(void) { return _coinNum; }
	vector<int> getBombUI(void) { return _bombNum; }
	vector<int> getKeyUI(void) { return _keyNum; }
	playerUI(){}
	~playerUI(){}
};

