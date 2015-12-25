/**************
MonsterAI
***************/
#include "MonsterAI.h"
#include <time.h>

MonsterAI::MonsterAI() {}
MonsterAI::~MonsterAI() {}

MonsterAI* MonsterAI::create(GameObject* owner) {
    auto mAI = new MonsterAI();
    mAI->init(owner);
    return mAI;
}

bool MonsterAI::init(GameObject* owner) {
    if (!Ability::init(owner)) {
        return false;
    }
    this->setName("MonsterAI");
    this->getOwner()->setVelocity(0, 0);

    //��ʼ����ͼ��Ϣ
    this->setMapInfo(MapController::getInstance()->mapInfo);
    //���ɹ������꼰��״̬
    this->start = { 10,20 };
    this->curPos = this->nextPos = this->start;
	this->flag = 0;
    //��������ص���ͼ��
    owner->setPositionX(MapController::getInstance()->getXPositionInWorld(this->start.posY));
    owner->setPositionY(MapController::getInstance()->getYPositionInWorld(this->start.posX));
    owner->setSize(10);
    //��ȡplayer����
    this->player = owner->getParent()->getChildByName("player");
    this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
    this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
	srand(time(0));

    return true;
}

void MonsterAI::update() {
    auto owner = this->getOwner();
	if ((player != NULL) &&
		this->curPos.posX == MapController::getInstance()->getYPositionInMap(player->getPositionY()) &&
		this->curPos.posY == MapController::getInstance()->getXPositionInMap(player->getPositionX())) {
		this->player = NULL;
		printf("find it\n");
	}
	if ((this->count % 400) == 0 && (this->player != NULL) && this->flag != 2 && this->flag != 3) {
        this->start = this->nextPos;
		this->path.Clear();
		//����playerλ�ú͵�ͼ��Ϣ
		this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
		this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
        this->setMapInfo(MapController::getInstance()->mapInfo);
		//����·��
        if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) &&
			(start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE) &&
			this->flag == 0) {
            BFSPath(this->map, this->start, this->end, this->path);
			this->flag = 1;
			printf("\nflag = 1,BFS\n");
        }
        else {
            DFSPath(this->map, this->start, this->end, this->path);
			this->flag = 0;
			printf("\nflag = 0,DFS\n");
        }
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
    }
	if ((this->count % 20) == 0 && this->flag != 4) {
        this->curPos = this->nextPos;
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
        if (this->curPos.posX == this->nextPos.posX&&
			this->curPos.posY == this->nextPos.posY) {
			if (this->player == NULL) {
				if (this->curPos.posX == 10 && this->curPos.posY == 20) {
					this->flag = 4;
				}
				else {
					this->start = this->nextPos;
					this->path.Clear();
					this->end = { 10,20 };
					this->setMapInfo(MapController::getInstance()->mapInfo);
					BFSPath(this->map, this->start, this->end, this->path);
					if (!this->path.Empty()) {
						this->path.Pop(this->nextPos);
					}
					this->flag = 2;
					this->curPos = this->nextPos;
					if (!this->path.Empty()) {
						this->path.Pop(this->nextPos);
					}
				}
			}
			else{
				this->start = this->nextPos;
				this->path.Clear();
				this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
				this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
				this->setMapInfo(MapController::getInstance()->mapInfo);
				if (this->flag == 2) {
					DFSPath(this->map, this->start, this->end, this->path);
					this->flag = 3;
					printf("\nrestrat,DFS\n", this->flag);
				}
				else {
					BFSPath(this->map, this->start, this->end, this->path);
					this->flag = 2;
					printf("\nrestrat,BFS\n", this->flag);
				}
				if (!this->path.Empty()) {
					this->path.Pop(this->nextPos);
				}
				this->curPos = this->nextPos;
				if (!this->path.Empty()) {
					this->path.Pop(this->nextPos);
				}
			}
        }
    }
    MoveByPath();
    this->count++;
}

//�������ɵ�·������
void MonsterAI::MoveByPath() {
    auto owner = this->getOwner();
    //�����յ�
    if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
        return;
    }
    //ˮƽ�ƶ�
    else if (this->curPos.posX == this->nextPos.posX) {
        if (this->curPos.posY < this->nextPos.posY) {
            owner->setPositionX(owner->getPositionX() + 1);		//�����˶�
        }
        else {
            owner->setPositionX(owner->getPositionX() - 1);		//�����˶�
        }
    }
    //��ֱ�ƶ�
    else if (this->curPos.posY == this->nextPos.posY) {
        if (this->curPos.posX < this->nextPos.posX) {
            owner->setPositionY(owner->getPositionY() - 1);		//�����˶�
        }
        else {
            owner->setPositionY(owner->getPositionY() + 1);		//�����˶�
        }
    }
}

//���õ�ͼ��Ϣ
void MonsterAI::setMapInfo(int(*map)[40]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            this->map[i][j] = map[i][j];
        }
    }
}

bool MonsterAI::BFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Queue<WElemType> Q;
	WElemType e, e1;
	MPosType curPos, nextPos;
	int di = 1, curVexs[20][40];
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

bool MonsterAI::DFSPath(int(*map)[MAP_LOW], MPosType start, MPosType end, Stack<MPosType> &path) {
	Stack<DElemType> S;
	DElemType e;
	MPosType curPos;
	int curstep;
	this->rndDi = rand() % 4;

	curPos = start;
	curstep = 1;

	do {
		if (Pass(map, curPos)) {
			map[curPos.posX][curPos.posY] = -1;	      //������ͨ·�ĵ�ͼ�����־Ϊ����ͨ
			e = { curstep,curPos,1 };
			//printf("%d,%d\n", e.seat.posX, e.seat.posY);
			S.Push(e);
			if ((curPos.posX == end.posX) && (curPos.posY == end.posY)) {
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

/*�жϵ�ǰ����Ƿ��ͨ*/
bool MonsterAI::Pass(int(*map)[MAP_LOW], MPosType curPos) {
	if (map[curPos.posX][curPos.posY] == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*���ݵ�ǰ����λ����һ�����*/
MPosType MonsterAI::NextPos(MPosType seat, int di) {
	switch ((di + this->rndDi) % 4 + 1) {
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

