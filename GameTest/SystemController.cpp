#include "SystemController.h"

#include "GameObject.h"
#include "Level.h"

#pragma comment (lib, "Alpha_Engine.lib")
// ȡ��ʹ��freopen�ľ���
#pragma warning(disable:4996)

/*****************
System Control
*****************/
SystemController *SystemController::sharedController = nullptr;

// ϵͳ��ʼ��
int SystemController::init(HINSTANCE hInstance, int nCmdShow) {
    // ���ÿ���̨���
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    this->log("System: init");
    // Alphaϵͳ��ʼ��
    sysInitInfo.mAppInstance = hInstance;	// WinMain�ĵ�1������
    sysInitInfo.mShow = nCmdShow;		// WinMain�ĵ�4������
    sysInitInfo.mWinWidth = 800;
    sysInitInfo.mWinHeight = 600;
    sysInitInfo.mCreateConsole = 1;			// �Ƿ���Ҫ�򿪿���̨
    sysInitInfo.mCreateWindow = 1;			// �Ƿ���Ҫ��������
    sysInitInfo.mWindowHandle = NULL;			// ��Alphaȱʡ����
    sysInitInfo.mMaxFrameRate = 60;			// ����֡�ʣ����ʹ��Alpha��֡�ʿ��ƹ��ܵĻ���
    sysInitInfo.mpWinCallBack = NULL;			// ָ�����ڹ��̺���
    sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// �����ඨ����ػ淽ʽ									
    sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;			// ���ڷ��ȡֵ��WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    if (0 == AESysInit(&sysInitInfo))
        return -1;
    AESysReset();

    // flag
    gameQuit = false;
    levelChange = false;

    // GameObject Control
    rootObject = nullptr;
    currentLevel = nullptr, nextLevel = nullptr;
    // Ϊ��ʼ��������׼��
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

// �л��ؿ�
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

// ϵͳ�˳�
void SystemController::exit(void) {
    this->log("System: Exit");
     rootObject->destroy();
    // Alphaϵͳ�˳�
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
    // ���û���ģʽ(Color or texture)
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