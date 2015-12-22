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
    curDirection = nextDirection = 0;

    //float cx = this->getOwner()->getPositionX();
    //float cy = this->getOwner()->getPositionY();
    //int x = MapController::getInstance()->getXPositionInMap(cx);
    //int y = MapController::getInstance()->getYPositionInMap(cy);
    //float fx = MapController::getInstance()->getXPositionInWorld(x);
    //float fy = MapController::getInstance()->getYPositionInWorld(y);
    //printf("test: map(%d, %d), cur(%f, %f), trans(%d, %d)\n", x, y, cx, cy, fx, fy);

    return true;
}

void PlayerControl::update() {
    // input event
    if (AEInputCheckCurr(VK_DOWN)) {
        onKeyDown(1);
        //curDirection = 1;
    } else if (AEInputCheckCurr(VK_UP)) {
        onKeyDown(2);
        //curDirection = 2;
    } else if (AEInputCheckCurr(VK_LEFT)) {
        onKeyDown(3);
        //curDirection = 3;
    } else if (AEInputCheckCurr(VK_RIGHT)) {
        onKeyDown(4);
        //curDirection = 4;
    }
    // move
    //auto owner = this->getOwner();

    //float fx = this->getOwner()->getPositionX();
    //float fy = this->getOwner()->getPositionY();
    //if (curDirection == 1) {
    //    fy -= 20;
    //}
    //else if (curDirection == 4) {
    //    fx += 20;
    //}
    //int x = MapController::getInstance()->getXPositionInMap(fx);
    //int y = MapController::getInstance()->getYPositionInMap(fy);

    //if (MapController::getInstance()->getObjectType(x, y) != 1) {
    //    owner->setPosition(owner->getPositionX() + deltaX[curDirection] * speed, owner->getPositionY() + deltaY[curDirection] * speed);
    //}
    //else {
    //    float originx = MapController::getInstance()->getXPositionInWorld(x + deltaX[curDirection]);
    //    float originy = 
    //    owner->setPosition(owner->getPositionX() - deltaX[curDirection] * speed, owner->getPositionY() - deltaY[curDirection] * speed);
    //}

    if (command.size()) {
        auto owner = this->getOwner();
        auto desX = (command.front().second.x);
        auto desY = (command.front().second.y);

        if (owner->getPositionX() == desX && owner->getPositionY() == desY) {
        //if (owner->getPositionX() >= desX - 0.0 && owner->getPositionX() <= desX + 0.0 &&
            //owner->getPositionY() >= desY - 0.0 && owner->getPositionY() <= desY + 0.0) {
            //owner->setPosition(owner->getPositionX() - deltaX[command.front().first] * speed, owner->getPositionY() - deltaY[command.front().first] * speed);
            command.pop();
            printf("After pop :%d\n", command.size());
        }
        else {
            owner->setPosition(owner->getPositionX() + deltaX[command.front().first] * speed, owner->getPositionY() + deltaY[command.front().first] * speed);
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
        // 计算出目的地的地图坐标
        // 当前地图坐标
        int posx = MapController::getInstance()->getXPositionInMap(this->getOwner()->getPositionX());
        int posy = MapController::getInstance()->getYPositionInMap(this->getOwner()->getPositionY());
        //printf("cur %d, %d\n", posx, posy);
        // 上一个命令的目的目标
        int desx = MapController::getInstance()->getXPositionInMap(command.front().second.x);
        int desy = MapController::getInstance()->getYPositionInMap(command.front().second.y);
        while (!(posx == desx && posy == desy)) {
            //printf("------%d, %d\n", posx, posy);
            if (MapController::getInstance()->getObjectType(posx + deltaX[dirct], posy - deltaY[dirct]) != 1) {
                // 修改上一个命令的目的地
                command.front().second.x = MapController::getInstance()->getXPositionInWorld(posx);
                command.front().second.y = MapController::getInstance()->getYPositionInWorld(posy);
                printf("modify: %d, %d\n", posx, posy);
                break;
            }
            posx += deltaX[command.front().first];
            posy += (-deltaY[command.front().first]);
        }
        // 如果无法改变方向则不添加新命令
        if (posx == desx && posy == desy && MapController::getInstance()->getObjectType(posx + deltaX[dirct], posy - deltaY[dirct])==1) {
            return;
        }
        // 添加新命令
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