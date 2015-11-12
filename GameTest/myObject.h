#pragma once

#include "SimpleGE.h"

class Ship : public GameObject {
public:
    Ship();
    ~Ship();

    CREATE_FUNC(Ship);

    virtual bool init();
};