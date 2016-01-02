#pragma once

#include <vector>
#include <string>

#include "AEEngine.h"
#include "Macros.h"
#include "SystemController.h"
#include "Ability.h"

using std::vector;

class GameObject {
private:
    std::string _name;

    bool isActive; // 若处于非活动状态则关闭update
    bool isVisible; // 若不可见则关闭draw
    AEGfxVertexList*	pMesh; // 形状
    float size; // 大小
    bool isPosInit;
    AEVec2 posRelative;	 // 相对位置
    AEVec2 posGlobal; // 全局位置
    AEVec2 velCurr;	// 当前速度
    float dirCurr;	// 当前方向
    AEMtx33 transform;	// 变换矩阵：每一帧都需要为每一个对象计算
    AEGfxTexture* texture; // GameObject 的纹理

    GameObject* parent; // 当前节点的parent
    vector<GameObject*> children; // 当前节点的children
    int referenceCount; // 引用计数

    vector<Ability*> abilities; // GameObject's extra ability
public:
    GameObject();
    ~GameObject();

    CREATE_FUNC(GameObject);
    CREATE_FUNC_WITH_STR(GameObject);

    // name
    void setName(const std::string &name) { _name = name; }
    std::string getName() { return _name; }
    // active
    void setActive(bool ac) { isActive = ac; }
    bool getActive() { return isActive; }
    // visible
    void setVisible(bool vi) { isVisible = vi; }
    bool getVisible() { return isVisible; }
    // getter & setter
    virtual void setSize(float s) { size = s; }
    virtual float getSize() { return size; }

    // position in relative
    virtual void setPosition(AEVec2 pos) { posRelative = pos; posGlobal = convertToGlobalPosition(this); }
    virtual void setPosition(float x, float y) { posRelative.x = x; posRelative.y = y; posGlobal = convertToGlobalPosition(this); }
    virtual void setPositionX(float x) { posRelative.x = x; posGlobal = convertToGlobalPosition(this); }
    virtual void setPositionY(float y) { posRelative.y = y; posGlobal = convertToGlobalPosition(this); }
    // # ISSUE : getPosition only can get the first set position, when use setVelocity to change GameObject's positon,
    //                   it cannot get the updated position
    //                   so currently if want it to return correct value, please use setPosition to change GameObject's position
    virtual AEVec2 getPosition() { return posRelative; }
    virtual float getPositionX() { return posRelative.x; }
    virtual float getPositionY() { return posRelative.y; }
    // position in global
    virtual void setRealPositionX(float x) { posGlobal.x = x; }
    virtual void setRealPositionY(float y) { posGlobal.y = y; }
    virtual void setRealPosition(float x, float y) { posGlobal.x = x; posGlobal.y = y; }
    virtual void setRealPosition(AEVec2 pos) { posGlobal = pos; }
    virtual float getRealPositionX() { return posGlobal.x; }
    virtual float getRealPositionY() { return posGlobal.y; }
    virtual AEVec2 getRealPosition() { return posGlobal; }
    // 坐标转化
    AEVec2 convertToGlobalPosition(GameObject *go) {
        auto parent = go->getParent();
        if (parent) {
            AEVec2 pos = convertToGlobalPosition(parent);
            pos.x += go->getPositionX();
            pos.y += go->getPositionY();
            return pos;
        }
        return go->getPosition();
    }
    AEVec2 convertToRelativePosition(GameObject *go) {
        // TODO:
    }

    void setVelocity(AEVec2 vel) { velCurr = vel; }
    void setVelocity(float x, float y) { velCurr.x = x; velCurr.y = y; }
    AEVec2 getVelocity() { return velCurr; }

    virtual void setDirection(float dir) { dirCurr = dir; }
    virtual float getDirection() { return dirCurr; }

    void setMesh(AEGfxVertexList* mesh) {
        if (pMesh) {
            AEGfxMeshFree(pMesh);
        }
        pMesh = mesh;
    }
    AEGfxVertexList* getMesh() { return pMesh; }

    void setTransformMatrix(AEMtx33 trans) { transform = trans; }
    AEMtx33* getTransformMatrix() { return &transform; }

    void setTexture(AEGfxTexture *tex) { texture = tex; }

    // virtual functions
    virtual bool init();
    virtual bool init(const std::string &textureName);
    virtual void update();
    virtual void draw();
    virtual void destroy();

    // GameObject tree
    void setParent(GameObject* parent);
    GameObject* getParent();
    void addChild(GameObject* child);
    void addChild(GameObject* child, const std::string &name);
    void removeChild(GameObject* child);
    bool removeFromParent();
    vector<GameObject*>& getChildren();
    GameObject* getChildByName(const std::string &name);

    void retain(); // 增加引用计数
    void release(); // 引用计数设为0
    int getReferenceCount();

    // abilities
    int getAbilityCount() { return abilities.size(); }
    void addAbility(Ability* ab);
    void removeAbility(const std::string& name);
    const vector<Ability*>& getAbilities() { return abilities; }
};
