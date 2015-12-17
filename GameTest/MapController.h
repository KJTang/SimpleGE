#pragma once

#include "SimpleGE.h"

#define MAP_ROW 20 //数组行数
#define MAP_LOW 40 //数组列数

class MapController {
private:
	static MapController *sharedController;
	int mapInfo[MAP_ROW][MAP_LOW];
public:
	MapController();
	~MapController();

	static MapController* getInstance() {
		if (!sharedController) {
			sharedController = new MapController();
		}
		return sharedController;
	}
	//fopen需要char* 类型，所以我将const string改成了char*__by wdp
	bool createMapFromFile(char* filename, GameObject* layer); // 从文件读取地图，并加载到layer上

	int getXPositionInMap(float realPosX); // 将真实X坐标转换为地图中的X坐标
	int getYPositionInMap(float realPosY); // 将真实Y坐标转换为地图中的Y坐标

	int getObjectType(GameObject *owner);//判断位置的Object的类型
};