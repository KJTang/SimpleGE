#include "CreatePath.h"

/*****************
Create Monster Path
******************/

/*���ݵ�ͼ���ɴ���㵽�յ��ͨ·*/
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
			map[curpos.posX][curpos.posY] = -1;	      //������ͨ·�ĵ�ͼ�����־Ϊ����ͨ
			e = { curstep,curpos,1 };
			//printf("%d,%d\n", e.seat.posX, e.seat.posY);
			S.Push(e);
			if ((curpos.posX == end.posX)&&(curpos.posY == end.posY)) {
				//�Ѿ����ɴ���㵽�յ��ͨ·
				//��ջS�е�Ԫ������ȡ������������ջ��path�У���path����ͨ·������
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
				//·������ͨ������
				while (e.di == 4 && !S.Empty()) {
					map[e.seat.posX][e.seat.posY] = 0; //�����˳����ĵ�ͼ�����־Ϊ��ͨ
					S.Pop(e);
				}
				//̽����������
				if (e.di < 4) {
					e.di++;
					S.Push(e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!S.Empty());

	return false;				  //�Ѿ��ҵ���ʼ���յ��ͨ·������true
}

/*�жϵ�ǰ·������Ƿ��ͨ*/
bool Pass(int(*map)[MAP_LOW], PosType curpos) {
	if (map[curpos.posX][curpos.posY] == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*���ݵ�ǰ�����ƶ�����һ��*/
PosType NextPos(PosType seat, int di) {
	switch (di) {
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