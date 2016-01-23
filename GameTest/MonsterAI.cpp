#include "MonsterAI.h"
#include"myLevel.h"
#include "PathGenerator.h"
#include "PlayerControl.h"

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

    //init maps info
    this->setMapInfo(MapController::getInstance()->mapInfo);
    //init monster and set status
    this->start = { 10,20 };
    this->curPos = this->nextPos = this->start;
    this->flag = 0;
    //add monster to map
    owner->setPositionX(MapController::getInstance()->getXPositionInWorld(this->start.posY));
    owner->setPositionY(MapController::getInstance()->getYPositionInWorld(this->start.posX));
    owner->setSize(10);
    //get player position
    this->player = owner->getParent()->getChildByName("player1");
    this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
    this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());

    return true;
}

void MonsterAI::update() {
    auto owner = this->getOwner();
    if ((player != NULL) &&
		(this->curPos.posX - MapController::getInstance()->getYPositionInMap(player->getPositionY()))*
		(this->curPos.posX - MapController::getInstance()->getYPositionInMap(player->getPositionY())) +
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player->getPositionX()))*
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player->getPositionX()))<REACH) {
        //this->player = NULL;

        int playerState = static_cast<PlayerControl*>(player->getAbility("PlayerControl"))->getPlayerState();
        if (playerState == 0) {
            SystemController::getInstance()->setNextLevel(LevelFail::create());
            return;
        }
        else if (playerState == 1) {
            static_cast<LevelOne*>(this->getOwner()->getParent())->minusMonster();
            owner->removeFromParent();
            return;
        }
    }
    if ((this->count % 400) == 0 && (this->player != NULL) && (this->flag == 0 || this->flag == 1)) {
        this->start = this->nextPos;
        this->path.Clear();
        //update player info 
        this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
        this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
        this->setMapInfo(MapController::getInstance()->mapInfo);
        //update path
        if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) &&
            (start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE) &&
            this->flag == 0) {
            PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
            this->flag = 1;
            //printf("\nflag = 1,BFS\n");
        }
        else {
            PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
            this->flag = 0;
            //printf("\nflag = 0,DFS\n");
        }
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
    }
    if ((this->count % 20) == 0 && this->flag != -1) {
        this->curPos = this->nextPos;
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
        if (this->curPos.posX == this->nextPos.posX&&
            this->curPos.posY == this->nextPos.posY) {
            if (this->player == NULL) {
                if (this->curPos.posX == 10 && this->curPos.posY == 20) {
                    this->flag = -1;
                }
                else {
                    this->start = this->nextPos;
                    this->path.Clear();
                    this->end = { 10,20 };
                    this->setMapInfo(MapController::getInstance()->mapInfo);
                    PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
                    //printf("flag = 2,BFS\n");
                    this->curPos = this->nextPos;
                    if (!this->path.Empty()) {
                        this->path.Pop(this->nextPos);
                    }
                    this->curPos = this->nextPos;
                    if (!this->path.Empty()) {
                        this->path.Pop(this->nextPos);
                    }
                    this->flag = 2;
                }
            }
            else{
                this->start = this->nextPos;
                this->path.Clear();
                this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
                this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
                this->setMapInfo(MapController::getInstance()->mapInfo);
                if (this->flag == 2) {
                    PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
                    this->flag++;
                    //printf("\nrestrat,DFS\n");
                }
                else {
                    PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
                    if (this->flag == 5) {
                        this->flag = 2;
                    }
                    //printf("\nrestrat,BFS\n");
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

//根据生成的路径行走
void MonsterAI::MoveByPath() {
    auto owner = this->getOwner();
    //到达终点
    if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
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

//设置地图信息
void MonsterAI::setMapInfo(int(*map)[40]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            this->map[i][j] = map[i][j];
        }
    }
}
