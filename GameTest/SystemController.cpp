#include "SystemController.h"

#include "GameObject.h"
#include "Level.h"
#include "SoundController.h"

#pragma comment (lib, "Alpha_Engine.lib")
// ȡ��ʹ��freopen�ľ���
#pragma warning(disable:4996)

/*****************
System Control
*****************/
SystemController *SystemController::sharedController = nullptr;

// ϵͳ��ʼ��
int SystemController::init(HINSTANCE hInstance, int nCmdShow) {
    //// ���ÿ���̨���
    //AllocConsole();
    //freopen("CONIN$", "r", stdin);
    //freopen("CONOUT$", "w", stdout);
    //freopen("CONOUT$", "w", stderr);

    this->log("System: init");

    WNDCLASS wndClass;		// �����ࣺ����
    HWND hWnd;				// ����ʵ��������
                            // MSG msg = {0};		// ��Ϣ��ȡ��Alpha��ɣ���˲�ʹ�øñ���

                            /* ʹ��Alpha���ƶ���ı������� */
    float obj1X = 0.0f, obj1Y = 0.0f;		// ����1��λ��
    AEGfxVertexList*	pMesh1;				// ����1������(mesh)ģ��
    float alpha = 1.0f;						// ͸���ȣ�ȡֵ��Χ[0,1]

                                            /* Alphaϵͳ���� */
    AESysInitInfo sysInitInfo;
    sysInitInfo.mAppInstance = hInstance;	// WinMain�ĵ�1������
    sysInitInfo.mShow = nCmdShow;		// WinMain�ĵ�4������
    sysInitInfo.mWinWidth = 800;
    sysInitInfo.mWinHeight = 600;
    sysInitInfo.mCreateConsole = 1;			// �Ƿ���Ҫ�򿪿���̨
    sysInitInfo.mCreateWindow = 0;			// �Ƿ���Ҫ��������
    sysInitInfo.mMaxFrameRate = 60;			// ����֡�ʣ����ʹ��Alpha��֡�ʿ��ƹ��ܵĻ���
    sysInitInfo.mpWinCallBack = NULL;			// ָ�����ڹ��̺�������Ϊû��Alpha�������ڣ��������ΪNULL��
    sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// �����ඨ����ػ淽ʽ									
    sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;			// ���ڷ��ȡֵ��WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    // ���ڶ���  ����Alphaϵͳͳһ��
    wndClass.style = sysInitInfo.mClassStyle;	// ˮƽ�ػ�ʹ�ֱ�ػ�
    wndClass.lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT { // ָ�򴰿ڹ��̺���
        switch (msg) {
            case WM_DESTROY:
                SystemController::getInstance()->quitGame();
                break;
                // �������Ĭ�ϴ��ڹ���
            default:
                return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        return 0;
    };

    wndClass.cbClsExtra = 0;					// ������ô�����ĸ����ڴ�
    wndClass.cbWndExtra = 0;					// ���������ʵ���ĸ����ڴ�
    wndClass.hInstance = sysInitInfo.mAppInstance;		// �����ʵ�������WinMain�ĵ�1������
    wndClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);  // ͼ�������������Ͻǵ�ͼ�꣬����ʹ���Լ���ͼ����Դ
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	   // �����
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������ˢ
    wndClass.lpszMenuName = NULL;				// �ַ������˵���Դ������
    wndClass.lpszClassName = "Window Class Name";     // ָ�������������						

    RegisterClass(&wndClass); // ����ע��

    // �Զ��崰�ڴ���
    hWnd = CreateWindow(wndClass.lpszClassName, "���ӵ��ջ�", WS_OVERLAPPEDWINDOW, 200, 100, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // ��¼������Ϣ�Ա��˳�ʱ����
    windowClassName = wndClass.lpszClassName;
    hinstance = hInstance;

    // ֪ͨAlphaϵͳ���ھ��		
    sysInitInfo.mWindowHandle = hWnd;

    // Alphaϵͳ��ʼ�� �� ģ������
    if (0 == AESysInit(&sysInitInfo))
        printf("System Init Failed!\n");
    AESysReset();

    // flag
    gameQuit = false;
    levelChange = false;

    // GameObject Control
    rootObject = nullptr;
    currentLevel = nullptr, nextLevel = nullptr;
    // Ϊ��ʼ��������׼��
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // ����ɫRGB
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    return 0;
}

void SystemController::start() {
    // main loop
    while (!isGameQuit()) {
        AESysFrameStart();		// ֡��ʼ����װ��PeekMessage
        AEInputUpdate();		// Alpha Engine��������

        update();
        draw();
        clear(); // ������Ҫ��GameObject

        AESysFrameEnd();		// ֡����

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

// �л��ؿ�
void SystemController::changeLevel() {
    this->setCurrentLevel(nextLevel);
    nextLevel = nullptr;
    levelChange = false;
}

void SystemController::quitGame() {
    gameQuit = true;
}

// ϵͳ�˳�
void SystemController::exit(void) {
    this->log("System: Exit");
     rootObject->destroy();
     SoundController::getInstance()->releaseAllMusic();
    // Alphaϵͳ�˳�
    AESysExit();
    UnregisterClass(windowClassName, hinstance); // ע������������
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
    //// ���û���ģʽ(Color or texture)
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