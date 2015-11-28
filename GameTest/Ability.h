#pragma once

#include <string>

class GameObject;

class Ability {
private:
    std::string abilityName;
    GameObject* abilityOwner;
public:
    Ability();
    ~Ability();

    static Ability* create(GameObject* owner);
    virtual bool init(GameObject* owner);
    virtual void update();
    virtual void destroy();

    void setName(const std::string& name) { abilityName = name; }
    std::string getName() { return abilityName; }

    GameObject* getOwner() { return abilityOwner; }
};
