#include "myAbility.h"

#include "MapController.h"

/**************
PlayerAI
***************/
const int deltaX[5] = { 0, 0, 0, -1, 1 };
const int deltaY[5] = { 0, -1, 1, 0, 0 };

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
    speed = 1;

    return true;
}

void PlayerControl::update() {
    // input event
    if (AEInputCheckCurr(VK_DOWN)) {
        onKeyDown(1);
    } else if (AEInputCheckCurr(VK_UP)) {
        onKeyDown(2);
    } else if (AEInputCheckCurr(VK_LEFT)) {
        onKeyDown(3);
    } else if (AEInputCheckCurr(VK_RIGHT)) {
        onKeyDown(4);
    }
    // move
    if (command.size()) {
        auto owner = this->getOwner();
        auto desX = (command.front().second.x);
        auto desY = (command.front().second.y);
        if (owner->getPositionX() != desX || owner->getPositionY() != desY) {
            owner->setPosition(owner->getPositionX() + deltaX[command.front().first] * speed, owner->getPositionY() + deltaY[command.front().first] * speed);
        }
        else {
            command.pop();
            printf("After pop :%d\n", command.size());
        }
    }
}

void PlayerControl::onKeyDown(int dirct) {
    if (command.size() >= 2) {
        return;
    }

    if (command.size() == 0) {
        // 计算出目的地的地图坐标
        int posx = MapController::getInstance()->getXPositionInMap(this->getOwner()->getPositionX());
        int posy = MapController::getInstance()->getYPositionInMap(this->getOwner()->getPositionY());
        while (MapController::getInstance()->getObjectType(posx, posy) != 1) {
            posx += deltaX[dirct];
            posy += (-deltaY[dirct]);
        }
        posx -= deltaX[dirct];
        posy -= (-deltaY[dirct]);
        // 计算出目的地的世界坐标
        float destinationX = MapController::getInstance()->getXPositionInWorld(posx);
        float destinationY = MapController::getInstance()->getYPositionInWorld(posy);
        // 添加到命令队列
        Point dest = { destinationX, destinationY };
        command.push(std::make_pair(dirct, dest));
        printf("des: %d, %d; size: %d\n", posx, posy, command.size());
    }
    else if (command.size() == 1) {
        // 如果与前一个命令方向一致则返回
        if (dirct == command.front().first) {
            return;
        }
        printf("fasdfdsaf\n");
        // 计算出目的地的地图坐标
        int posx = MapController::getInstance()->getXPositionInMap(command.front().second.x);
        int posy = MapController::getInstance()->getYPositionInMap(command.front().second.y);
        printf("sec: %d, %d", posx, posy);
        while (MapController::getInstance()->getObjectType(posx, posy) != 1) {
            posx += deltaX[dirct];
            posy += (-deltaY[dirct]);
        }
        posx -= deltaX[dirct];
        posy -= (-deltaY[dirct]);
        // 计算出目的地的世界坐标
        float destinationX = MapController::getInstance()->getXPositionInWorld(posx);
        float destinationY = MapController::getInstance()->getYPositionInWorld(posy);
        // 添加到命令队列
        Point dest = { destinationX, destinationY };
        command.push(std::make_pair(dirct, dest));
        printf("des: %d, %d; size: %d\n", posx, posy, command.size());
    }

}