#include "myLevel.h"
#include "myObject.h"
#include "myAbility.h"
#include "MonsterAI.h"
#include "MapController.h"

/********************
Loading Level
*******************/
LoadingLevel::LoadingLevel() {}
LoadingLevel::~LoadingLevel() {}

bool LoadingLevel::init() {
    if (!Level::init()) {
        return false;
    }
    count = 0;
    quit = false;

    auto loading = Animation::create();
    this->addChild(loading);
    for (int i = 0; i != 12; ++i) {
        char filename[40];
        sprintf(filename, "picture/loading/loading%02d.png", i);
        loading->addFrame(filename);
    }
    loading->start(0.05, -1);
    loading->setSize(50);
    loading->setPosition(0, 0);
    
    SoundController::getInstance()->loadMusic("music/test.mp3", [](void *data) {memset(data, 1, sizeof(bool)); }, (void*)(&quit));

    return true;
}

void LoadingLevel::update() {
    if (count++ >= 60) {
        if (quit) {
            SystemController::getInstance()->setNextLevel(LevelOne::create());
        }
    }
}

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

    SoundController::getInstance()->playMusic("music/test.mp3");
    /********************
    TKJ
    *******************/
    //auto ani = Animation::create();
    //this->addChild(ani);
    //ani->addFrame("animation01.png");
    //ani->addFrame("animation02.png");
    //ani->addFrame("animation03.png");
    //ani->start(0.5, -1);
    //ani->setSize(20);
    //ani->setPosition(100, 100);

    /********************
    DPW
    *******************/
    auto mapLayer = GameObject::create();
    this->addChild(mapLayer, "mapLayer");
    MapController::getInstance()->createMapFromFile("wdp2.txt", mapLayer);
    auto player = GameObject::create("bean.png");
    this->addChild(player, "player");
    player->addAbility(PlayerControl::create(player));
    player->setPosition(MapController::getInstance()->getXPositionInWorld(6), MapController::getInstance()->getYPositionInWorld(1));
    //player->setPosition(0, 0);
    player->setSize(10);
    //int flag = MapController::getInstance()->getObjectType(player);
    //if (flag)
    //	GameLog("collision");

    /********************
    LJD
    *******************/
    auto monster = GameObject::create("test.png");
    this->addChild(monster);
    monster->addAbility(MonsterAI::create(monster));
    auto monster2 = GameObject::create("test.png");
    this->addChild(monster2);
    monster2->addAbility(MonsterAI::create(monster2));
    auto monster3 = GameObject::create("test.png");
    this->addChild(monster3);
    monster3->addAbility(MonsterAI::create(monster3));

    return true;
}

void LevelOne::update() {
    Level::update();
    //if (count >= CONST_FPS * 600) {
    //    GameLog("LevelChange: LevelOne to LevelTwo");
    //    SystemController::getInstance()->setNextLevel(LevelTwo::create());
    //}
    //++count;
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
    if (count >= 300) {
        GameLog("LevelChange: LevelTwo to LevelThree");
        SystemController::getInstance()->setNextLevel(LevelThree::create());
    }
    ++count;
}

/********************
Level Three
*******************/
LevelThree::LevelThree() {}
LevelThree::~LevelThree() {}

bool LevelThree::init() {
    if (!Level::init()) {
        return false;
    }
    count = 0;

    auto go = GameObject::create("test.png");
    this->addChild(go);
    auto pos = go->getPosition();
    pos.x += 10;
    pos.y += 10;
    go->setPositionX(pos.x);
    go->setPositionY(pos.y);
    go->setDirection(3.14f);
    go->setVelocity(10, 10);


    return true;
}

void LevelThree::update() {
    Level::update();
    if (count >= 500) {
        SystemController::getInstance()->quitGame();
    }
    ++count;
}
