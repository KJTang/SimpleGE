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
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    auto level = LevelZero::create();
    //auto level = LevelSuccess::create();
    //auto level = LevelFaile::create();

<<<<<<< HEAD
    //auto level = LevelOne::create();
    //auto level = LoadingLevel::create();
=======
    //auto level = LevelOne::create();
    //auto level = LoadingLevel::create();
=======
<<<<<<< HEAD
    auto level = LevelZero::create();
	//auto level = LevelSuccess::create();
	//auto level = LevelFaile::create();

=======
    //auto level = LevelOne::create();
    auto level = LoadingLevel::create();
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    system->setCurrentLevel(level);

    // GameStart
    system->start();

    // System Exit
    system->exit();

    return 0;
}