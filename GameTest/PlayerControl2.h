#pragma once

#include <queue>
#include "SimpleGE.h"



class PlayerControl2 : public Ability {
private:
	enum {
		NONE,
		DOWN,
		UP,
		LEFT,
		RIGHT
	};
	int _playerState;
	int count;

	float speed;
	int curDirection, nextDirection;
	void onKeyDown(int direction); // �����¼�
	bool isOppositeDirection(int direction1, int direction2);
	// ��ȡ��ײ����
	void getCollisionPoint(int direction, float &x, float &y); // һ�����
	void getCollisionPoint(int direction, float &x1, float &y1, float &x2, float &y2); // �������
																					   // �Զ���
	int beans;
	void eatBeans();
public:
	PlayerControl2();
	~PlayerControl2();

	static PlayerControl2* create(GameObject* owner);
	virtual bool init(GameObject* owner);
	virtual void update();

	int getPlayerState() { return _playerState; }
};