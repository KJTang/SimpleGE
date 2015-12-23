###**中文说明**###

1. **SystemController**

    SystemController是这个简单游戏引擎的总控制类，它是一个单例，通过```SystemController::getInstance()```获取实例。
    这个类控制了整个游戏引擎的流程，例如游戏中所有物体的逻辑更新、渲染，关卡的切换等等。
    例如在游戏的入口文件[GameTest.cpp](https://github.com/KJTang/SimpleGE/blob/master/GameTest/GameTest.cpp)中，
    SystemController控制了游戏初始化、游戏循环以及游戏退出。
    ```
  int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // System Initialize
    auto system = SystemController::getInstance();
    system->init(hInstance, nCmdShow);

    // Level One
    auto level = LevelOne::create();
    system->setCurrentLevel(level); // 设置初始关卡

    // main loop， 游戏循环
    while (!system->isGameQuit()) {
        AESysFrameStart();
        AEInputUpdate();
        system->update();
        system->draw();
        AESysFrameEnd();
        // 处理关卡切换事件
        if (system->isLevelChanged()) {
            system->changeLevel();
        }
    }

    // System Exit，游戏退出
    system->exit();
    return 0;
  }
    ```
    
    以下简单介绍以下SystemController的常用方法：
    
    **设置初始关卡：**游戏开始，我们需要运行一个初始关卡：
    
    ```
    auto level = LevelOne::create();
    system->setCurrentLevel(level);
    level->addChild(GameObject::create());
    ```
    此处LevelOne是自定义的关卡，继承自Level，介绍见下节。
    
    **关卡切换：**当达到某个条件，我们可以进行关卡的切换，例如开始界面中点击游戏开始，进入第一关。下面是关卡切换的示例：
    
    ```
    SystemController::getInstance()->setNextLevel(LevelTwo::create());
    ```
    这行代码调用了SystemController设置了下一个关卡为LevelTwo，于是这一帧结束时LevelOne会被销毁，切换到LevelTwo。
    
    **退出游戏：**游戏结束时，利用SystemController退出游戏:```SystemController::getInstance()->quitGame();```




2. **Level**

    Level意即关卡，一个游戏我们可以将其看作数个关卡的组合，比如开始界面(也当作一种关卡)，游戏第一关，游戏第二关，结束界面等等；
    在此，Level其实可以当作一个游戏界面的场景，不同场景的切换组成的一个完整的游戏。
    
    当使用者想要自定义一个关卡时，只要继承Level并重写相应方法即可。例如示例代码[myLevel.cpp](https://github.com/KJTang/SimpleGE/blob/master/GameTest/myLevel.cpp)。
    继承Level时，常用的方法用init和update。

    init是Level的初始化方法，当一个Level被实例化时，此方法自动被调用。例如LevelOne中：
    
    ```
    bool LevelOne::init() {
      if (!Level::init()) {
          return false;
      }
      count = 0;

      auto go = GameObject::create("test.png");
      this->addChild(go);
      go->setPosition(0, 0);
      go->setSize(20);

      return true;
    }
    ```
    此处LevelOne的init首先调用父类Level的init方法，如果父类初始化成功才继续；接着LevelOne创建了一个GameObject(GameObject介绍
    见下节)，设置了此GameObject的位置与大小信息，并添加其为自己的子节点，
    
    ####因为引擎采用渲染树的方式对游戏物体进行渲染，LevelOne被设置为初始关卡，故其为渲染树的根####
    ####通过addChild方法可以将GameObject添加为自己的子节点，加入渲染树。否则物体不会被渲染####
    ####当切换关卡为其它Level时，渲染树的根会改变为新Level，旧渲染树会被销毁，从内存中释放####
    
    update是逻辑更新方法，每一帧都会被调用，可以用于对关卡状态进行实时判断，并执行相应代码。
    
    ```
    void LevelOne::update() {
      Level::update();
      if (count >= 300) {
          GameLog("LevelChange: LevelOne to LevelTwo");
          SystemController::getInstance()->setNextLevel(LevelTwo::create());
      }
      ++count;
    }
    ```
    此处LevelOne的update首先调用父类的update方法，然后再进行自主操作。count在init初始化过，作为计数器，因为update每帧调用一次
    故count可用于计时，当count达到300，则执行切换关卡操作。




3. **GameObject**

    GameObject为游戏中的物体，例如游戏的背景图片，游戏中的人物，游戏中的道具等等，都属于GameObject的范畴，Level也继承自GameObject。
    GameObject可以多种方式创建，常用方式是通过加载本地图片文件作为纹理，加载显示，例如加载本地test.png:
    
    ```
    auto go = GameObject::create("test.png");
    go->setPosition(0, 0);
    go->setSize(20);
    go->setDirection(3.14); // 旋转180度
    go->setVelocity(0, 0); // 设置速度 
    ```
    GameObject还有多种属性可以设置和获取，详细代码见[GameObject.h](https://github.com/KJTang/SimpleGE/blob/master/GameTest/GameObject.h)。

 

 
4. **Ability**

    Ability为GameObject的额外属性，通过GameObject的addAbility方法添加，其update方法会被每帧调用，例如：
    
    ```
    auto go = GameObject::create("test.png");
    this->addChild(go); // current level add 'go' as child
    go->addAbility(PlayerAI::create(go));
    ```
    
    在[myAbility.h](https://github.com/KJTang/SimpleGE/blob/master/GameTest/myAbility.h)
    以及[myAbility.cpp](https://github.com/KJTang/SimpleGE/blob/master/GameTest/myAbility.cpp)中包含了作为示例
    的PlayerAI代码，其作用是让go响应键盘事件来改变运动方向。
    
    使用者可根据需要自行构造Ability的子类，并且应用到GameObject上，示例可参照PlayerAI
