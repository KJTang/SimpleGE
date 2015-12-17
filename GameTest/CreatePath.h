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

bool MonsterPath(int (*map)[MAP_LOW], PosType start, PosType end,Stack<PosType> &path);
bool Pass(int (*map)[MAP_LOW], PosType curpos);
PosType NextPos(PosType seat, int di);