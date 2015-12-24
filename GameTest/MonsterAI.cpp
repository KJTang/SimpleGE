#include "MonsterAI.h"
#include "PathGenerator.h"
#include <time.h>

/**************
MonsterAI
***************/
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

    return true;
}

void MonsterAI::update() {
    auto owner = this->getOwner();
	if ((player != NULL) &&
		this->curPos.posX == MapController::getInstance()->getYPositionInMap(player->getPositionY()) &&
		this->curPos.posY == MapController::getInstance()->getXPositionInMap(player->getPositionX())) {
		this->player->removeFromParent();
		this->player = NULL;
		this->flag = 2;
		printf("find it\n");
	}
	if ((this->count % 400) == 0 && (this->player != NULL)) {
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
            PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
			this->flag = 1;
			printf("flag = 1,BFS\n");
        }
        else {
            PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
			this->flag = 0;
			printf("flag = 0,DFS\n");
        }
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
    }
    if ((this->count % 20) == 0) {
        this->curPos = this->nextPos;
        if (!this->path.Empty()) {
            this->path.Pop(this->nextPos);
        }
        if (this->curPos.posX == this->nextPos.posX&&
			this->curPos.posY == this->nextPos.posY) {
			if (this->flag == 2) {
				this->start = this->nextPos;
				this->path.Clear();
				this->end = { 10,20 };
				this->setMapInfo(MapController::getInstance()->mapInfo);
				PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
				printf("flag = 2,BFS\n");
			}
			else{
				this->start = this->nextPos;
				this->path.Clear();
				this->end.posY = MapController::getInstance()->getXPositionInMap(player->getPositionX());
				this->end.posX = MapController::getInstance()->getYPositionInMap(player->getPositionY());
				this->setMapInfo(MapController::getInstance()->mapInfo);
				PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
				printf("flag = 2,DFS\n");
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
