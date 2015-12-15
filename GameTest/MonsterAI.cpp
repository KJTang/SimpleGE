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

	return true;
}

void MonsterAI::update() {
	auto owner = this->getOwner();
	if ((this->count % 100) == 0) {
		owner->setPositionX(owner->getPositionX() + 1);
	}
	this->count++;
}