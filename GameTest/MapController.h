#pragma once

#include "SimpleGE.h"
#include "MonsterAI.h"

//#define MAP_ROW 20 //数组行数
//#define MAP_LOW 40 //数组列数
//
///*地图坐标类型定义*/
//typedef struct MPosType {
//	int posX;		//横坐标，对应数组行
//	int posY;		//纵坐标，对应数组列
//}MPosType;
//
///*世界坐标类型定义*/
//typedef struct WPosType {
//	float posX;		//横坐标
//	float posY;		//纵坐标
//}WPosType;
//
///*基于宽度优先搜索算法下的路径结点类型定义*/
//typedef struct DElemType {
//	int ord;		//路径结点在路径上的“序号”
//	MPosType seat;	//路径结点在地图上的“坐标位置”
//	int di;			//从此结点走向下一结点的“方向”
//}DElemType;
//
///*基于深度优先搜索算法下的路径结点类型定义*/
//typedef struct WElemType {
//	int vexs[20][40];  //保存从开始结点到当前结点的路径
//	MPosType seat;				  //路径结点在地图上的“坐标位置”
//}WElemType;
//

class MapController {
private:
	static MapController *sharedController;
public:
	int mapInfo[MAP_ROW][MAP_LOW];
	MPosType rndmPos;
	WPosType rndwPos;
	MapController();
	~MapController();

	static MapController* getInstance() {
		if (!sharedController) {
			sharedController = new MapController();
			sharedController->init();
		}
		return sharedController;
	}
	bool init();
	//fopen需要char* 类型，所以我将const string改成了char*__by wdp
	bool createMapFromFile(char* filename, GameObject* layer); // 从文件读取地图，并加载到layer上

	int getXPositionInMap(float realPosX); // 将真实X坐标转换为地图中的X坐标
	int getYPositionInMap(float realPosY); // 将真实Y坐标转换为地图中的Y坐标

	int getObjectType(GameObject *owner);//判断位置的Object的类型
    int getObjectType(int mapX, int mapY);

	/***********
	*JDL
	***********/

	/*地图中的X坐标转化为真实X坐标*/
	float getXPositionInWorld(int mapPosX);

	/*地图中的Y坐标转化为真实X坐标*/
	float getYPositionInWorld(int mapPosY);

	/*随机生成一个空的世界坐标*/
	void RndCreateEmptyPosInWorld(WPosType &wPos);

	/*随机生成一个空的地图坐标*/
	void RndCreateEmptyPosInMap(MPosType &mPos);

	/*将地图坐标转换为世界坐标*/
	WPosType  ChangeWorldPosToMapPos(MPosType mPos);

	/*将世界坐标转换为地图坐标*/
	MPosType ChangeWorldPosToMapPos(WPosType wPos);
};