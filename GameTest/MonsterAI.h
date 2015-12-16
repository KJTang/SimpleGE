#pragma once

#include "SimpleGE.h"


class MonsterAI : public Ability {
private:
	int count;
	PosType curpos, nextpos,start,end;
	MapType map[6][4];
	Stack<PosType> path;
public:
	MonsterAI();
	~MonsterAI();

	static MonsterAI* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();
	void MoveByPath();
};