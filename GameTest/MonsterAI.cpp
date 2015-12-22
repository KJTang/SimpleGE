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
	GameObject* player = owner->getParent()->getChildByName("player");
	this->end.posX = MapController::getInstance()->getXPositionInMap(player->getPositionX());
	this->end.posY = MapController::getInstance()->getYPositionInMap(player->getPositionY());
	//MapController::getInstance()->RndCreateEmptyPosInMap(this->end);
	//设置刷新路径的时间间隔
	srand(time(0));
	this->randtime = (rand() % 20 + 1)*100;

	return true;
}

void MonsterAI::update() {
	auto owner = this->getOwner();
	if ((this->count % this->randtime) == 0) {
		this->randtime = (rand() % 10 + 1) * 100;
		MPosType e;
		this->start = this->nextPos;
		while (!this->path.Empty()) {
			this->path.Pop(e);
		}
		GameObject* player = owner->getParent()->getChildByName("player");
		this->end.posX = MapController::getInstance()->getXPositionInMap(player->getPositionX());
		this->end.posY = MapController::getInstance()->getYPositionInMap(player->getPositionY());
		this->setMapInfo(MapController::getInstance()->mapInfo);
		if ((start.posX - end.posX<=5&&start.posX - end.posX>=-5)&& (start.posY - end.posY <= 5 && start.posY - end.posY >= -5)) {
			PathGenerator::getInstance()->WFSPath(this->map, this->start, this->end, this->path);
			printf("Updata Path By WFS\n");
			printf("start(%d,%d)\n", start.posX, start.posY);
			printf("end(%d,%d)\n", end.posX, end.posY);
		}
		else {
			PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
			printf("Updata Path By DFS\n");
			printf("start(%d,%d)\n", start.posX, start.posY);
			printf("end(%d,%d)\n", end.posX, end.posY);
		}
		if (!this->path.Empty()) {
			this->path.Pop(this->nextPos);
		}
	}
	if ((this->count % 20) == 0) {
		//if (this->curPos.posX == this->end.posX&&this->curPos.posY == this->end.posY) {
		//	owner->getParent()->removeChild(owner->getParent()->getChildByName("player"));
		//}
		this->curPos = this->nextPos;
		if (!this->path.Empty()) {
			this->path.Pop(this->nextPos);
		}
	}
	MoveByPath();
	this->count++;
}

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

void MonsterAI::setMapInfo(int (*map)[40]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			this->map[i][j] = map[i][j];
		}
	}
}
