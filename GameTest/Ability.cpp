#include "Ability.h"

Ability::Ability() {}
Ability::~Ability() {}

Ability* Ability::create(GameObject* owner) {
    auto pAb = new Ability();
    pAb->init(owner);

    return pAb;
}

bool Ability::init(GameObject* owner) {
    abilityOwner = owner;
    abilityName = "DefaultAbility";
    return true;
}

void Ability::update() {

}

void Ability::destroy() {
    delete this;
}