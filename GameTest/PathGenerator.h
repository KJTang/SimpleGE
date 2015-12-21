#pragma once

#include "Stack.h"
#include "Queue.h"

#define MAP_ROW 20 //数组行数
#define MAP_LOW 40 //数组列数

/*地图坐标类型定义*/
typedef struct MPosType {
	int posX;		//横坐标
	int posY;		//纵坐标
}MPosType;

/*世界坐标类型定义*/
typedef struct WPosType {
	float posX;		//横坐标
	float posY;		//纵坐标
}WPosType;

/*基于宽度优先搜索算法下的路径结点类型定义*/
typedef struct DElemType {
	int ord;		//路径结点在路径上的“序号”
	MPosType seat;	//路径结点在地图上的“坐标位置”
	int di;			//从此结点走向下一结点的“方向”
}DElemType;

/*基于深度优先搜索算法下的路径结点类型定义*/
typedef struct WElemType {
	int vexs[20][40];  //保存从开始结点到当前结点的路径
	MPosType seat;				  //路径结点在地图上的“坐标位置”
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

	/*根据深度优先搜索生成路线*/
	bool DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*根据广度优先搜索生成路线*/
	bool WFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path);
	/*判断当前结点是否可通*/
	bool Pass(int(*map)[MAP_LOW], MPosType curPos);
	/*判断当前结点是否在顶点域中*/
	bool Belong(int(*vexs)[MAP_LOW], MPosType curPos);
	/*根据当前方向定位到下一个结点*/
	MPosType NextPos(MPosType seat, int di);
};