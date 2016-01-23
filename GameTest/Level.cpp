#include "Level.h"

Level::Level() {}

Level::~Level() {}

bool Level::init() {
    if (!GameObject::init()) {
        return false;
    }
    return true;
}