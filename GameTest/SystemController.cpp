#include "SystemController.h"

#include "GameObject.h"
#include "Level.h"
#include "SoundController.h"

#pragma comment (lib, "Alpha_Engine.lib")
// 取消使用freopen的警告
#pragma warning(disable:4996)

/*****************
System Control
*****************/
SystemController *SystemController::sharedController = nullptr;

// 系统初始化
int SystemController::init(HINSTANCE hInstance, int nCmdShow) {
    //// 启用控制台输出
    //AllocConsole();
    //freopen("CONIN$", "r", stdin);
    //freopen("CONOUT$", "w", stdout);
    //freopen("CONOUT$", "w", stderr);

    this->log("System: init");

    WNDCLASS wndClass;		// 窗口类：定义
    HWND hWnd;				// 窗口实例：创建
                            // MSG msg = {0};		// 消息获取由Alpha完成，因此不使用该变量

                            /* 使用Alpha绘制对象的变量声明 */
    float obj1X = 0.0f, obj1Y = 0.0f;		// 对象1的位置
    AEGfxVertexList*	pMesh1;				// 对象1的网格(mesh)模型
    float alpha = 1.0f;						// 透明度，取值范围[0,1]

                                            /* Alpha系统定义 */
    AESysInitInfo sysInitInfo;
    sysInitInfo.mAppInstance = hInstance;	// WinMain的第1个参数
    sysInitInfo.mShow = nCmdShow;		// WinMain的第4个参数
    sysInitInfo.mWinWidth = 800;
    sysInitInfo.mWinHeight = 600;
    sysInitInfo.mCreateConsole = 1;			// 是否需要打开控制台
    sysInitInfo.mCreateWindow = 0;			// 是否需要创建窗口
    sysInitInfo.mMaxFrameRate = 60;			// 设置帧率（如果使用Alpha的帧率控制功能的话）
    sysInitInfo.mpWinCallBack = NULL;			// 指定窗口过程函数（因为没用Alpha创建窗口，因此设置为NULL）
    sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// 窗口类定义的重绘方式									
    sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;			// 窗口风格，取值：WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    // 窗口定义  （与Alpha系统统一）
    wndClass.style = sysInitInfo.mClassStyle;	// 水平重绘和垂直重绘
    wndClass.lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT { // 指向窗口过程函数
        switch (msg) {
            case WM_DESTROY:
                SystemController::getInstance()->quitGame();
                break;
                // 其余调用默认窗口过程
            default:
                return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        return 0;
    };

    wndClass.cbClsExtra = 0;					// 分配给该窗口类的附加内存
    wndClass.cbWndExtra = 0;					// 分配给窗口实例的附加内存
    wndClass.hInstance = sysInitInfo.mAppInstance;		// 程序的实例句柄，WinMain的第1个参数
    wndClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);  // 图标句柄，窗口左上角的图标，可以使用自己的图标资源
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	   // 光标句柄
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景画刷
    wndClass.lpszMenuName = NULL;				// 字符串，菜单资源的名字
    wndClass.lpszClassName = "Window Class Name";     // 指定窗口类的名字						

    RegisterClass(&wndClass); // 窗口注册

    // 自定义窗口创建
    hWnd = CreateWindow(wndClass.lpszClassName, "豆子的诱惑", WS_OVERLAPPEDWINDOW, 200, 100, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // 记录窗口信息以便退出时清理
    windowClassName = wndClass.lpszClassName;
    hinstance = hInstance;

    // 通知Alpha系统窗口句柄		
    sysInitInfo.mWindowHandle = hWnd;

    // Alpha系统初始化 及 模块重置
    if (0 == AESysInit(&sysInitInfo))
        printf("System Init Failed!\n");
    AESysReset();

    // flag
    gameQuit = false;
    levelChange = false;

    // GameObject Control
    rootObject = nullptr;
    currentLevel = nullptr, nextLevel = nullptr;
    // 为开始画对象做准备
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // 背景色RGB
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    return 0;
}

void SystemController::start() {
    // main loop
    while (!isGameQuit()) {
        AESysFrameStart();		// 帧开始：封装了PeekMessage
        AEInputUpdate();		// Alpha Engine处理输入

        update();
        draw();
        clear(); // 清理不需要的GameObject

        AESysFrameEnd();		// 帧结束

        if (isLevelChanged()) {
            changeLevel();
        }
    }
}

void SystemController::setCurrentLevel(Level* level) {
    assert(level);
    if (currentLevel) {
        currentLevel->destroy();
    }
    currentLevel = level;
    rootObject = currentLevel;
    rootObject->retain();
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
    this->setCurrentLevel(nextLevel);
    nextLevel = nullptr;
    levelChange = false;
}

void SystemController::quitGame() {
    gameQuit = true;
}

// 系统退出
void SystemController::exit(void) {
    this->log("System: Exit");
     rootObject->destroy();
     SoundController::getInstance()->releaseAllMusic();
    // Alpha系统退出
    AESysExit();
    UnregisterClass(windowClassName, hinstance); // 注销所创建窗口
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
        int test = go->getChildren().size();
        for (auto it = go->getChildren().begin(); it != go->getChildren().end(); ++it) {
            recursiveUpdate((*it));
        }
    }
}

void SystemController::draw() {
    assert(rootObject);
    //AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    ////AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    //AEGfxSetTextureMode(AE_GFX_TM_AVERAGE);
    //AEGfxTextureSet(NULL, 0, 0);
    //AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    //// 设置绘制模式(Color or texture)
    //AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
    recursiveDraw(rootObject);
}

void SystemController::recursiveDraw(GameObject* go) {
    if (go->getVisible()) {
        go->draw();
        for (auto it = go->getChildren().begin(); it != go->getChildren().end(); ++it) {
            recursiveDraw((*it));
        }
    }
}

void SystemController::clear() {
    assert(rootObject);
    recursiveClear(rootObject);
}

void SystemController::recursiveClear(GameObject* go) {
    std::vector<GameObject*> &children = go->getChildren();
    for (int i = 0; i != children.size(); ) {
        if (children[i]->getReferenceCount() == 0) {
            children[i]->destroy();
            children.erase(children.begin()+i);
            int test = go->getChildren().size();
        }
        else {
            recursiveClear(children[i]);
            ++i;
        }
    }
}