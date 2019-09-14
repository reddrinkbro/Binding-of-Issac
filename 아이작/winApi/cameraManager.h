#pragma once
#include "singletonBase.h"

enum CAMERAMOVE
{
	CAMERAMOVE_UP,
	CAMERAMOVE_DOWN,
	CAMERAMOVE_LEFT,
	CAMERAMOVE_RIGHT
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _cameraSpeed;
	float _minRenderX;
	float _minRenderY;
	float _maxRenderX;
	float _maxRenderY;
	float _maxGameRenderX;
	float _maxGameRenderY;
	float _cPosX;
	float _cPosY;
	RECT _window;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getRenderX(void) { return _minRenderX; }
	float getRenderY(void) { return _minRenderY; }
	float getMaxRenderX(void) { return _maxRenderX; }
	float getMaxRenderY(void) { return _maxRenderY; }
	float getX(void) { return _cPosX; }
	float getY(void) { return _cPosY; }
	float getGameMaxRenderX(void){ return _maxGameRenderX; }
	float getGameMaxRenderY(void) { return _maxGameRenderY; }
	RECT getWindow(void) { return _window; }
	void camerMoveInMapTool(void);
	void cameraMoveX(CAMERAMOVE _cameraMove);
	void cameraMoveY(CAMERAMOVE _cameraMove, bool isWall);
	void setCameraPos(float x, float y);
	cameraManager(){}
	~cameraManager(){}
};

