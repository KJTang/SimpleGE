#include "MonsterAI.h"
#include "PathGenerator.h"

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

	owner->setPositionX(MapController::getInstance()->getXPositionInWorld(1));
	owner->setPositionY(MapController::getInstance()->getYPositionInWorld(1));
	owner->setSize(10);
	this->curpos = { 1,1 };
	this->nextpos = { 1,1 };
	this->end = { 10,20 };
	this->flag = 0;
	this->randtime = (rand() % 10 + 1)*1000;

	return true;
}

void MonsterAI::update() {
	auto owner = this->getOwner();
	if ((this->count % this->randtime) == 0) {
		this->randtime = (rand() % 10 + 1) * 1000;
		PosType e;
		this->start = this->nextpos;
		while (!this->path.Empty()) {
			this->path.Pop(e);
		}
		this->setMapInfo(MapController::getInstance()->mapInfo);
		PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
		if (!this->path.Empty()) {
			this->path.Pop(this->nextpos);
		}
	}
	if ((this->count % 20) == 0) {
		this->flag = 0;
		this->curpos = this->nextpos;
		if (!this->path.Empty()) {
			this->path.Pop(this->nextpos);
		}
	}
	MoveByPath();
	this->count++;
}

void MonsterAI::MoveByPath() {
	auto owner = this->getOwner();
	//到达终点
	if (this->curpos.posX == this->nextpos.posX&&this->curpos.posY == this->nextpos.posY) {
		return;
	}
	//水平移动
	else if (this->curpos.posX == this->nextpos.posX) {
		if (this->curpos.posY < this->nextpos.posY) {
			owner->setPositionX(owner->getPositionX() + 1);		//向右运动
		}
		else {
			owner->setPositionX(owner->getPositionX() - 1);		//向左运动
		}
	}
	//垂直移动
	else if (this->curpos.posY == this->nextpos.posY) {
		if (this->curpos.posX < this->nextpos.posX) {
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