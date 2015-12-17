#pragma once

#include "SimpleGE.h"

#define MAP_ROW 20 //��������
#define MAP_LOW 40 //��������

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
	//fopen��Ҫchar* ���ͣ������ҽ�const string�ĳ���char*__by wdp
	bool createMapFromFile(char* filename, GameObject* layer); // ���ļ���ȡ��ͼ�������ص�layer��

	int getXPositionInMap(float realPosX); // ����ʵX����ת��Ϊ��ͼ�е�X����
	int getYPositionInMap(float realPosY); // ����ʵY����ת��Ϊ��ͼ�е�Y����

	int getObjectType(GameObject *owner);//�ж�λ�õ�Object������
};