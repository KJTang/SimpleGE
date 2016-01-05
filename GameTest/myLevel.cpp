#include "myLevel.h"
#include "myObject.h"
#include "PlayerControl.h"
#include "MonsterAI.h"
#include "MapController.h"

/********************
<<<<<<< HEAD
WQY
*********************/
bool LevelZero::init() {
	if (!Level::init())
		return false;

	count = 1;
	auto mainManu = GameObject::create("picture/level/GameMenu.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/singleGame.png");
	subMenu1->setPositionX(X0);
	subMenu1->setPositionY(Y0+dY);
	subMenu1->setSize(SIZE);
	this->addChild(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/doubleGame.png");
	subMenu2->setPositionX(X0 + dX);
	subMenu2->setPositionY(Y0+dY);
	subMenu2->setSize(SIZE);
	this->addChild(subMenu2);

	auto subMenu3 = GameObject::create("picture/level/aboutUs.png");
	subMenu3->setPositionX(X0);
	subMenu3->setPositionY(Y0-dY);
	subMenu3->setSize(SIZE);
	this->addChild(subMenu3);

	auto subMenu4 = GameObject::create("picture/level/exitGame.png");
	subMenu4->setPositionX(X0 + dX);
	subMenu4->setPositionY(Y0-dY);
	subMenu4->setSize(SIZE);
	this->addChild(subMenu4);

	go = GameObject::create("test.png");
	go->setPositionX(X0);
	go->setPositionY(dY);
	this->addChild(go);

	return true;
}

void LevelZero::update() {
	Level::update();
	if (AEInputCheckCurr(VK_RETURN))
	{
		if (count == 1)
		{
			GameLog("LevelChange: LevelZreoto LevelOne");
			SystemController::getInstance()->setNextLevel(LevelGameInfo::create());
		}
		else if (count == 3)
		{
			SystemController::getInstance()->setNextLevel(LevelTwo::create());
		}
		else if (count == 2)
		{
			SystemController::getInstance()->setNextLevel(LevelTeamInfo::create());
		}
		else if (count == 6)
		{
			SystemController::getInstance()->quitGame();
		}
	}
	else if (AEInputCheckCurr(VK_DOWN) && (count == 1 || count == 3))
	{
		count *= 2;
		auto pos = go->getPosition();
		pos.y = -dY;
		go->setPosition(pos);
	}
	else if (AEInputCheckCurr(VK_UP) && (count == 2 || count == 6))
	{
		count /= 2;
		auto pos = go->getPosition();
		pos.y = dY;
		go->setPosition(pos);
	}
	else if (AEInputCheckCurr(VK_RIGHT) && (count == 1 || count == 2))
	{
		count *= 3;
		auto pos = go->getPosition();
		pos.x += dX;
		go->setPosition(pos);
	}
	else if (AEInputCheckCurr(VK_LEFT) && (count == 3 || count == 6))
	{
		count /= 3;
		auto pos = go->getPosition();
		pos.x -= dX;
		go->setPosition(pos);
	}
}

/********************
=======
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
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

    //SoundController::getInstance()->playMusic("music/test.mp3");

    /********************
    DPW
    *******************/
    auto mapLayer = GameObject::create();
    this->addChild(mapLayer, "mapLayer");
    MapController::getInstance()->createMapFromFile("wdp2.txt", mapLayer);
    auto player = Animation::create();
    this->addChild(player, "player");
    player->addFrame("picture/player/player1.png");
    player->addFrame("picture/player/player2.png");
    player->start(0.5, -1);
    player->addAbility(PlayerControl::create(player));
    player->setPosition(MapController::getInstance()->getXPositionInWorld(6), MapController::getInstance()->getYPositionInWorld(1));
    player->setSize(10);

    /********************
    LJD
    *******************/
<<<<<<< HEAD
	/*auto monester1 = Animation::create();
	this->addChild(monester1, "monester1");
	monester1->addFrame("picture/player/fire1.png");
	monester1->addFrame("picture/player/fire2.png");
	monester1->addAbility(MonsterAI::create(monester1));

	auto monester2 = Animation::create();
	this->addChild(monester2, "monester2");
	monester2->addFrame("picture/player/fire1.png");
	monester2->addFrame("picture/player/fire2.png");
	monester2->addAbility(MonsterAI::create(monester2));

	auto monester3 = Animation::create();
	this->addChild(monester3, "monester1");
	monester3->addFrame("picture/player/fire1.png");
	monester3->addFrame("picture/player/fire2.png");
	monester3->addAbility(MonsterAI::create(monester3));*/
    auto monster = GameObject::create("picture/player/fire1.png");
    this->addChild(monster);
    monster->addAbility(MonsterAI::create(monster));
    auto monster2 = GameObject::create("picture/player/fire2.png");
    this->addChild(monster2);
    monster2->addAbility(MonsterAI::create(monster2));
    auto monster3 = GameObject::create("picture/player/fire2.png");
=======
    auto monster = GameObject::create("test.png");
    this->addChild(monster);
    monster->addAbility(MonsterAI::create(monster));
    auto monster2 = GameObject::create("test.png");
    this->addChild(monster2);
    monster2->addAbility(MonsterAI::create(monster2));
    auto monster3 = GameObject::create("test.png");
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
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
<<<<<<< HEAD

/*************
WDP
**************/
/*********
LevelGameInfo
********/
LevelGameInfo::LevelGameInfo(){}
LevelGameInfo::~LevelGameInfo(){}

bool LevelGameInfo::init() {
	if (!Level::init()) {
		return false;
	}

	count = 0;
	auto mainManu = GameObject::create("picture/level/GameInfo.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	return true;
}

void LevelGameInfo::update() {
	Level::update();
	
	if (AEInputCheckCurr(VK_SPACE))
	{
		SystemController::getInstance()->setNextLevel(LevelOne::create());
	}
	count++;
}

/************
LevelTeamInfo
**************/
bool LevelTeamInfo::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/teamInfo.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	return true;
}

void LevelTeamInfo::update() {
	Level::update();
	if (AEInputCheckCurr(VK_ESCAPE))
	{
		SystemController::getInstance()->setNextLevel(LevelZero::create());
	}
}

/************
LevelSuccess
**************/
bool LevelSuccess::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/success1.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/backGame.png");
	subMenu1->setName("backGame");
	subMenu1->setPositionX(250);
	subMenu1->setPositionY(0);
	subMenu1->setSize(40);
	this->addChild(subMenu1);
	choice.push_back(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/exitGame.png");
	subMenu2->setName("exitGame");
	subMenu2->setPositionX(250);
	subMenu2->setPositionY(-60.0);
	subMenu2->setSize(40);
	this->addChild(subMenu2);
	choice.push_back(subMenu2);

	auto cursor = GameObject::create("test.png");
	this->addChild(cursor);
	cursor->setPositionX(250);
	cursor->setPositionY(0.0);
	cursor->setSize(10);
	cursor->setName("cursor");

	return true;

}

void LevelSuccess::update() {
	Level::update();

	auto owner = this->getChildByName("cursor");
	auto posY = owner->getPositionY();

	if (AEInputCheckCurr(VK_UP)) {
		if (posY >= 0) {
			posY = 0;
		}
		else {
			posY += 60;
			owner->setPositionY(posY);
		}
	}
	else if (AEInputCheckCurr(VK_DOWN))
	{
		if (posY <= -60) {
			posY = -60;
		}
		else {
			posY -= 60;
			owner->setPositionY(posY);
		}
	}

	else if (AEInputCheckCurr(VK_SPACE))
	{
		GameObject *choLevel = NULL;
		for (auto it = choice.begin(); it != choice.end(); ++it) {
			if ((*it)->getPositionY() == posY) {
				choLevel = (*it);
			}
		}
		std::string myName = choLevel->getName();
		if (myName == "backGame")
			SystemController::getInstance()->setNextLevel(LevelZero::create());
		else if (myName == "exitGame") {
			SystemController::getInstance()->quitGame();
		}
	}
}

/************
LevelFaile
**************/
bool LevelFaile::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/Faile.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/backGame.png");
	subMenu1->setName("backGame");
	subMenu1->setPositionX(250);
	subMenu1->setPositionY(0);
	subMenu1->setSize(40);
	this->addChild(subMenu1);
	choice.push_back(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/exitGame.png");
	subMenu2->setName("exitGame");
	subMenu2->setPositionX(250);
	subMenu2->setPositionY(-60);
	subMenu2->setSize(40);
	this->addChild(subMenu2);
	choice.push_back(subMenu2);

	auto cursor = GameObject::create("test.png");
	this->addChild(cursor);
	cursor->setPositionX(250);
	cursor->setPositionY(0);
	cursor->setSize(10);
	cursor->setName("cursor");

	return true;

}

void LevelFaile::update() {
	Level::update();

	auto owner = this->getChildByName("cursor");
	auto posY = owner->getPositionY();

	if (AEInputCheckCurr(VK_UP)) {
		if (posY >= 0) {
			posY = 0;
		}
		else {
			posY += 60;
			owner->setPositionY(posY);
		}
	}
	else if (AEInputCheckCurr(VK_DOWN))
	{
		if (posY <= -60) {
			;
		}
		else {
			posY -= 60;
			owner->setPositionY(posY);
		}
	}

	else if (AEInputCheckCurr(VK_SPACE))
	{
		GameObject *choLevel = NULL;
		for (auto it = choice.begin(); it != choice.end(); ++it) {
			if ((*it)->getPositionY() == posY) {
				choLevel = (*it);
			}
		}
		std::string myName = choLevel->getName();
		if (myName == "backGame")
			SystemController::getInstance()->setNextLevel(LevelOne::create());
		else if (myName == "exitGame") {
			SystemController::getInstance()->quitGame();
		}
	}
}
=======
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
