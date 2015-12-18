#pragma once

#include "Stack.h"
#define MAP_ROW 20 //��������
#define MAP_LOW 40 //��������

/*�������Ͷ���*/
typedef struct {
	int posX;		//������
	int posY;		//������
}PosType;

/*·��������Ͷ���*/
typedef struct {
	int ord;		//·�������·���ϵġ���š�
	PosType seat;	//·������ڵ�ͼ�ϵġ�����λ�á�
	int di;			//�Ӵ˽��������һ���ġ�����
}SElemType;

class PathGenerator {
private:
	static PathGenerator *sharedGenerator;
public:
	PathGenerator();
	~PathGenerator();

	static PathGenerator* getInstance() {
		if (!sharedGenerator) {
			sharedGenerator = new PathGenerator();
		}
		return sharedGenerator;
	}

	/*�������������������·��*/
	bool DFSPath(int(*map)[MAP_LOW], PosType start, PosType end, Stack<PosType> &path);
	/*���ݹ��������������·��*/
	/*�жϵ�ǰ����Ƿ��ͨ*/
	bool Pass(int(*map)[MAP_LOW], PosType curpos);
	/*���ݵ�ǰ����λ����һ�����*/
	PosType NextPos(PosType seat, int di);
};