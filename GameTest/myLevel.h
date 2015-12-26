#pragma once

#include "SimpleGE.h"

class LoadingLevel : public Level {
private:
    int count;
    bool quit;
public:
    LoadingLevel();
    ~LoadingLevel();

    CREATE_FUNC(LoadingLevel);

    virtual bool init();
    virtual void update();

    void callback(void *data); // when loaded, call this
};

class LevelOne : public Level {
private:
    int count;
    GameObject* go;
public:
    LevelOne();
    ~LevelOne();

    CREATE_FUNC(LevelOne);

    virtual bool init();
    virtual void update();
};

class LevelTwo : public Level {
private:
    int count;
public:
    LevelTwo();
    ~LevelTwo();

    CREATE_FUNC(LevelTwo);

    virtual bool init();
    virtual void update();
};

class LevelThree : public Level {
private:
    int count;
public:
    LevelThree();
    ~LevelThree();

    CREATE_FUNC(LevelThree);

    virtual bool init();
    virtual void update();
};