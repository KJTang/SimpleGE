#ifndef MONSTER_AI
#define MONSTER_AI

#include "SimpleGE.h"
#include "Stack.h"
#include "Queue.h"

const int DISTANCE = 10;

#define MAP_ROW 20 //��������
#define MAP_LOW 40 //��������

/*��ͼ�������Ͷ���*/
typedef struct MPosType {
	int posX;		//�����꣬��Ӧ������
	int posY;		//�����꣬��Ӧ������
}MPosType;

/*�����������Ͷ���*/
typedef struct WPosType {
	float posX;		//������
	float posY;		//������
}WPosType;

/*���ڿ�����������㷨�µ�·��������Ͷ���*/
typedef struct DElemType {
	int ord;		//·�������·���ϵġ���š�
	MPosType seat;	//·������ڵ�ͼ�ϵġ�����λ�á�
	int di;			//�Ӵ˽��������һ���ġ�����
}DElemType;

/*����������������㷨�µ�·��������Ͷ���*/
typedef struct WElemType {
	int vexs[20][40];  //����ӿ�ʼ��㵽��ǰ����·��
	MPosType seat;				  //·������ڵ�ͼ�ϵġ�����λ�á�
}WElemType;


class MonsterAI : public Ability {
private:
	int count, randtime, flag, rndDi;
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

	/*�������������������·��*/
	bool DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*���ݹ��������������·��*/
	bool BFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*�жϵ�ǰ����Ƿ��ͨ*/
	bool Pass(int(*map)[MAP_LOW], MPosType curPos);
	/*���ݵ�ǰ����λ����һ�����*/
	MPosType NextPos(MPosType seat, int di);
};

#endif