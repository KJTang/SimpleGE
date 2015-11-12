#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() {}

bool GameObject::init() {
    isActive = true;
    parent = nullptr;
    // mesh
    AEGfxMeshStart();
    //AEGfxTriAdd(
    //    -0.5f, 0.5f, 0x01FF0000, 0.0f, 0.0f,
    //    -0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
    //    0.5f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
    auto newMesh = AEGfxMeshEnd();
    this->setMesh(newMesh);

    this->setSize(0.0f);
    this->setPosition(0, 0);
    this->setVelocity(0, 0);
    this->setDirection(0.0f);
    return true;
}

void GameObject::update() {
    // 更新位置
    AEVec2 added, newPos;
    auto frameTime = static_cast<float>(AEFrameRateControllerGetFrameTime());
    AEVec2Set(&added, this->getVelocity().x * frameTime, this->getVelocity().y * frameTime);
    AEVec2Add(&newPos, &this->getPosition(), &added);
    this->setPosition(newPos);

    AEMtx33 trans, rot, scale;
    // 缩放矩阵
    AEMtx33Scale(&scale, this->getSize(), this->getSize());
    // 旋转矩阵
    AEMtx33Rot(&rot, this->getDirection());
    // 平移矩阵
    AEMtx33Trans(&trans, this->getPosition().x, this->getPosition().y);
    // 以正确的顺序连乘以上3个矩阵形成2维变换矩阵
    AEMtx33Concat(this->getTransformMatrix(), &trans, &rot);
    AEMtx33Concat(this->getTransformMatrix(), this->getTransformMatrix(), &scale);
}

void GameObject::draw() {
    // 设置所有参数(Color blend, textures, etc..)
    AEGfxSetBlendMode(AE_GFX_RM_COLOR);
    // 设置对象的2D变换矩阵，使用函数：AEGfxSetTransform
    AEGfxSetTransform((*this->getTransformMatrix()).m);
    // 绘制当前对象，使用函数：AEGfxMeshDraw
    AEGfxMeshDraw(this->getMesh(), AE_GFX_MDM_TRIANGLES);
}

void GameObject::destroy() {
    GameLog("\tGameObject::destroy");
    for (auto it = children.begin(); it != children.end(); ++it) {
        (*it)->destroy();
        //children.erase(it);
    }
    delete this;
}

GameObject* GameObject::getParent() {
    return parent;
}

void GameObject::addChild(GameObject* child) {
    children.push_back(child);
}

void GameObject::removeChild(GameObject* child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it) == child) {
            child->destroy();
            children.erase(it);
        }
    }
}

vector<GameObject*>& GameObject::getChildren() {
    return children;
}

void GameObject::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

void GameObject::removeAbility(const std::string& name) {
    for (auto it = abilities.begin(); it != abilities.end(); ++it) {
        if ((*it)->getName() == name) {
            (*it)->destroy();
            abilities.erase(it);
            return;
        }
    }
}
