#include "myLevel.h"
#include "myObject.h"
#include "PlayerControl.h"
#include "PlayerControl2.h"
#include "PlayerControl3.h"
#include "MonsterAI.h"
#include "MonsterAI2.h"
#include "MapController.h"

/********************
WQY
*********************/
bool LevelZero::init() {
    if (!Level::init())
        return false;

    SoundController::getInstance()->pauseAllMusic();

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

    go = GameObject::create("picture/level/cursor.png");
    go->setPositionX(X0);
    go->setPositionY(Y0+dY);
    go->setSize(SIZE);
    this->addChild(go);

    return true;
}

void LevelZero::update() {
    Level::update();
    if (AEInputCheckCurr(VK_RETURN))
    {
        if (count == 1)
        {
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
        pos.y -= 2*dY;
        go->setPosition(pos);
    }
    else if (AEInputCheckCurr(VK_UP) && (count == 2 || count == 6))
    {
        count /= 2;
        auto pos = go->getPosition();
        pos.y += 2*dY;
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

    // load sound
    SoundController::getInstance()->loadMusic("music/eat.wav");
    SoundController::getInstance()->loadMusic("music/bgm.mp3", [](void *data) {memset(data, 1, sizeof(bool)); }, (void*)(&quit));

    return true;
}

void LoadingLevel::update() {
    if (count++ >= 60) {
        if (quit) {
            SystemController::getInstance()->setNextLevel(LevelZero::create());
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
    count = CONST_FPS * 3;

    SoundController::getInstance()->playMusic("music/bgm.mp3");

    /********************
    DPW
    *******************/
    auto mapLayer = GameObject::create();
    this->addChild(mapLayer, "mapLayer");
    MapController::getInstance()->createMapFromFile("map/map02.txt", mapLayer);
    auto player = Animation::create();
    this->addChild(player, "player1");
    player->addFrame("picture/player/player1.png");
    player->addFrame("picture/player/player2.png");
    player->start(0.1, -1);
    player->addAbility(PlayerControl::create(player));
    player->setPosition(MapController::getInstance()->getXPositionInWorld(8), MapController::getInstance()->getYPositionInWorld(5));
    player->setSize(10);

    monsterCount = 0;

    return true;
}

void LevelOne::update() {
    Level::update();
    if (count >= CONST_FPS * 5 && monsterCount < 3) {
        createMonster();
        count = 0;
    }
	if (AEInputCheckCurr(VK_ESCAPE))
	{
		SystemController::getInstance()->setNextLevel(LevelZero::create());
	}
    ++count;
}

void LevelOne::createMonster() {
    auto monster = Animation::create();
    this->addChild(monster);
    monster->addFrame("picture/monster/fire1.png");
    monster->addFrame("picture/monster/fire2.png");
    monster->start(0.1, -1);
    monster->addAbility(MonsterAI::create(monster));

    ++monsterCount;
}

void LevelOne::minusMonster() {
    --monsterCount;
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
	count = -CONST_FPS;

	SoundController::getInstance()->playMusic("music/bgm.mp3");

	/********************
	DPW
	*******************/
	auto mapLayer = GameObject::create();
	this->addChild(mapLayer, "mapLayer");
	MapController::getInstance()->createMapFromFile("map/map01.txt", mapLayer);
	introduction = GameObject::create("picture/level/Introduction2.png");
	this->addChild(introduction);
	introduction->setPositionX(0.0);
	introduction->setPositionY(0.0);
	introduction->setSize(BGSIZE);

	//createMonster();

	monsterCount = 0;

	return true;
}

void LevelTwo::update() {
	Level::update();
	if (count == -1 || AEInputCheckCurr(VK_SPACE))
	{
		introduction->setVisible(false);
		auto player1 = Animation::create();
		this->addChild(player1, "player1");
		player1->addFrame("picture/player/player1.png");
		player1->addFrame("picture/player/player2.png");
		player1->start(0.1, -1);
		player1->addAbility(PlayerControl3::create(player1));
		player1->setPosition(MapController::getInstance()->getXPositionInWorld(6), MapController::getInstance()->getYPositionInWorld(3));
		player1->setSize(10);

		auto player2 = Animation::create();
		this->addChild(player2, "player2");
		player2->addFrame("picture/player/player3.png");
		player2->addFrame("picture/player/player4.png");
		player2->start(0.1, -1);
		player2->addAbility(PlayerControl2::create(player2));
		player2->setPosition(MapController::getInstance()->getXPositionInWorld(33), MapController::getInstance()->getYPositionInWorld(16));
		player2->setSize(10);
		count = CONST_FPS * 3;
	}
	else if (count >= CONST_FPS * 5 && monsterCount < 5) {
		createMonster();
		count = 0;
	}
	if (AEInputCheckCurr(VK_ESCAPE))
	{
		SystemController::getInstance()->setNextLevel(LevelZero::create());
	}
	++count;
}

void LevelTwo::createMonster() {
	auto monster = Animation::create();
	this->addChild(monster);
	monster->addFrame("picture/monster/fire1.png");
	monster->addFrame("picture/monster/fire2.png");
	monster->start(0.1, -1);
	monster->addAbility(MonsterAI2::create(monster));

	++monsterCount;
}

void LevelTwo::minusMonster() {
	--monsterCount;
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

    auto go = GameObject::create("picture/level/cursor.png");
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

    auto subMenu1 = GameObject::create("picture/level/continueGame.png");
    subMenu1->setName("backGame");
    subMenu1->setPositionX(280);
    subMenu1->setPositionY(30);
    subMenu1->setSize(SIZE);
    this->addChild(subMenu1);
    choice.push_back(subMenu1);

    auto subMenu2 = GameObject::create("picture/level/exitGame.png");
    subMenu2->setName("exitGame");
    subMenu2->setPositionX(280);
    subMenu2->setPositionY(-30.0);
    subMenu2->setSize(SIZE);
    this->addChild(subMenu2);
    choice.push_back(subMenu2);

    auto cursor = GameObject::create("picture/level/cursor.png");
    this->addChild(cursor);
    cursor->setPositionX(280);
    cursor->setPositionY(30.0);
    cursor->setSize(SIZE);
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
        if (posY <= -30) {
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
            SystemController::getInstance()->setNextLevel(LevelOne::create());
        else if (myName == "exitGame") {
            SystemController::getInstance()->setNextLevel(LevelZero::create());
        }
    }
}

/************
LevelFail
**************/
bool LevelFail::init() {
    if (!Level::init()) {
        return false;
    }

    auto mainManu = GameObject::create("picture/level/Fail.png");
    this->addChild(mainManu);
    mainManu->setPositionX(0.0);
    mainManu->setPositionY(0.0);
    mainManu->setSize(BGSIZE);

    auto subMenu1 = GameObject::create("picture/level/continueGame.png");
    subMenu1->setName("backGame");
    subMenu1->setPositionX(280);
    subMenu1->setPositionY(30);
    subMenu1->setSize(SIZE);
    this->addChild(subMenu1);
    choice.push_back(subMenu1);

    auto subMenu2 = GameObject::create("picture/level/exitGame.png");
    subMenu2->setName("exitGame");
    subMenu2->setPositionX(280);
    subMenu2->setPositionY(-30);
    subMenu2->setSize(SIZE);
    this->addChild(subMenu2);
    choice.push_back(subMenu2);

    auto cursor = GameObject::create("picture/level/cursor.png");
    this->addChild(cursor);
    cursor->setPositionX(280);
    cursor->setPositionY(30);
    cursor->setSize(SIZE);
    cursor->setName("cursor");

    return true;
}

void LevelFail::update() {
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
        if (posY <= -30) {
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
            SystemController::getInstance()->setNextLevel(LevelZero::create());
        }
    }
}

/************
LevelFail2
**************/
bool LevelFail2::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/Fail.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/continueGame.png");
	subMenu1->setName("backGame");
	subMenu1->setPositionX(280);
	subMenu1->setPositionY(30);
	subMenu1->setSize(SIZE);
	this->addChild(subMenu1);
	choice.push_back(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/exitGame.png");
	subMenu2->setName("exitGame");
	subMenu2->setPositionX(280);
	subMenu2->setPositionY(-30);
	subMenu2->setSize(SIZE);
	this->addChild(subMenu2);
	choice.push_back(subMenu2);

	auto cursor = GameObject::create("picture/level/cursor.png");
	this->addChild(cursor);
	cursor->setPositionX(280);
	cursor->setPositionY(30);
	cursor->setSize(SIZE);
	cursor->setName("cursor");

	return true;
}

void LevelFail2::update() {
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
		if (posY <= -30) {
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
			SystemController::getInstance()->setNextLevel(LevelTwo::create());
		else if (myName == "exitGame") {
			SystemController::getInstance()->setNextLevel(LevelZero::create());
		}
	}
}

/************
LevelP1win
**************/
bool LevelP1win::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/Success3.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/continueGame.png");
	subMenu1->setName("backGame");
	subMenu1->setPositionX(200);
	subMenu1->setPositionY(-30);
	subMenu1->setSize(SIZE);
	this->addChild(subMenu1);
	choice.push_back(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/exitGame.png");
	subMenu2->setName("exitGame");
	subMenu2->setPositionX(200);
	subMenu2->setPositionY(-72);
	subMenu2->setSize(SIZE);
	this->addChild(subMenu2);
	choice.push_back(subMenu2);

	auto cursor = GameObject::create("picture/level/cursor.png");
	this->addChild(cursor);
	cursor->setPositionX(200);
	cursor->setPositionY(-30);
	cursor->setSize(SIZE);
	cursor->setName("cursor");

	return true;
}

void LevelP1win::update() {
	Level::update();

	auto owner = this->getChildByName("cursor");
	auto posY = owner->getPositionY();

	if (AEInputCheckCurr(VK_UP)) {
		if (posY >= -30) {
			posY = -30;
		}
		else {
			posY += 42;
			owner->setPositionY(posY);
		}
	}
	else if (AEInputCheckCurr(VK_DOWN))
	{
		if (posY <= -72) {
			;
		}
		else {
			posY -= 42;
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
			SystemController::getInstance()->setNextLevel(LevelTwo::create());
		else if (myName == "exitGame") {
			SystemController::getInstance()->setNextLevel(LevelZero::create());
		}
	}
}

/************
LevelP2win
**************/
bool LevelP2win::init() {
	if (!Level::init()) {
		return false;
	}

	auto mainManu = GameObject::create("picture/level/Success2.png");
	this->addChild(mainManu);
	mainManu->setPositionX(0.0);
	mainManu->setPositionY(0.0);
	mainManu->setSize(BGSIZE);

	auto subMenu1 = GameObject::create("picture/level/continueGame.png");
	subMenu1->setName("backGame");
	subMenu1->setPositionX(200);
	subMenu1->setPositionY(-30);
	subMenu1->setSize(SIZE);
	this->addChild(subMenu1);
	choice.push_back(subMenu1);

	auto subMenu2 = GameObject::create("picture/level/exitGame.png");
	subMenu2->setName("exitGame");
	subMenu2->setPositionX(200);
	subMenu2->setPositionY(-72);
	subMenu2->setSize(SIZE);
	this->addChild(subMenu2);
	choice.push_back(subMenu2);

	auto cursor = GameObject::create("picture/level/cursor.png");
	this->addChild(cursor);
	cursor->setPositionX(200);
	cursor->setPositionY(-30);
	cursor->setSize(SIZE);
	cursor->setName("cursor");

	return true;
}

void LevelP2win::update() {
	Level::update();

	auto owner = this->getChildByName("cursor");
	auto posY = owner->getPositionY();

	if (AEInputCheckCurr(VK_UP)) {
		if (posY >= -30) {
			posY = -30;
		}
		else {
			posY += 42;
			owner->setPositionY(posY);
		}
	}
	else if (AEInputCheckCurr(VK_DOWN))
	{
		if (posY <= -72) {
			;
		}
		else {
			posY -= 42;
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
			SystemController::getInstance()->setNextLevel(LevelTwo::create());
		else if (myName == "exitGame") {
			SystemController::getInstance()->setNextLevel(LevelZero::create());
		}
	}
}
