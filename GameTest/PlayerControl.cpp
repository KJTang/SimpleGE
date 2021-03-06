#include "PlayerControl.h"

#include "Animation.h"
#include"myLevel.h"
#include "MapController.h"
#include "SoundController.h"

const int WINNUM = 151;
const float SUPER_TIME = 5;

// 运动偏移
const int deltaX[5] = { 0, 0, 0, -1, 1 };
const int deltaY[5] = { 0, -1, 1, 0, 0 };
// 旋转
const float deltaRotate[5] = { 1.57, -1.57, 1.57, -3.14, 0 };

PlayerControl::PlayerControl() {}
PlayerControl::~PlayerControl() {}

PlayerControl* PlayerControl::create(GameObject* owner) {
    auto pAI = new PlayerControl();
    pAI->init(owner);
    return pAI;
}

bool PlayerControl::init(GameObject* owner) {
    if (!Ability::init(owner)) {
        return false;
    }
    this->setName("PlayerControl");
    _playerState = 0; // '0' for 'normal'
    count = 0;

    speed = 1.5;
    curDirection = nextDirection = 0;
    beans = 0;

    return true;
}

void PlayerControl::update() {
    // input event
    if (AEInputCheckCurr(VK_DOWN)) {
        onKeyDown(DOWN);
    } else if (AEInputCheckCurr(VK_UP)) {
        onKeyDown(UP);
    } else if (AEInputCheckCurr(VK_LEFT)) {
        onKeyDown(LEFT);
	} else if (AEInputCheckCurr(VK_RIGHT)) {
		onKeyDown(RIGHT);
	}

	//super status
	if (AEInputCheckCurr('C')) {
		_playerState = 1;
		static_cast<Animation*>(this->getOwner())->setSize(12.5);
		printf("who is you daddy....");
	}

    // move
    if (curDirection) {
        auto owner = this->getOwner();
        // 获取碰撞检测点
        float collisionX = 0, collisionY = 0;
        this->getCollisionPoint(curDirection, collisionX, collisionY);
        // 检测新方向上是否有障碍物
        int x = MapController::getInstance()->getXPositionInMap(collisionX + deltaX[curDirection] * speed);
        int y = MapController::getInstance()->getYPositionInMap(collisionY + deltaY[curDirection] * speed);
        if (MapController::getInstance()->getObjectType(x, y) != 1) {
            // 无障碍则向新方向运动
            owner->setPosition(owner->getPositionX() + deltaX[curDirection], owner->getPositionY() + deltaY[curDirection]);
        }
    }
    // next move
    if (nextDirection) {
        // 获取碰撞检测点
        float collisionX1 = 0, collisionX2 = 0, collisionY1 = 0, collisionY2 = 0;
        this->getCollisionPoint(nextDirection, collisionX1, collisionY1, collisionX2, collisionY2);
        // 检测新方向上是否有障碍物
        int x1 = MapController::getInstance()->getXPositionInMap(collisionX1 + deltaX[nextDirection] * speed);
        int y1 = MapController::getInstance()->getYPositionInMap(collisionY1 + deltaY[nextDirection] * speed);
        int x2 = MapController::getInstance()->getXPositionInMap(collisionX2 + deltaX[nextDirection] * speed);
        int y2 = MapController::getInstance()->getYPositionInMap(collisionY2 + deltaY[nextDirection] * speed);
        if (x1 == x2 && y1 == y2 &&
            MapController::getInstance()->getObjectType(x1, y1) != 1 &&
            MapController::getInstance()->getObjectType(x2, y2) != 1) {
            // 无障碍
            if (!isOppositeDirection(curDirection, nextDirection)) {
                // printf("turn: (%d, %d)  (%d, %d)\n", x1, y1, x1 - deltaX[nextDirection], y1 + deltaY[nextDirection]);
                this->getOwner()->setPositionX(MapController::getInstance()->getXPositionInWorld(x1 - deltaX[nextDirection]));
                this->getOwner()->setPositionY(MapController::getInstance()->getYPositionInWorld(y1 + deltaY[nextDirection]));
            }
            curDirection = nextDirection;
            nextDirection = 0;
            this->getOwner()->setDirection(deltaRotate[curDirection]);
        }
    }

    // eat beans
    this->eatBeans();
    if (_playerState == 1) {
        ++count;
        if (count >= CONST_FPS * SUPER_TIME) {
            count = 0;
            _playerState = 0;
            static_cast<Animation*>(this->getOwner())->setSize(10);
        }
    }
}

