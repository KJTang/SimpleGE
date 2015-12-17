#include "MonsterAI.h"

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
	this->map[0][0] = 1;
	this->map[0][1] = 1;
	this->map[0][2] = 1;
	this->map[0][3] = 1;
	this->map[1][0] = 1;
	this->map[1][1] = 0;
	this->map[1][2] = 0;
	this->map[1][3] = 1;
	this->map[2][0] = 1;
	this->map[2][1] = 1;
	this->map[2][2] = 0;
	this->map[2][3] = 1;
	this->map[3][0] = 1;
	this->map[3][1] = 1;
	this->map[3][2] = 1;
	this->map[3][3] = 1;
	//this->map[4][0] = 1;
	//this->map[4][1] = 0;
	//this->map[4][2] = 0;
	//this->map[4][3] = 1;
	//this->map[5][0] = 1;
	//this->map[5][1] = 1;
	//this->map[5][2] = 1;
	//this->map[5][3] = 1;

	this->curpos = { 1,1 };
	this->end = { 4,1 };
	this->path.Init();

	return true;
}

void MonsterAI::update() {
	auto owner = this->getOwner();
	if ((this->count % 200) == 0) {
		this->start = this->curpos;
		this->end = { 2,2 };
		MonsterPath(this->map, this->start, this->end, this->path);
		if (!this->path.Empty()) {
			this->path.Pop(this->nextpos);
		}
	}
	if ((this->count % 40) == 0) {
		this->curpos = this->nextpos;
		if (!this->path.Empty()) {
			this->path.Pop(this->nextpos);
			printf("%d,%d\n", this->curpos.posX, this->curpos.posY);
			printf("%d,%d\n", this->nextpos.posX, this->nextpos.posY);
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
			owner->setPositionY(owner->getPositionY() - 1);		//向上运动
		}
		else {
			owner->setPositionY(owner->getPositionY() + 1);		//向下运动
		}
	}
}