#pragma once
#include "gameNode.h"
#include "tileNode.h"

struct issacCutScene
{
	image* isaac;
	image* name;
	image* celler;
	float x;
	float y;	
};

struct bossCutScene
{
	image* boss;
	image* name;
	image* celler;
	float x;
	float y;
};

class cutScene : public gameNode
{
private:
	issacCutScene _isaac;
	bossCutScene _boss;
	image* _backGround;
	image* _versus;
	float _distance;
	float _speed;
	float _restTime;
	int _alpha;
	bool _isOn;
public:
	HRESULT init(BOSSSELECT select);
	void release(void);
	void update(void);
	void render(void);
	void speedUp(bool isGoNear);
	void speedDown(void);
	bool getIsOn(void) { return _isOn; }
	void setIsOn(bool isOn) { _isOn = isOn; }
	cutScene(){}
	~cutScene(){}
};

