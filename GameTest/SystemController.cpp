#include "SystemController.h"

#include "GameObject.h"
#include "Level.h"

#pragma comment (lib, "Alpha_Engine.lib")
// 取消使用freopen的警告
#pragma warning(disable:4996)

/*****************
System Control
*****************/
SystemController *SystemController::sharedController = nullptr;

// 系统初始化
int SystemController::init(HINSTANCE hInstance, int nCmdShow) {
    // 启用控制台输出
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    this->log("System: init");
    // Alpha系统初始化
    sysInitInfo.mAppInstance = hInstance;	// WinMain的第1个参数
    sysInitInfo.mShow = nCmdShow;		// WinMain的第4个参数
    sysInitInfo.mWinWidth = 800;
    sysInitInfo.mWinHeight = 600;
    sysInitInfo.mCreateConsole = 1;			// 是否需要打开控制台
    sysInitInfo.mCreateWindow = 1;			// 是否需要创建窗口
    sysInitInfo.mWindowHandle = NULL;			// 让Alpha缺省处理
    sysInitInfo.mMaxFrameRate = 60;			// 设置帧率（如果使用Alpha的帧率控制功能的话）
    sysInitInfo.mpWinCallBack = NULL;			// 指定窗口过程函数
    sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// 窗口类定义的重绘方式									
    sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;			// 窗口风格，取值：WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    if (0 == AESysInit(&sysInitInfo))
        return -1;
    AESysReset();

    // flag
    gameQuit = false;
    levelChange = false;

    // GameObject Control
    rootObject = nullptr;
    currentLevel = nullptr, nextLevel = nullptr;
    // 为开始画对象做准备
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    return 0;
}

void SystemController::setCurrentLevel(Level* level) {
    assert(level);
    if (currentLevel) {
        currentLevel->destroy();
    }
    currentLevel = level;
    rootObject = currentLevel;
}

void SystemController::setNextLevel(Level* level) {
    assert(level);
    if (nextLevel) {
        nextLevel->destroy();
    }
    nextLevel = level;
    levelChange = true;
}

// 切换关卡
void SystemController::changeLevel() {
    assert(nextLevel);
    if (currentLevel) {
        currentLevel->destroy();
    }
    currentLevel = nextLevel;
    nextLevel = nullptr;
    rootObject = currentLevel;
    levelChange = false;
}

void SystemController::quitGame() {
    gameQuit = true;
}

// 系统退出
void SystemController::exit(void) {
    this->log("System: Exit");
     rootObject->destroy();
    // Alpha系统退出
    AESysExit();
}

// log
void SystemController::log(const string &info) {
    cout <<"GameLog: " << info << endl;
}

/***************
GameObject Control
****************/
void SystemController::setRootObject(GameObject* rootObj) {
    if (rootObject) {
        rootObject->destroy();
    }
    rootObject = rootObj;
}

void SystemController::update() {
    assert(rootObject);
    recursiveUpdate(rootObject);
}

void SystemController::recursiveUpdate(GameObject* go) {
    if (go->getActive()) {
        go->update();
        if (go->getAbilityCount()) {
            for (auto it = go->getAbilities().begin(); it != go->getAbilities().end(); ++it) {
                (*it)->update();
            }
        }
        for (auto it = go->getChildren().begin(); it != go->getChildren().end(); ++it) {
            recursiveUpdate((*it));
        }
    }
}

void SystemController::draw() {
    assert(rootObject);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    // 设置绘制模式(Color or texture)
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
    recursiveDraw(rootObject);
}

void SystemController::recursiveDraw(GameObject* go) {
    if (go->getActive()) {
        go->draw();
        for (auto it = go->getChildren().begin(); it != go->getChildren().end(); ++it) {
            recursiveDraw((*it));
        }
    }
}