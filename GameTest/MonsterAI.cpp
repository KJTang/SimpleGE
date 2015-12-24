#include "MonsterAI.h"
#include "PathGenerator.h"
#include <time.h>

/**************
MonsterAI
***************/
MonsterAI::MonsterAI() {}
MonsterAI::~MonsterAI() {}

MonsterAI* MonsterAI::create(GameObject* owner) {
    auto mAI = new MonsterAI();
    mAI->init(owner);
    return mAI;
}

bool MonsterAI::init(GameObject* owner) {
    if (!Ability::init(owner)) {
        return false;
    }
    this->setName("MonsterAI");
    this->getOwner()->setVelocity(0, 0);

    //初始化地图信息
    this->setMapInfo(MapController::getInstance()->mapInfo);
    //随机生成怪物坐标
    this->start = { 10,20 };
    this->curPos = this->nextPos = this->start;
    //将怪物加载到地图上
    owner->setPositionX(MapController::getInstance()->getXPositionInWorld(this->start.posY));
    owner->setPositionY(MapController::getInstance()->getYPositionInWorld(this->start.posX));
    owner->setSize(10);
    //获取player坐标
    this->player = owner->getParent()->getChildByName("player");
    this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
    this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());

    return true;
}

void MonsterAI::update() {
    auto owner = this->getOwner();
    if ((this->count % 200) == 0) {
        MPosType e;
        this->start = this->nextPos;
        while (!this->path.Empty()) {
            this->path.Pop(e);
        }
		if (player != NULL) {
			this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
			this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
		}
		else {
			this->end = { 10,20 };
		}
        this->setMapInfo(MapController::getInstance()->mapInfo);
        if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) &&
			(start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE)) {
            PathGenerator::getInstance()->WFSPath(this->map, this->start, this->end, this->path);
        }
        else {
            PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
        }
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
    }
	if ((player!=NULL)&&
		this->curPos.posX == MapController::getInstance()->getYPositionInMap(player->getPositionY()) &&
		this->curPos.posY == MapController::getInstance()->getXPositionInMap(player->getPositionX())) {
		owner->getParent()->removeChild(player);
		player = NULL;
	}
    if ((this->count % 20) == 0) {
        this->curPos = this->nextPos;
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
        if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
            if (this->curPos.posX != MapController::getInstance()->getYPositionInMap(player->getPositionY()) ||
                this->curPos.posY != MapController::getInstance()->getXPositionInMap(player->getPositionX())) {
                MPosType e;
                this->start = this->nextPos;
                while (!this->path.Empty()) {
                    this->path.Pop(e);
                }
                this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
                this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
                this->setMapInfo(MapController::getInstance()->mapInfo);
                if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) && (start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE)) {
                    PathGenerator::getInstance()->WFSPath(this->map, this->start, this->end, this->path);
                    printf("Updata Path By BFS\n");
                    printf("start(%d,%d)\n", start.posX, start.posY);
                    printf("end(%d,%d)\n", end.posX, end.posY);
                }
                else {
                    PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
                    printf("Updata Path By DFS\n");
                    printf("start(%d,%d)\n", start.posX, start.posY);
                    printf("end(%d,%d)\n", end.posX, end.posY);
                }
                if (!this->path.Empty()) {
                    this->path.Pop(this->nextPos);
                }
                this->curPos = this->nextPos;
                if (!this->path.Empty()) {
                    this->path.Pop(this->nextPos);
                }
            }
        }
    }
    MoveByPath();
    this->count++;
}

void MonsterAI::MoveByPath() {
    auto owner = this->getOwner();
    //到达终点
    if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
        if (this->curPos.posX != MapController::getInstance()->getYPositionInMap(player->getPositionY()) ||
            this->curPos.posY != MapController::getInstance()->getXPositionInMap(player->getPositionX())) {
            MPosType e;
            this->start = this->nextPos;
            while (!this->path.Empty()) {
                this->path.Pop(e);
            }
            this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
            this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
            this->setMapInfo(MapController::getInstance()->mapInfo);
            if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) && (start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE)) {
                PathGenerator::getInstance()->WFSPath(this->map, this->start, this->end, this->path);
                printf("Updata Path By BFS\n");
                printf("start(%d,%d)\n", start.posX, start.posY);
                printf("end(%d,%d)\n", end.posX, end.posY);
            }
            else {
                PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
                printf("Updata Path By DFS\n");
                printf("start(%d,%d)\n", start.posX, start.posY);
                printf("end(%d,%d)\n", end.posX, end.posY);
            }
            if (!this->path.Empty()) {
                this->path.Pop(this->nextPos);
            }
            this->curPos = this->nextPos;
            if (!this->path.Empty()) {
                this->path.Pop(this->nextPos);
            }
        }
        return;
    }
    //水平移动
    else if (this->curPos.posX == this->nextPos.posX) {
        if (this->curPos.posY < this->nextPos.posY) {
            owner->setPositionX(owner->getPositionX() + 1);		//向右运动
        }
        else {
            owner->setPositionX(owner->getPositionX() - 1);		//向左运动
        }
    }
    //垂直移动
    else if (this->curPos.posY == this->nextPos.posY) {
        if (this->curPos.posX < this->nextPos.posX) {
            owner->setPositionY(owner->getPositionY() - 1);		//向下运动
        }
        else {
            owner->setPositionY(owner->getPositionY() + 1);		//向上运动
        }
    }
}

void MonsterAI::setMapInfo(int(*map)[40]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            this->map[i][j] = map[i][j];
        }
    }
}
