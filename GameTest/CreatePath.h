#pragma once

#include "Stack.h"

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

/*��ͼ���Ͷ���*/
typedef int MapType;

bool MonsterPath(MapType (*map)[4], PosType start, PosType end,Stack<PosType> &path);
bool Pass(MapType(*map)[4], PosType curpos);
PosType NextPos(PosType seat, int di);