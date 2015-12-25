#pragma once

#include<time.h>
#include "Stack.h"
#include "Queue.h"

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

class PathGenerator {
private:
	static PathGenerator *sharedGenerator;
public:
	PathGenerator();
	~PathGenerator();

	static PathGenerator* getInstance() {
		if (!sharedGenerator) {
			sharedGenerator = new PathGenerator();
			srand(time(0));
		}
		return sharedGenerator;
	}

	/*�������������������·��*/
	bool DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*���ݹ��������������·��*/
	bool BFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*�жϵ�ǰ����Ƿ��ͨ*/
	bool Pass(int(*map)[MAP_LOW], MPosType curPos);
	/*���ݵ�ǰ����λ����һ�����*/
	MPosType NextPos(MPosType seat, int di, int rndDi);
};