#include "myAbility.h"

/**************
PlayerAI
***************/
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
    this->getOwner()->setVelocity(0, 0);

    return true;
}

void PlayerControl::update() {
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