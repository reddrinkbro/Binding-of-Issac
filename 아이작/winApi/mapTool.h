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
	//문 제외
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
	//타일 창
	// 0 : 베이스, 1 : 다이스룸, 2 : 케이브  , 3 : 체스트 , 4 : 네크로폴리스, 5 : 시크릿룸
	tagSampleRoom _sampleRoom[6];
	tilesPaper* _paper;
	miniMap* _miniMap;
	//타일 드래그로 그릴때 좌표가 될 인덱스
	int _xIndex1, _xIndex2, _xIndex3, _xIndex4;
	//타일 드래그로 그린 인덱스를 저장할 인덱스
	int _dIndex1, _dIndex2;
	//타일 지우기로 그린 인덱스를 저장할 인덱스
	int _eIndex1, _eIndex2;
	//상점 좌표를 저장할 인덱스
	int _sIndex;
	bool _isTileBrushOn;
	bool _mouseInpaper;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//맵툴 셋팅
	void maptoolSetup();
	void setMap();
	void save();
	void load();
	//드래그로 타일 그리기
	void tileDraw(void);
	//지형, 오브젝트
	TERRAIN terrainSelect(int index);
	OBJECT objSelect(int frameX, int frameY);
	TERRAINTILE tileSelect(int frameX, int frameY);
	FRAMEOBJECT frameObjSelect(int frameX, int frameY);
	DOOROBJECT doorObjSelect(int frameX, int frameY);
	PROPS propsSelect(int index);
	MONSTER monsterSelect(int frameX, int frameY);
	ITEM itemSelect(int frameX, int frameY);
	void tileSetup(void);
	//타일 그리기
	void tileRender(void);
	//타일이 있는지 없는지 확인, 타일 드래그시 타일 색상 변화
	void tileCheck(int index);
	//지우기
	void erase();
	//상점 맵 건설
	void shopMap();

	tilesPaper* getPaper(void) { return _paper; }
	mapTool(){}
	~mapTool(){}
};

