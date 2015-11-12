#pragma once

#include <vector>

#include "AEEngine.h"

#include "Macros.h"
#include "SystemController.h"
#include "Ability.h"

using std::vector;

class GameObject {
private:
    bool isActive; // �����ڷǻ״̬��ر�update
    AEGfxVertexList*	pMesh; // ��״
    float size; // ��С
    AEVec2 posCurr;	 // ��ǰλ��
    AEVec2 velCurr;	// ��ǰ�ٶ�
    float dirCurr;	// ��ǰ����
    AEMtx33 transform;	// �任����ÿһ֡����ҪΪÿһ���������

    GameObject* parent; // ��ǰ�ڵ��parent
    vector<GameObject*> children; // ��ǰ�ڵ��children

    vector<Ability*> abilities; // GameObject's extra ability
public:
    GameObject();
    ~GameObject();

    CREATE_FUNC(GameObject);

    // active
    void setActive(bool ac) { isActive = ac; }
    bool getActive() { return isActive; }
    // getter & setter
    void setSize(float s) { size = s; }
    float getSize() { return size; }

    void setPosition(AEVec2 pos) { posCurr = pos; }
    void setPosition(float x, float y) { posCurr.x = x; posCurr.y = y; }
    void setPositionX(float x) { posCurr.x = x; }
    void setPositionY(float y) { posCurr.y = y; }
    AEVec2 getPosition() { return posCurr; }
    float getPositionX() { return posCurr.x; }
    float getPositionY() { return posCurr.y; }

    void setVelocity(AEVec2 vel) { velCurr = vel; }
    void setVelocity(float x, float y) { velCurr.x = x; velCurr.y = y; }
    AEVec2 getVelocity() { return velCurr; }

    void setDirection(float dir) { dirCurr = dir; }
    float getDirection() { return dirCurr; }

    void setMesh(AEGfxVertexList* mesh) {
        if (pMesh) {
            AEGfxMeshFree(pMesh);
        }
        pMesh = mesh;
    }
    AEGfxVertexList* getMesh() { return pMesh; }

    void setTransformMatrix(AEMtx33 trans) { transform = trans; }
    AEMtx33* getTransformMatrix() { return &transform; }

    // virtual functions
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual void destroy();

    // GameObject tree
    GameObject* getParent();
    void addChild(GameObject* child);
    void removeChild(GameObject* child);
    vector<GameObject*>& getChildren();

    // abilities
    int getAbilityCount() { return abilities.size(); }
    void addAbility(Ability* ab);
    void removeAbility(const std::string& name);
    const vector<Ability*>& getAbilities() { return abilities; }
};
