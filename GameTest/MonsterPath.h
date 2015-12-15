#pragma once

#include "Stack.h"

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

/*地图类型定义*/
typedef struct {
	PosType *seat;
}MapType;

/*生成怪物行走的路径*/
bool MonsterPath(MapType map,PosType start,PosType end) {

}
