#include "stdafx.h"
#include "mainGame.h"
#include "menuScene.h"
#include "mapToolScene.h"
#include "dungeonGameScene.h"
#include "optionScene.h"
//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	SCENEMANAGER->addScene("����", new mapToolScene);
	SCENEMANAGER->addScene("�޴�", new menuScene);
	SCENEMANAGER->addScene("����" ,new dungeonGameScene);
	SCENEMANAGER->addScene("�ɼ�", new optionScene);
	SCENEMANAGER->changeScene("�޴�");
	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ
	SCENEMANAGER->update();

}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	//������ �� ��Ʈ�� (�̰͵� ������ �״�� �Ѱ�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================

	//��üȭ�� ���ʿ� ���� ���
	//��üȭ�� ���ʿ� ������Ʈ ���
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//=============================================================
	//������� ������ HDC�� �׸���
	this->getBackBuffer()->render(getHDC());
}