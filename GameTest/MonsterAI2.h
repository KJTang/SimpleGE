#pragma once

#include "SimpleGE.h"
#include "PathGenerator.h"


class MonsterAI2 : public Ability {
private:
	bool game;
	int count, flag;
	int map[MAP_ROW][MAP_LOW];
	Stack<MPosType> path;
	MPosType curPos, nextPos, start, end;
	GameObject* player1, *player2;
public:
	MonsterAI2();
	~MonsterAI2();

	static MonsterAI2* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();
	void MoveByPath();
	void setMapInfo(int(*map)[40]);
};