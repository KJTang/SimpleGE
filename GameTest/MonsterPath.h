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
typedef struct {
	PosType *seat;
}MapType;

/*���ɹ������ߵ�·��*/
bool MonsterPath(MapType map,PosType start,PosType end) {

}
