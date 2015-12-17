#pragma once

#include "SimpleGE.h"

#define MAP_ROW 20 //��������
#define MAP_LOW 40 //��������


class MapController {
private:
	static MapController *sharedController;
public:
	int mapInfo[MAP_ROW][MAP_LOW];
	MapController();
	~MapController();

	static MapController* getInstance() {
		if (!sharedController) {
			sharedController = new MapController();
		}
		return sharedController;
	}
	//fopen��Ҫchar* ���ͣ������ҽ�const string�ĳ���char*__by wdp
	bool createMapFromFile(char* filename, GameObject* layer); // ���ļ���ȡ��ͼ�������ص�layer��

	int getXPositionInMap(float realPosX); // ����ʵX����ת��Ϊ��ͼ�е�X����
	int getYPositionInMap(float realPosY); // ����ʵY����ת��Ϊ��ͼ�е�Y����

	int getObjectType(GameObject *owner);//�ж�λ�õ�Object������

	/***********
	*JDL
	***********/

	/*��ͼ�е�X����ת��Ϊ��ʵX����*/
	float getXPositionInWorld(int mapPosX);

	/*��ͼ�е�Y����ת��Ϊ��ʵX����*/
	float getYPositionInWorld(int mapPosY);
};