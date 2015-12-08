#pragma once

#include "SimpleGE.h"

class MapController {
private:
    static MapController *sharedController;
public:
    MapController();
    ~MapController();

    static MapController* getInstance() {
        if (!sharedController) {
            sharedController = new MapController();
        }
        return sharedController;
    }

    bool createMapFromFile(const std::string &filename, GameObject* layer); // ���ļ���ȡ��ͼ�������ص�layer��
    int getXPositionInMap(float realPosX); // ����ʵX����ת��Ϊ��ͼ�е�X����
    int getYPositionInMap(float realPosY); // ����ʵY����ת��Ϊ��ͼ�е�Y����
};