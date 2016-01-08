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
    auto level = LoadingLevel::create();
    system->setCurrentLevel(level);

    // GameStart
    system->start();

    // System Exit
    system->exit();

    return 0;
}