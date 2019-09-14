#include "stdafx.h"
#include "mapToolScene.h"

HRESULT mapToolScene::init(void)
{
	_mapTool = new mapTool;
	_mapTool->init();
	return S_OK;
}

void mapToolScene::release(void)
{
	SAFE_DELETE(_mapTool);
}

void mapToolScene::update(void)
{
	_mapTool->update();
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_mapTool->setMap();
	}
	CAMERAMANAGER->camerMoveInMapTool();
}

void mapToolScene::render(void)
{
	_mapTool->render();
}
