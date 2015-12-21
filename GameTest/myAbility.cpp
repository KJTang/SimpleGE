#include "myAbility.h"

/**************
PlayerAI
***************/
PlayerAI::PlayerAI() {}
PlayerAI::~PlayerAI() {}

PlayerAI* PlayerAI::create(GameObject* owner) {
    auto pAI = new PlayerAI();
    pAI->init(owner);
    return pAI;
}

bool PlayerAI::init(GameObject* owner) {
    if (!Ability::init(owner)) {
        return false;
    }
    this->setName("PlayerAI");
    this->getOwner()->setVelocity(0, 0);

    return true;
}

void PlayerAI::update() {
    auto owner = this->getOwner();
    if (AEInputCheckCurr(VK_DOWN)) {
        //owner->setPositionY(owner->getPositionY() - 10);
        owner->setVelocity(0, -50);
    }
    if (AEInputCheckCurr(VK_UP)) {
        //owner->setPositionY(owner->getPositionY() + 10);
        owner->setVelocity(0, 50);
    }
    if (AEInputCheckCurr(VK_LEFT)) {
        //owner->setPositionX(owner->getPositionX() - 10);
        owner->setVelocity(-50, 0);
    }
    if (AEInputCheckCurr(VK_RIGHT)) {
        //owner->setPositionX(owner->getPositionX() + 10);
        owner->setVelocity(50, 0);
    }
}