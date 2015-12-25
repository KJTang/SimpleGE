#include "SimpleGE.h"
#include <time.h>

MapController* MapController::sharedController = nullptr;

MapController::MapController() {}

MapController::~MapController() {}

bool MapController::init() {
	srand(time(0));
	return true;
}

bool MapController::createMapFromFile(char* filename, GameObject* layer)
{
	FILE *fp = NULL;
	if ((fp = fopen(filename, "r")) == NULL)
		return false;
	int length = 0, width = 0;
	int i = 0, j = 0;
	fscanf(fp, "%d%d", &length, &width);
	while (i < length)
	{
		j = 0;
		while (j < width) {
			fscanf(fp, "%d", &mapInfo[i][j]);
			j++;
		}
		i++;
	}
	for (i = 0; i != length; i++)
	{
		for (j = 0; j != width; j++)
		{
			if (mapInfo[i][j] == 1)
			{
				auto map_obj = GameObject::create("wall.png");
				layer->addChild(map_obj);
				map_obj->setPosition((j - width / 2) * 20.0, (i - length / 2) * -20.0);
				//map_obj->setActive(false);
				map_obj->setSize(10);
			}
			else if (mapInfo[i][j] == 0)
			{
				//auto map_obj = GameObject::create("bean.png");
				//layer->addChild(map_obj);
				//map_obj->setPosition((j - width / 2) * 20.0, (i - length / 2) * -20.0);
				////map_obj->setActive(false);
				//map_obj->setSize(5);
			}
		}
	}

	return true;
}

int MapController::getXPositionInMap(float realPosX) // 将真实X坐标转换为地图中的X坐标
{
    //return (int)(realPosX / 20);
    return (int)(realPosX / 20 + 20);
}


int MapController::getYPositionInMap(float realPosY) // 将真实X坐标转换为地图中的X坐标
{
	//return (int)(realPosY / 20);
    return (int)(realPosY / -20 + 10);
}

//0表示没有东西，1表示墙，2表示豆子，3表示大力丸
int MapController::getObjectType(GameObject *owner)
{
	return mapInfo[(int)(owner->getPositionX() - 0.5)][(int)(owner->getPositionY() - 0.5)];
}

int MapController::getObjectType(int mapx, int mapy) {
    return mapInfo[mapy][mapx];
}

/***********
*JDL
***********/

/*地图中的X坐标转化为真实X坐标*/
float MapController::getXPositionInWorld(int mapPosX) {
	return (float)((mapPosX - 40 / 2) * 20.0);
}

/*地图中的Y坐标转化为真实Y坐标*/
float MapController::getYPositionInWorld(int mapPosY) {
	return (float)((mapPosY - 20 / 2) * -20.0);
}

/*随机生成一个空的世界坐标*/
void MapController::RndCreateEmptyPosInWorld(WPosType &wPos) {
	int x, y;
	do {
		x = rand() % 20;
		y = rand() % 40;
	}
	while (mapInfo[x][y] == 1);
	wPos.posX = (float)(x - 40 / 2) * 20.0;
	wPos.posY = (float)(y - 40 / 2) * 20.0;
}

/*随机生成一个空的地图坐标*/
void MapController::RndCreateEmptyPosInMap(MPosType &mPos) {
	int x, y;
	do {
		x = rand() % 20;
		y = rand() % 40;
	}
	while (mapInfo[x][y] == 1);
	mPos.posX = x;
	mPos.posY = y;
}

/*将世界坐标转换为地图坐标*/
MPosType MapController::ChangeWorldPosToMapPos(WPosType wPos) {
	MPosType mPos;
	mPos.posX = (int)(wPos.posX / 20);
	mPos.posY = (int)(wPos.posY / 20);
	return mPos;
}

/*将地图坐标转换为世界坐标*/
WPosType MapController::ChangeWorldPosToMapPos(MPosType mPos) {
	WPosType wPos;
	wPos.posX = (float)((mPos.posX - 40 / 2) * 20.0);
	wPos.posY = (float)((mPos.posY - 20 / 2) * -20.0);
	return wPos;
}


