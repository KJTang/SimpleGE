//#pragma once
#ifndef MY_ABILITY_H
#define MY_ABILITY_H

#include <queue>
#include "SimpleGE.h"

struct Point{
    int x;
    int y;
};

class PlayerControl : public Ability {
private:
    enum {
        NONE,
        DOWN,
        UP,
        LEFT,
        RIGHT
    };
    float speed;
    int curDirection, nextDirection;
    void onKeyDown(int direction); // 按键事件
    bool isOppositeDirection(int direction1, int direction2);
    // 获取碰撞检测点
    void getCollisionPoint(int direction, float &x, float &y); // 一组检测点
    void getCollisionPoint(int direction, float &x1, float &y1, float &x2, float &y2); // 两组检测点
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

#endif