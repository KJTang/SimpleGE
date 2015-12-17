#pragma once

#include "Stack.h"
#define MAP_ROW 20 //数组行数
#define MAP_LOW 40 //数组列数

/*坐标类型定义*/
typedef struct {
	int posX;		//横坐标
	int posY;		//纵坐标
}PosType;

/*路径结点类型定义*/
typedef struct {
	int ord;		//路径结点在路径上的“序号”
	PosType seat;	//路径结点在地图上的“坐标位置”
	int di;			//从此结点走向下一结点的“方向”
}SElemType;

bool MonsterPath(int (*map)[MAP_LOW], PosType start, PosType end,Stack<PosType> &path);
bool Pass(int (*map)[MAP_LOW], PosType curpos);
PosType NextPos(PosType seat, int di);