#pragma once

#include <iostream>
#include <string>
#include <cstdio>

#include "AEEngine.h"

#define GameLog SystemController::getInstance()->log

using std::cout;
using std::endl;
using std::string;

// forward declaration
class GameObject;
class Level;

class SystemController
{
private:
    static SystemController* sharedController;
    AESysInitInfo sysInitInfo;

    // flag
    bool gameQuit;
    bool levelChange;
    // Level Controll
    Level* currentLevel, *nextLevel;
    // GameObject Control
    GameObject* rootObject;
    void setRootObject(GameObject* rootObj);
    void recursiveUpdate(GameObject* go);
    void recursiveDraw(GameObject* go);
public:
    void update();
    void draw();

public:
    SystemController() {}
    ~SystemController() {}

    static SystemController* getInstance() {
        if (!sharedController) {
            sharedController = new SystemController();
        }
        return sharedController;
    }

    // 系统初始化
    int init(HINSTANCE hInstance, int nCmdShow);
    // 切换关卡
    bool isLevelChanged() { return levelChange; }
    void changeLevel();
    // 系统退出
    bool isGameQuit() { return gameQuit; }
    void quitGame(); // 用于调用的接口
    void exit();
    // log
    void log(const string &info);

    void setCurrentLevel(Level* level);
    void setNextLevel(Level* level);
};