// GameTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>

#include "SimpleGE.h"

#include "myLevel.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // System Initialize
    auto system = SystemController::getInstance();
    system->init(hInstance, nCmdShow);

    // Level One
    auto level = LevelOne::create();
    system->setCurrentLevel(level);
    level->addChild(GameObject::create());

    
    // main loop
    while (!system->isGameQuit()) {
        AESysFrameStart();		// 帧开始：封装了PeekMessage
        AEInputUpdate();		// Alpha Engine处理输入
        system->update();
        system->draw();
        AESysFrameEnd();		// 帧结束

        if (system->isLevelChanged()) {
            system->changeLevel();
        }
    }

    // System Exit
    system->exit();

    return 0;
}