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

    bool createMapFromFile(const std::string &filename, GameObject* layer); // 从文件读取地图，并加载到layer上
    int getXPositionInMap(float realPosX); // 将真实X坐标转换为地图中的X坐标
    int getYPositionInMap(float realPosY); // 将真实Y坐标转换为地图中的Y坐标
};