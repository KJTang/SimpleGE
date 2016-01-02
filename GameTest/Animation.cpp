#include "Animation.h"

#include "AEEngine.h"
#include "SystemController.h"

bool Animation::init() {
    if (!GameObject::init()) {
        return false;
    }
    currentFrame = 0;

    delayCount = 0;
    delayTime = 0;
    repeatCount = 0;
    repeatTimes = -1;

    this->setActive(false);
    this->setVisible(true);
    return true;
}

void Animation::addFrame(const std::string &filename) {
    auto newFrame = GameObject::create(filename);
    AE_ASSERT(newFrame);
    this->addChild(newFrame);
    AnimationFrame.push_back(newFrame);

    newFrame->setVisible(false);
}

bool Animation::start(float dt, int times) {
    if (!AnimationFrame.size()) {
        return false;
    }
    delayTime = dt;
    repeatTimes = times*AnimationFrame.size();
    this->setActive(true);
    this->setVisible(true);
    return true;
}

void Animation::update() {
    if (repeatTimes != -1 && repeatCount == repeatTimes) {
        this->setActive(false);
        return;
    }
    if (delayCount >= delayTime*CONST_FPS) {
        delayCount = 0;
        AnimationFrame.at(currentFrame)->setVisible(false);
        ++currentFrame;
        currentFrame %= AnimationFrame.size();
        AnimationFrame.at(currentFrame)->setVisible(true);

        ++repeatCount;
    }
    else {
        ++delayCount;
    }
}

void Animation::setSize(float size) {
    GameObject::setSize(size);
    for (auto it = AnimationFrame.begin(); it != AnimationFrame.end(); ++it) {
        (*it)->setSize(size);
    }
}

void Animation::setPositionX(float x) {
    GameObject::setPositionX(x);
    for (auto it = AnimationFrame.begin(); it != AnimationFrame.end(); ++it) {
        (*it)->setRealPositionX(this->getRealPositionX());
    }
}

void Animation::setPositionY(float y) {
    GameObject::setPositionY(y);
    for (auto it = AnimationFrame.begin(); it != AnimationFrame.end(); ++it) {
        (*it)->setRealPositionY(this->getRealPositionY());
    }
}

void Animation::setPosition(float x, float y) {
    this->setPositionX(x);
    this->setPositionY(y);
}

void Animation::setDirection(float d) {
    GameObject::setDirection(d);
    for (auto it = AnimationFrame.begin(); it != AnimationFrame.end(); ++it) {
        (*it)->setDirection(d);
    }
}