#pragma once

#include "SimpleGE.h"
#include "PathGenerator.h"


class MonsterAI : public Ability {
private:
	int count,randtime;
	PosType curpos, nextpos,start,end;
	int map[MAP_ROW][MAP_LOW];
	Stack<PosType> path;
	int flag;
public:
	MonsterAI();
	~MonsterAI();

	static MonsterAI* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();
	void MoveByPath();
	void setMapInfo(int (*map)[40]);
};