#include "CreatePath.h"

/*****************
Create Monster Path
******************/

/*根据地图生成从起点到终点的通路*/
bool MonsterPath(int (*map)[MAP_LOW], PosType start, PosType end,Stack<PosType> &path) {
	Stack<SElemType> S;
	SElemType e;
	PosType curpos;
	int curstep;

	curpos = start;
	curstep = 1;
	S.Init();

	do {
		if (Pass(map,curpos)) {
			map[curpos.posX][curpos.posY] = -1;	      //将加入通路的地图坐标标志为不可通
			e = { curstep,curpos,1 };
			//printf("%d,%d\n", e.seat.posX, e.seat.posY);
			S.Push(e);
			if ((curpos.posX == end.posX)&&(curpos.posY == end.posY)) {
				//已经生成从起点到终点的通路
				//将栈S中的元素依次取出并将坐标入栈到path中，用path返回通路的坐标
				while (!S.Empty()) {
					S.Pop(e);
					curpos = e.seat;
					printf("%d,%d\n", e.seat.posX,e.seat.posY);
					path.Push(curpos);
				}
				return true;
			}
			else {
				curstep++;
				curpos = NextPos(e.seat, e.di);
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
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!S.Empty());

	return false;				  //已经找到开始到终点的通路，返回true
}

/*判断当前路径结点是否可通*/
bool Pass(int(*map)[MAP_LOW], PosType curpos) {
	if (map[curpos.posX][curpos.posY] == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*根据当前方向移动到下一步*/
PosType NextPos(PosType seat, int di) {
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