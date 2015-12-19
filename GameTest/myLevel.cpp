#include "myLevel.h"
#include "myObject.h"
#include "myAbility.h"
#include "MonsterAI.h"
#include "MapController.h"

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
	auto layer = GameObject::create();
	this->addChild(layer);
	MapController::getInstance()->createMapFromFile("wdp.txt", layer);
	auto player = GameObject::create("test.png");
	this->addChild(player);
	player->addAbility(PlayerControl::create(player));
	player->setPosition(0, 0);
	player->setSize(10);
	int flag = MapController::getInstance()->getObjectType(player);
	if (flag)
		GameLog("collision");

	/********************
	LJD
	*******************/
	auto monster = GameObject::create("test.png");
	this->addChild(monster);
	monster->addAbility(MonsterAI::create(monster));

    return true;
}

void LevelOne::update() {
    Level::update();
    if (count >= CONST_FPS * 600) {
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
