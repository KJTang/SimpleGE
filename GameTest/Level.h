#pragma once

#include "GameObject.h"

class Level : public GameObject {
private:

public:
    Level();
    ~Level();

    CREATE_FUNC(Level);

    virtual bool init();
};