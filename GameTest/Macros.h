#pragma once

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() { \
    auto pObject = new __TYPE__(); \
    pObject->init(); \
    return pObject; \
}