#pragma once

#include <vector>
#include <string>
#include "Macros.h"
#include "GameObject.h"

//class GameObject;

class Animation : public GameObject {
private:
    int currentFrame;
    std::vector<GameObject*> AnimationFrame;
    int delayCount;
    float delayTime;
    int repeatCount;
    int repeatTimes;
public:
    virtual bool init();
    CREATE_FUNC(Animation);

    void addFrame(const std::string &filename);
    bool start(float dt, int times); // times == -1 means forever
    virtual void update();

    void setSize(float size);
};