void PlayerControl::onKeyDown(int direction) {
    if (curDirection == direction) {
        return;
    }
    nextDirection = direction;
}

bool PlayerControl::isOppositeDirection(int direction1, int direction2) {
    switch (direction1) {
        case UP:
        {
            return direction2 == DOWN;
        }
        case DOWN:
        {
            return direction2 == UP;
        }
        case LEFT:
        {
            return direction2 == RIGHT;
        }
        case RIGHT:
        {
            return direction2 == LEFT;
        }
        default:
        {
            return false;
        }
    }
}

void PlayerControl::getCollisionPoint(int direction, float &x, float &y) {
    float curX = this->getOwner()->getPositionX();
    float curY = this->getOwner()->getPositionY();
    switch (direction) {
        case DOWN:
        {
            x = curX + 10;
            y = curY - 20;
            break;
        }
        case UP:
        {
            x = curX + 10;
            y = curY;
            break;
        }
        case LEFT:
        {
            x = curX;
            y = curY - 10;
            break;
        }
        case RIGHT:
        {
            x = curX + 20;
            y = curY - 10;
            break;
        }
        default:
        {
            x = curX;
            y = curY;
            break;
        }
    }
    //printf("get: (%.2f, %.2f)-(%.2f, %.2f)\n", curX, curY, x, y);
}

void PlayerControl::getCollisionPoint(int direction, float &x1, float &y1, float &x2, float &y2) {
    float curX = this->getOwner()->getPositionX();
    float curY = this->getOwner()->getPositionY();
    float delta = 1.5f;
    switch (direction) {
        case DOWN:
        {
            x1 = curX + delta;
            x2 = curX + 20 - delta;
            y1 = y2 = curY - 20;
            break;
        }
        case UP:
        {
            x1 = curX + delta;
            x2 = curX + 20 - delta;
            y1 = y2 = curY;
            break;
        }
        case LEFT:
        {
            x1 = x2 = curX;
            y1 = curY - delta;
            y2 = curY - 20 + delta;
            break;
        }
        case RIGHT:
        {
            x1 = x2 = curX + 20;
            y1 = curY - delta;
            y2 = curY - 20 + delta;
            break;
        }
        default:
        {
            x1 = x2 = curX;
            y1 = y2 = curY;
            break;
        }
    }
}

void PlayerControl::eatBeans() {
    auto owner = this->getOwner();
    int curX = MapController::getInstance()->getXPositionInMap(owner->getPositionX() + 10); // +10 偏移量
    int curY = MapController::getInstance()->getYPositionInMap(owner->getPositionY() - 10); // -10 偏移量
    char name[10];
    sprintf(name, "(%d, %d)", curX, curY);
    auto bean = owner->getParent()->getChildByName("mapLayer")->getChildByName("beanLayer")->getChildByName(name);
    if (bean) {
        //bean->setVisible(false);
        ++beans;
        bean->removeFromParent();
        SoundController::getInstance()->playMusic("music/eat.wav");
        if (MapController::getInstance()->getObjectType(curX, curY) == 3) { // 吃到大力豆
            _playerState = 1;
			count = 0;
            static_cast<Animation*>(this->getOwner())->setSize(12.5);
        }
    }
	if (beans==WINNUM) {
		SystemController::getInstance()->setNextLevel(LevelSuccess::create());	
    }
}