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

	/*根据深度优先搜索生成路线*/
	bool DFSPath(int(*map)[MAP_LOW], PosType start, PosType end, Stack<PosType> &path);
	/*根据广度优先搜索生成路线*/
	/*判断当前结点是否可通*/
	bool Pass(int(*map)[MAP_LOW], PosType curpos);
	/*根据当前方向定位到下一个结点*/
	PosType NextPos(PosType seat, int di);
};