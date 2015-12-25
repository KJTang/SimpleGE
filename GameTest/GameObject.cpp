#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() {}

bool GameObject::init() {
    isActive = true;
    isVisible = true;
    parent = nullptr;
    texture = nullptr;
    referenceCount = 0;
    // mesh
    AEGfxMeshStart();
    //AEGfxTriAdd(
    //    -1.0f, -1.0f, 0x00000000, 0.0f, 1.0f,
    //    1.0f, -1.0f, 0x00000000, 1.0f, 1.0f,
    //    -1.0f, 1.0f, 0x00000000, 0.0f, 0.0f);
    //AEGfxTriAdd(
    //    1.0f, -1.0f, 0x00000000, 1.0f, 1.0f,
    //    1.0f, 1.0f, 0x00000000, 1.0f, 0.0f,
    //    -1.0f, 1.0f, 0x00000000, 0.0f, 0.0f);
    auto newMesh = AEGfxMeshEnd();
    this->setMesh(newMesh);

    this->setSize(0.0f);
    this->setPosition(0, 0);
    isPosInit = false;
    this->setVelocity(0, 0);
    this->setDirection(0.0f);

    return true;
}

bool GameObject::init(const std::string &textureName) {
    isActive = true;
    isVisible = true;
    parent = nullptr;
    texture = nullptr;
    referenceCount = 0;
    // mesh
    AEGfxMeshStart();
    AEGfxTriAdd(
        -1.0f, -1.0f, 0x00FFFFFF, 0.0f, 1.0f,
        1.0f, -1.0f, 0x00FFFFFF, 1.0f, 1.0f,
        -1.0f, 1.0f, 0x00FFFFFF, 0.0f, 0.0f);
    AEGfxTriAdd(
        1.0f, -1.0f, 0x00FFFFFF, 1.0f, 1.0f,
        1.0f, 1.0f, 0x00FFFFFF, 1.0f, 0.0f,
        -1.0f, 1.0f, 0x00FFFFFF, 0.0f, 0.0f);
    auto newMesh = AEGfxMeshEnd();
    this->setMesh(newMesh);

    this->setSize(50.0f);
    this->setPosition(0, 0);
    isPosInit = false;
    this->setVelocity(0, 0);
    this->setDirection(0.0f);

    texture = AEGfxTextureLoad(textureName.c_str());

    return true;
}

void GameObject::update() {
    if (!isPosInit) {
        this->setRealPosition(convertToGlobalPosition(this)); // �ȸ��µ�ǰλ��
        isPosInit = true;
    }
    // ����λ��
    AEVec2 added, newPos;
    auto frameTime = static_cast<float>(AEFrameRateControllerGetFrameTime());
    AEVec2Set(&added, this->getVelocity().x * frameTime, this->getVelocity().y * frameTime);
    newPos.x = posGlobal.x + added.x;
    newPos.y = posGlobal.y + added.y;
    this->setRealPosition(newPos);

    AEMtx33 trans, rot, scale;
    // ���ž���
    AEMtx33Scale(&scale, this->getSize(), this->getSize());
    // ��ת����
    AEMtx33Rot(&rot, this->getDirection());
    // ƽ�ƾ���
    AEMtx33Trans(&trans, this->getRealPosition().x, this->getRealPosition().y);
    // ����ȷ��˳����������3�������γ�2ά�任����
    AEMtx33Concat(this->getTransformMatrix(), &trans, &rot);
    AEMtx33Concat(this->getTransformMatrix(), this->getTransformMatrix(), &scale);
}

void GameObject::draw() {
    if (!texture) {
        // �������в���(Color blend, textures, etc..)
        AEGfxSetBlendMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(nullptr, 0, 0);
        // ���ö����2D�任����ʹ�ú�����AEGfxSetTransform
        AEGfxSetTransform((*this->getTransformMatrix()).m);
        // ���Ƶ�ǰ����ʹ�ú�����AEGfxMeshDraw
        AEGfxMeshDraw(this->getMesh(), AE_GFX_MDM_TRIANGLES);
    }
    else {
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        AEGfxTextureSet(texture, 0, 0);
        AEGfxSetTextureMode(AE_GFX_TM_AVERAGE);
        // ���ö����2D�任����ʹ�ú�����AEGfxSetTransform
        AEGfxSetTransform((*this->getTransformMatrix()).m);
        // ���Ƶ�ǰ����ʹ�ú�����AEGfxMeshDraw
        AEGfxMeshDraw(this->getMesh(), AE_GFX_MDM_TRIANGLES);
    }
}

void GameObject::destroy() {
    //GameLog("\tGameObject::destroy");
    for (auto it = children.begin(); it != children.end(); ++it) {
        (*it)->destroy();
    }
    while (abilities.size()) {
        abilities.pop_back();
    }
    delete this;
}

void GameObject::setParent(GameObject* p) {
    parent = p;
}

GameObject* GameObject::getParent() {
    return parent;
}

void GameObject::addChild(GameObject* child) {
    children.push_back(child);
    child->setParent(this);
    child->retain();
}

void GameObject::addChild(GameObject* child, const std::string &name) {
    children.push_back(child);
    child->setParent(this);
    child->setName(name);
    child->retain();
}

void GameObject::removeChild(GameObject* child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it) == child) {
            (*it)->release();
            break;
        }
    }
}

bool GameObject::removeFromParent() {
    if (!parent) {
        GameLog("GameObject::removeFromParent: can not remove a GameObject without parent");
        return false;
    }
    parent->removeChild(this);
    return true;
}

std::vector<GameObject*>& GameObject::getChildren() {
    return children;
}

void GameObject::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

GameObject* GameObject::getChildByName(const std::string &name) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->getName() == name) {
            return (*it);
        }
    }
    return nullptr;
}

void GameObject::retain() {
    ++referenceCount;
}

void GameObject::release() {
    referenceCount = 0;
}

int GameObject::getReferenceCount() {
    return referenceCount;
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
