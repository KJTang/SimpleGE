#include "SimpleGE.h"

PathGenerator* PathGenerator::sharedGenerator = nullptr;

PathGenerator::PathGenerator() {}

PathGenerator::~PathGenerator() {}

/*****************
Create Monster Path
******************/

/*根据深度优先搜索生成路线*/
bool PathGenerator::DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Stack<DElemType> S;
	DElemType e;
	MPosType curPos;
	int curstep;

	curPos = start;
	curstep = 1;

	do {
		if (Pass(map,curPos)) {
			map[curPos.posX][curPos.posY] = -1;	      //将加入通路的地图坐标标志为不可通
			e = { curstep,curPos,1 };
			//printf("%d,%d\n", e.seat.posX, e.seat.posY);
			S.Push(e);
			if ((curPos.posX == end.posX)&&(curPos.posY == end.posY)) {
				//已经生成从起点到终点的通路
				//将栈S中的元素依次取出并将坐标入栈到path中，用path返回通路的坐标
				while (!S.Empty()) {
					S.Pop(e);
					curPos = e.seat;
					printf("%d,%d\n", e.seat.posX,e.seat.posY);
					path.Push(curPos);
				}
				return true;
			}
			else {
				curstep++;
				curPos = NextPos(e.seat, e.di);
				//printf("%d,%d\n", curpos.posX, curpos.posY);
			}
		}
		else {
			if (!S.Empty()) {
				S.Pop(e);
				//路径不可通，回溯
				while (e.di == 4 && !S.Empty()) {
					map[e.seat.posX][e.seat.posY] = 0; //将后退出来的地图坐标标志为可通
					S.Pop(e);
				}
				//探索其他方向
				if (e.di < 4) {
					e.di++;
					S.Push(e);
					curPos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!S.Empty());

	return false;				  //已经找到开始到终点的通路，返回true
}

/*根据广度优先搜索生成路线*/
bool PathGenerator::WFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Queue<WElemType> Q;
	WElemType e,e1;
	MPosType curPos,nextPos;
	int di = 1,curVexs[20][40];

	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_LOW; j++) {
			curVexs[i][j] = 0;
		}
	}
	curPos = start;

	curVexs[curPos.posX][curPos.posY] = 1;	
	map[curPos.posX][curPos.posY] = -1;	      //将加入通路的地图坐标标志为不可通
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_LOW; j++) {
			e.vexs[i][j] = curVexs[i][j];
		}
	}
	e.seat = curPos;

	do {
		if (di <= 4) {
			curPos = NextPos(e.seat, di);
			if (Pass(map, curPos)) {
				map[curPos.posX][curPos.posY] = -1;	      //将加入通路的地图坐标标志为不可通
				curVexs[curPos.posX][curPos.posY] = 1;
				for (int i = 0; i < MAP_ROW; i++) {
					for (int j = 0; j < MAP_LOW; j++) {
						e1.vexs[i][j] = curVexs[i][j];
					}
				}
				e1.seat = curPos;
				Q.EnQueue(e1);
				if ((curPos.posX == end.posX) && (curPos.posY == end.posY)) {
					//已经生成从起点到终点的通路
					//将队列Q中的元素依次取出并将坐标入栈到path中，用path返回通路的坐标
					curPos = end;
					while (curVexs[curPos.posX][curPos.posY]) {
						printf("%d,%d\n", curPos.posX, curPos.posY);
						path.Push(curPos);
						curVexs[curPos.posX][curPos.posY] = 0;
						for (int i = 1; i <= 4; i++) {
							nextPos = NextPos(curPos, i);
							if (curVexs[nextPos.posX][nextPos.posY]) {
								break;
							}
						}
						curPos.posX = nextPos.posX;
						curPos.posY = nextPos.posY;
					}
					return true;
				}
				curVexs[curPos.posX][curPos.posY] = 0;
			}
			di++;
		}
		else {
			if (!Q.Empty()) {
				Q.DeQueue(e);
				di = 1;
				for (int i = 0; i < MAP_ROW; i++) {
					for (int j = 0; j < MAP_LOW; j++) {
						curVexs[i][j] = e.vexs[i][j];
					}
				}
			}
		}
	} while (!Q.Empty());

	return false;
}

/*判断当前结点是否可通*/
bool PathGenerator::Pass(int(*map)[MAP_LOW], MPosType curPos) {
	if (map[curPos.posX][curPos.posY] == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*根据当前方向定位到下一个结点*/
MPosType PathGenerator::NextPos(MPosType seat, int di) {
	switch (di) {
	case 1:			//向下移动一步
		seat = { seat.posX + 1,seat.posY };
		break;
	case 2:			//向右移动一步
		seat = { seat.posX,seat.posY + 1 };
		break;
	case 3:			//向上移动一步
		seat = { seat.posX - 1,seat.posY };
		break;
	case 4:			//向左移动一步
		seat = { seat.posX,seat.posY - 1 };
		break;
	}
	return seat;
}