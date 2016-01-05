#pragma once

#include "SimpleGE.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
/**************
WQY
*************/
#define dY 50
#define Y0 30
#define dX 150
#define X0 130
#define BGSIZE 400
#define SIZE 70
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8

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

<<<<<<< HEAD
=======
=======
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

class LoadingLevel :public Level {
=======
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
class LoadingLevel : public Level {
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
};

/************
WDP
***************/
class LevelGameInfo :public Level {
private:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    int count;
    GameObject *go;
public:
    LevelGameInfo();
    ~LevelGameInfo();

    CREATE_FUNC(LevelGameInfo);

    virtual bool init();
    virtual void update();
<<<<<<< HEAD
=======
=======
	int count;
	GameObject *go;
public:
	LevelGameInfo();
	~LevelGameInfo();

	CREATE_FUNC(LevelGameInfo);

	virtual bool init();
	virtual void update();
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
};

class LevelTeamInfo :public Level {
private:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    GameObject *go;
public:
    LevelTeamInfo(){}
    ~LevelTeamInfo(){}

    CREATE_FUNC(LevelTeamInfo);

    virtual bool init();
    virtual void update();
<<<<<<< HEAD
=======
=======
	GameObject *go;
public:
	LevelTeamInfo(){}
	~LevelTeamInfo(){}

	CREATE_FUNC(LevelTeamInfo);

	virtual bool init();
	virtual void update();
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
};

class LevelSuccess :public Level {
private:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    GameObject *go;
    std::vector<GameObject *> choice;
public:
    LevelSuccess(){}
    ~LevelSuccess(){}

    CREATE_FUNC(LevelSuccess);

    virtual bool init();
    virtual void update();
<<<<<<< HEAD
=======
=======
	GameObject *go;
	std::vector<GameObject *> choice;
public:
	LevelSuccess(){}
	~LevelSuccess(){}

	CREATE_FUNC(LevelSuccess);

	virtual bool init();
	virtual void update();
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
};

class LevelFaile :public Level {
private:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
    GameObject *go;
    std::vector<GameObject *> choice;
public:
    LevelFaile() {}
    ~LevelFaile() {}

    CREATE_FUNC(LevelSuccess);

    virtual bool init();
    virtual void update();
<<<<<<< HEAD
=======
=======
	GameObject *go;
	std::vector<GameObject *> choice;
public:
	LevelFaile() {}
	~LevelFaile() {}

	CREATE_FUNC(LevelSuccess);

	virtual bool init();
	virtual void update();
=======
>>>>>>> 6796733aa2a52888b87f31c25ddc3386c9ffd7c7
>>>>>>> 3d5af31a699c3da4508d64910a5b4db227b42836
>>>>>>> 47ff747121f93f9ba1454f73873a8fad97613cc8
};