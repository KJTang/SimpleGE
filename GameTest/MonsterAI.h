#pragma once

#include "SimpleGE.h"

class MonsterAI : public Ability {
private:
	int count;
public:
	MonsterAI();
	~MonsterAI();

	static MonsterAI* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();
};