#include "SimpleGE.h"

PathGenerator* PathGenerator::sharedGenerator = nullptr;

PathGenerator::PathGenerator() {}

PathGenerator::~PathGenerator() {}

/*****************
Create Monster Path
******************/

/*�������������������·��*/
bool PathGenerator::DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Stack<DElemType> S;
	DElemType e;
	MPosType curPos;
	int curstep;
	this->rndDi = rand() % 4 ;

	curPos = start;
	curstep = 1;

	do {
		if (Pass(map,curPos)) {
			map[curPos.posX][curPos.posY] = -1;	      //������ͨ·�ĵ�ͼ�����־Ϊ����ͨ
			e = { curstep,curPos,1 };
			//printf("%d,%d\n", e.seat.posX, e.seat.posY);
			S.Push(e);
			if ((curPos.posX == end.posX)&&(curPos.posY == end.posY)) {
				//�Ѿ����ɴ���㵽�յ��ͨ·
				//��ջS�е�Ԫ������ȡ������������ջ��path�У���path����ͨ·������
				printf("\nDFS\n");
				while (!S.Empty()) {
					S.Pop(e);
					curPos = e.seat;
					printf("(%d,%d)->", curPos.posX, curPos.posY);
					path.Push(curPos);
				}
				return true;
			}
			else {
				curstep++;
				curPos = NextPos(e.seat, e.di);
			}
		}
		else {
			if (!S.Empty()) {
				S.Pop(e);
				//·������ͨ������
				while (e.di == 4 && !S.Empty()) {
					map[e.seat.posX][e.seat.posY] = 0; //�����˳����ĵ�ͼ�����־Ϊ��ͨ
					S.Pop(e);
				}
				//̽����������
				if (e.di < 4) {
					e.di++;
					S.Push(e);
					curPos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!S.Empty());

	return false;				  //�Ѿ��ҵ���ʼ���յ��ͨ·������true
}

/*���ݹ��������������·��*/
bool PathGenerator::BFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Queue<WElemType> Q;
	WElemType e,e1;
	MPosType curPos,nextPos;
	int di = 1,curVexs[20][40];
	this->rndDi = 0;

	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_LOW; j++) {
			curVexs[i][j] = 0;
		}
	}
	curPos = start;

	curVexs[curPos.posX][curPos.posY] = 1;	
	map[curPos.posX][curPos.posY] = 1;
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_LOW; j++) {
			e.vexs[i][j] = curVexs[i][j];
		}
	}
	e.seat = curPos;
	Q.EnQueue(e);

	do {
		if (!Q.Empty()) {
			Q.DeQueue(e);
			for (int i = 0; i < MAP_ROW; i++) {
				for (int j = 0; j < MAP_LOW; j++) {
					curVexs[i][j] = e.vexs[i][j];
				}
			}
		}
		for (int di = 1; di <= 4; di++) {
			curPos = NextPos(e.seat, di);
			if (Pass(map, curPos)) {
				map[curPos.posX][curPos.posY] = 1;
				curVexs[curPos.posX][curPos.posY] = 1;
				for (int i = 0; i < MAP_ROW; i++) {
					for (int j = 0; j < MAP_LOW; j++) {
						e1.vexs[i][j] = curVexs[i][j];
					}
				}
				e1.seat = curPos;
				Q.EnQueue(e1);
				if ((curPos.posX == end.posX) && (curPos.posY == end.posY)) {
					//�Ѿ����ɴ���㵽�յ��ͨ·
					//������Q�е�Ԫ������ȡ������������ջ��path�У���path����ͨ·������
					curPos = end;
					printf("\nBFS\n");
					while (curVexs[curPos.posX][curPos.posY]) {
						printf("(%d,%d)->", curPos.posX, curPos.posY);
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
		}
	} while (!Q.Empty());

	return false;
}

/*�жϵ�ǰ����Ƿ��ͨ*/
bool PathGenerator::Pass(int(*map)[MAP_LOW], MPosType curPos) {
	if (map[curPos.posX][curPos.posY] == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*���ݵ�ǰ����λ����һ�����*/
MPosType PathGenerator::NextPos(MPosType seat, int di) {
	switch ((di + this->rndDi)%4 + 1) {
	case 1:			//�����ƶ�һ��
		seat = { seat.posX + 1,seat.posY };
		break;
	case 2:			//�����ƶ�һ��
		seat = { seat.posX,seat.posY + 1 };
		break;
	case 3:			//�����ƶ�һ��
		seat = { seat.posX - 1,seat.posY };
		break;
	case 4:			//�����ƶ�һ��
		seat = { seat.posX,seat.posY - 1 };
		break;
	}
	return seat;
}