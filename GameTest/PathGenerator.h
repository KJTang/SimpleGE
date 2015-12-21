#pragma once

#include "Stack.h"
#include "Queue.h"

#define MAP_ROW 20 //��������
#define MAP_LOW 40 //��������

/*��ͼ�������Ͷ���*/
typedef struct MPosType {
	int posX;		//������
	int posY;		//������
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
	int rndDi;
	PathGenerator();
	~PathGenerator();

	static PathGenerator* getInstance() {
		if (!sharedGenerator) {
			sharedGenerator = new PathGenerator();
		}
		return sharedGenerator;
	}

	/*�������������������·��*/
	bool DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*���ݹ��������������·��*/
	bool WFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*�жϵ�ǰ����Ƿ��ͨ*/
	bool Pass(int(*map)[MAP_LOW], MPosType curPos);
	/*�жϵ�ǰ����Ƿ��ڶ�������*/
	bool Belong(int(*vexs)[MAP_LOW], MPosType curPos);
	/*���ݵ�ǰ����λ����һ�����*/
	MPosType NextPos(MPosType seat, int di);
};