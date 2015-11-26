#include "myLevel.h"
#include "myObject.h"
#include "myAbility.h"

/********************
Level One
*******************/
LevelOne::LevelOne() {}
LevelOne::~LevelOne() {}

bool LevelOne::init() {
    if (!Level::init()) {
        return false;
    }
    count = 0;

    auto go = GameObject::create("test.png");
    this->addChild(go);
    go->setPosition(0, 0);
    go->setSize(20);

    return true;
}

void LevelOne::update() {
    Level::update();
    if (count >= 300) {
        GameLog("LevelChange: LevelOne to LevelTwo");
        SystemController::getInstance()->setNextLevel(LevelTwo::create());
    }
    ++count;
}

/********************
Level Two
*******************/
LevelTwo::LevelTwo() {}
LevelTwo::~LevelTwo() {}

bool LevelTwo::init() {
    if (!Level::init()) {
        return false;
    }
    count = 0;

    auto go = GameObject::create("test.png");
    this->addChild(go);
    auto go2 = GameObject::create("test.png");
    this->addChild(go2);
    auto pos = go2->getPosition();
    pos.y += 10;
    go2->setPosition(pos);
    go2->setDirection(3.14f);
    go2->setVelocity(-30, 0);

    return true;
}

void LevelTwo::update() {
    Level::update();
    if (count >= 180) {
        SystemController::getInstance()->quitGame();
    }
    ++count;
}
