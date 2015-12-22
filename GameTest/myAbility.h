#pragma once

#include <queue>
#include "SimpleGE.h"

struct Point{
    int x;
    int y;
};

class PlayerControl : public Ability {
private:
    float speed;
    void onKeyDown(int dirct);
    std::queue<std::pair<int, Point> > command;
public:
    PlayerControl();
    ~PlayerControl();

    static PlayerControl* create(GameObject* owner);
    virtual bool init(GameObject* owner);
    virtual void update();
};

class TestAbility : public Ability {
private:
    int count = 0;
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