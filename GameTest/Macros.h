#pragma once

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() { \
    auto pObject = new __TYPE__(); \
    pObject->init(); \
    return pObject; \
}

#define CREATE_FUNC_WITH_STR(__TYPE__) \
static __TYPE__* create(const std::string &str) { \
    auto pObject = new __TYPE__(); \
    pObject->init(str); \
    return pObject; \
}