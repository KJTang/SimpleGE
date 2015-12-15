#include "MapController.h"

MapController* MapController::sharedController = nullptr;

MapController::MapController() {}

MapController::~MapController() {}

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
				map_obj->setPosition((j - width/2) * 20.0, (i - length/2) * -20.0);
				//map_obj->setActive(false);
				map_obj->setSize(10);
			}
			else if (mapInfo[i][j] == 0)
			{
				auto map_obj = GameObject::create("bean.png");
				layer->addChild(map_obj);
				map_obj->setPosition((j - width/2) * 20.0, (i - length/2) * -20.0);
				//map_obj->setActive(false);
				map_obj->setSize(5);
			}
		}
	}
	
	return true;
}

int MapController::getXPositionInMap(float realPosX) // ����ʵX����ת��Ϊ��ͼ�е�X����
{
	return (int)(realPosX / 20);
}


int MapController::getYPositionInMap(float realPosY) // ����ʵX����ת��Ϊ��ͼ�е�X����
{
	return (int)(realPosY / 20);
}

//0��ʾû�ж�����1��ʾǽ��2��ʾ���ӣ�3��ʾ������
int MapController::getObjectType(GameObject *owner)
{
	return mapInfo[(int)(owner->getPositionX() - 0.5)][(int)(owner->getPositionY() - 0.5)];
}



