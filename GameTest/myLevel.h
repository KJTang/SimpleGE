#pragma once

#include "SimpleGE.h"

/**************
WQY
*************/
#define dY 50
#define Y0 30
#define dX 150
#define X0 130
#define BGSIZE 400
#define SIZE 70

class LevelZero : public Level {
private:
    int count;
    GameObject *go;
public:
    LevelZero(){}
    ~LevelZero(){}

    CREATE_FUNC(LevelZero);

    virtual bool init();
    virtual void update();
};

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

/************
WDP
***************/
class LevelGameInfo :public Level {
private:
    int count;
    GameObject *go;
public:
    LevelGameInfo();
    ~LevelGameInfo();

    CREATE_FUNC(LevelGameInfo);

    virtual bool init();
    virtual void update();
};

class LevelTeamInfo :public Level {
private:
    GameObject *go;
public:
    LevelTeamInfo(){}
    ~LevelTeamInfo(){}

    CREATE_FUNC(LevelTeamInfo);

    virtual bool init();
    virtual void update();
};

class LevelSuccess :public Level {
private:
    GameObject *go;
    std::vector<GameObject *> choice;
public:
    LevelSuccess(){}
    ~LevelSuccess(){}

    CREATE_FUNC(LevelSuccess);

    virtual bool init();
    virtual void update();
};

class LevelFail :public Level {
private:
    GameObject *go;
    std::vector<GameObject *> choice;
public:
    LevelFail() {}
    ~LevelFail() {}

    CREATE_FUNC(LevelFail);

    virtual bool init();
    virtual void update();
};