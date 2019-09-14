#pragma once
#include "gameNode.h"
#include "tilesPaper.h"
#include "tileNode.h"
#include "miniMap.h"
class mapTool : public gameNode
{
private:

	HBRUSH _tileBrush;
	HBRUSH _tileOldBrush;
	vector<image*>_tileSampleImage;
	//�� ����
	vector<image*> _objectImage;
	vector<image*> _propsImage;
	vector<image*> _monsterImage;
	vector<image*> _itemImage;
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagSampleTile _sampleProps[PROPSTILEX * PROPSTILEY];
	tagSampleTile _sampleObject[OBJECTTILEX * OBJECTTILEY];
	tagSampleTile _sampleFrameObject[FRAMEOBJECTTILEX * FRAMEOBJECTTILEY];
	tagSampleTile _sampleDoor[DOORTILEX * DOORTILEY];
	tagSampleTile _sampleMonsterObject[MONSTEROBJECTTILEX * MONSTEROBJECTTILEY];
	tagSampleTile _sampleItemObject[ITEMOBJECTTILEX * ITEMOBJECTTILEY];
	POINT _pos[2];
	//Ÿ�� â
	// 0 : ���̽�, 1 : ���̽���, 2 : ���̺�  , 3 : ü��Ʈ , 4 : ��ũ��������, 5 : ��ũ����
	tagSampleRoom _sampleRoom[6];
	tilesPaper* _paper;
	miniMap* _miniMap;
	//Ÿ�� �巡�׷� �׸��� ��ǥ�� �� �ε���
	int _xIndex1, _xIndex2, _xIndex3, _xIndex4;
	//Ÿ�� �巡�׷� �׸� �ε����� ������ �ε���
	int _dIndex1, _dIndex2;
	//Ÿ�� ������ �׸� �ε����� ������ �ε���
	int _eIndex1, _eIndex2;
	//���� ��ǥ�� ������ �ε���
	int _sIndex;
	bool _isTileBrushOn;
	bool _mouseInpaper;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//���� ����
	void maptoolSetup();
	void setMap();
	void save();
	void load();
	//�巡�׷� Ÿ�� �׸���
	void tileDraw(void);
	//����, ������Ʈ
	TERRAIN terrainSelect(int index);
	OBJECT objSelect(int frameX, int frameY);
	TERRAINTILE tileSelect(int frameX, int frameY);
	FRAMEOBJECT frameObjSelect(int frameX, int frameY);
	DOOROBJECT doorObjSelect(int frameX, int frameY);
	PROPS propsSelect(int index);
	MONSTER monsterSelect(int frameX, int frameY);
	ITEM itemSelect(int frameX, int frameY);
	void tileSetup(void);
	//Ÿ�� �׸���
	void tileRender(void);
	//Ÿ���� �ִ��� ������ Ȯ��, Ÿ�� �巡�׽� Ÿ�� ���� ��ȭ
	void tileCheck(int index);
	//�����
	void erase();
	//���� �� �Ǽ�
	void shopMap();

	tilesPaper* getPaper(void) { return _paper; }
	mapTool(){}
	~mapTool(){}
};

