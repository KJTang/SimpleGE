#pragma once

#include "SimpleGE.h"
#include "PathGenerator.h"

const int DISTANCE = 10;
const int REACH = 1;

class MonsterAI : public Ability {
private:
	int count, randtime, flag;
	int map[MAP_ROW][MAP_LOW];
	Stack<MPosType> path;
	MPosType curPos, nextPos, start, end;
	GameObject* player;
public:
	MonsterAI();
	~MonsterAI();

	static MonsterAI* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();
	void MoveByPath();
	void setMapInfo(int (*map)[40]);
};