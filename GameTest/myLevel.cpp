#include "myLevel.h"
#include "myObject.h"
#include "myAbility.h"

/********************
Level One
*******************/

//size��Ϊ20

LevelOne::LevelOne() {}
LevelOne::~LevelOne() {}

bool LevelOne::init() {
    if (!Level::init()) {
        return false;
    }
    count = 0;

	auto layer = GameObject::create();
	this->addChild(layer);
	MapController::getInstance()->createMapFromFile("wdp.txt", layer);

    //go = GameObject::create("test.png");
    //this->addChild(go);
    //go->setPosition(-100, 0);
    //go->setSize(10);
    ////go->setActive(false);
    ////go->setVisible(false);
    //go->setVelocity(-30, 0);

	auto test = GameObject::create("test.png");
	this->addChild(test);
	test->addAbility(PlayerAI::create(test));
	test->setPosition(0, 0);
	test->setSize(10);
	int flag = MapController::getInstance()->getObjectType(test);
	if (flag)
		GameLog("collision");

    auto ani = Animation::create();
    this->addChild(ani);
    ani->addFrame("animation01.png");
    ani->addFrame("animation02.png");
    ani->addFrame("animation03.png");
    ani->start(0.5, -1);
    ani->setSize(10);
    ani->setPosition(0, 0);

    return true;
}

void LevelOne::update() {
    Level::update();
    if (count >= CONST_FPS * 30) {
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

    //auto go = GameObject::create("test.png");
    //this->addChild(go);
    //auto go2 = GameObject::create("test.png");
    //this->addChild(go2);
    //auto pos = go2->getPosition();
    //pos.y += 10;
    //go2->setPosition(pos);
    //go2->setDirection(3.14f);
    //go2->setVelocity(-30, 0);

    return true;
}

void LevelTwo::update() {
    Level::update();
    if (count >= 60) {
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

	/*auto go = GameObject::create("test.png");
	this->addChild(go);
	auto pos = go->getPosition();
	pos.x += 10;
	pos.y += 10;
	go->setPositionX(pos.x);
	go->setPositionY(pos.y);
	go->setDirection(3.14f);
	go->setVelocity(10, 10);*/


	return true;
}

void LevelThree::update() {
	Level::update();
	if (count >= 60) {
		SystemController::getInstance()->quitGame();
	}
	++count;
}
