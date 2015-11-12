#include "myObject.h"

/**************
Ship
**************/
Ship::Ship() {}

Ship::~Ship() {}

bool Ship::init() {
    if (!GameObject::init()) {
        return false;
    }
    // mesh
    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, 0.5f, 0x01FF0000, 0.0f, 0.0f,
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
        0.5f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
    auto newMesh = AEGfxMeshEnd();
    this->setMesh(newMesh);

    this->setSize(50.0f);
    this->setPosition(0, 0);
    this->setVelocity(0, 0);
    this->setDirection(0.0f);
    return true;
}