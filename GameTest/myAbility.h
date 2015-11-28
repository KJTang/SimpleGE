#pragma once

#include "SimpleGE.h"

class PlayerAI : public Ability {
private:
public:
    PlayerAI();
    ~PlayerAI();

    static PlayerAI* create(GameObject* owner);
    virtual bool init(GameObject* owner);
    virtual void update();
};

class TestAbility : public Ability {
private:
    int count;
public:
    TestAbility() {}
    ~TestAbility() {}

    static TestAbility* create(GameObject* owner) {
        auto pTest = new TestAbility();
        pTest->init(owner);
        return pTest;
    }
    virtual bool init(GameObject* owner) {
        if (!Ability::init(owner)) {
            return false;
        }
        count = 0;
        this->setName("TestAbility");
        return true;
    }
    virtual void update() {
        if (!(count % 30)) {
            printf("TestAbility::update\n");
        }
        ++count;
    }
};