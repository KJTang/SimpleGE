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

	//��ʼ����ͼ��Ϣ
	this->setMapInfo(MapController::getInstance()->mapInfo);

	owner->setPositionX(MapController::getInstance()->getXPositionInWorld(1));
	owner->setPositionY(MapController::getInstance()->getYPositionInWorld(1));
	owner->setSize(10);
	this->curPos = { 1,1 };
	this->nextPos = { 1,1 };
	this->end = { 10,20 };
	this->flag = 0;
	this->randtime = (rand() % 10 + 1)*1000;

	return true;
}

void MonsterAI::update() {
	auto owner = this->getOwner();
	if ((this->count % this->randtime) == 0) {
		this->randtime = (rand() % 10 + 1) * 1000;
		MPosType e;
		this->start = this->nextPos;
		while (!this->path.Empty()) {
			this->path.Pop(e);
		}
		this->setMapInfo(MapController::getInstance()->mapInfo);
		PathGenerator::getInstance()->WFSPath(this->map, this->start, this->end, this->path);
		if (!this->path.Empty()) {
			this->path.Pop(this->nextPos);
		}
	}
	if ((this->count % 20) == 0) {
		this->flag = 0;
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
	//�����յ�
	if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
		return;
	}
	//ˮƽ�ƶ�
	else if (this->curPos.posX == this->nextPos.posX) {
		if (this->curPos.posY < this->nextPos.posY) {
			owner->setPositionX(owner->getPositionX() + 1);		//�����˶�
		}
		else {
			owner->setPositionX(owner->getPositionX() - 1);		//�����˶�
		}
	}
	//��ֱ�ƶ�
	else if (this->curPos.posY == this->nextPos.posY) {
		if (this->curPos.posX < this->nextPos.posX) {
			owner->setPositionY(owner->getPositionY() - 1);		//�����˶�
		}
		else {
			owner->setPositionY(owner->getPositionY() + 1);		//�����˶�
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