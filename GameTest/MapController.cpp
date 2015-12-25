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

int MapController::getXPositionInMap(float realPosX) // ����ʵX����ת��Ϊ��ͼ�е�X����
{
    //return (int)(realPosX / 20);
    return (int)(realPosX / 20 + 20);
}


int MapController::getYPositionInMap(float realPosY) // ����ʵX����ת��Ϊ��ͼ�е�X����
{
	//return (int)(realPosY / 20);
    return (int)(realPosY / -20 + 10);
}

//0��ʾû�ж�����1��ʾǽ��2��ʾ���ӣ�3��ʾ������
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

/*��ͼ�е�X����ת��Ϊ��ʵX����*/
float MapController::getXPositionInWorld(int mapPosX) {
	return (float)((mapPosX - 40 / 2) * 20.0);
}

/*��ͼ�е�Y����ת��Ϊ��ʵY����*/
float MapController::getYPositionInWorld(int mapPosY) {
	return (float)((mapPosY - 20 / 2) * -20.0);
}

/*�������һ���յ���������*/
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

/*�������һ���յĵ�ͼ����*/
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

/*����������ת��Ϊ��ͼ����*/
MPosType MapController::ChangeWorldPosToMapPos(WPosType wPos) {
	MPosType mPos;
	mPos.posX = (int)(wPos.posX / 20);
	mPos.posY = (int)(wPos.posY / 20);
	return mPos;
}

/*����ͼ����ת��Ϊ��������*/
WPosType MapController::ChangeWorldPosToMapPos(MPosType mPos) {
	WPosType wPos;
	wPos.posX = (float)((mPos.posX - 40 / 2) * 20.0);
	wPos.posY = (float)((mPos.posY - 20 / 2) * -20.0);
	return wPos;
}


