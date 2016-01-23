#include "MonsterAI2.h"
#include"myLevel.h"
#include "PathGenerator.h"
#include "PlayerControl.h"
const int DISTANCE = 10;
const int REACH = 1;
static bool i = 0;
/**************
MonsterAI2
***************/
MonsterAI2::MonsterAI2() {}
MonsterAI2::~MonsterAI2() {}

MonsterAI2* MonsterAI2::create(GameObject* owner) {
	auto mAI = new MonsterAI2();
	mAI->init(owner);
	return mAI;
}

bool MonsterAI2::init(GameObject* owner) {
	if (!Ability::init(owner)) {
		return false;
	}
	this->setName("MonsterAI2");
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
	this->player1 = owner->getParent()->getChildByName("player1");
	this->player2 = owner->getParent()->getChildByName("player2");

	game = i;
	if (i)
	{
		this->end.posY = MapController::getInstance()->getXPositionInMap(player1->getPositionX());
		this->end.posX = MapController::getInstance()->getYPositionInMap(player1->getPositionY());
		i = 0;
	}
	else
	{
		this->end.posY = MapController::getInstance()->getXPositionInMap(player2->getPositionX());
		this->end.posX = MapController::getInstance()->getYPositionInMap(player2->getPositionY());
		i = 1;
	}
	return true;
}

void MonsterAI2::update() {
	auto owner = this->getOwner();
	if ((this->curPos.posX - MapController::getInstance()->getYPositionInMap(player1->getPositionY()))*
		(this->curPos.posX - MapController::getInstance()->getYPositionInMap(player1->getPositionY()))+
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player1->getPositionX()))*
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player1->getPositionX()))<REACH) 
	{
		int playerState = static_cast<PlayerControl*>(player1->getAbility("PlayerControl3"))->getPlayerState();
		if (playerState == 0) {
			SystemController::getInstance()->setNextLevel(LevelFail2::create());
			return;
		}
		else if (playerState == 1) {
			static_cast<LevelOne*>(this->getOwner()->getParent())->minusMonster();
			owner->removeFromParent();
			return;
		}
	}
	if ((this->curPos.posX - MapController::getInstance()->getYPositionInMap(player2->getPositionY()))*
		(this->curPos.posX - MapController::getInstance()->getYPositionInMap(player2->getPositionY())) +
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player2->getPositionX()))*
		(this->curPos.posY - MapController::getInstance()->getXPositionInMap(player2->getPositionX()))<REACH)
	{
		int playerState = static_cast<PlayerControl*>(player2->getAbility("PlayerControl2"))->getPlayerState();
		if (playerState == 0) {
			SystemController::getInstance()->setNextLevel(LevelFail2::create());
			return;
		}
		else if (playerState == 1) {
			static_cast<LevelOne*>(this->getOwner()->getParent())->minusMonster();
			owner->removeFromParent();
			return;
		}
	}
	if ((this->count % 400) == 0 && (this->flag == 0 || this->flag == 1)) {
		this->start = this->nextPos;
		this->path.Clear();
		//����playerλ�ú͵�ͼ��Ϣ
		if (game)
		{
			this->end.posY = MapController::getInstance()->getXPositionInMap(player1->getPositionX());
			this->end.posX = MapController::getInstance()->getYPositionInMap(player1->getPositionY());
		}
		else
		{
			this->end.posY = MapController::getInstance()->getXPositionInMap(player2->getPositionX());
			this->end.posX = MapController::getInstance()->getYPositionInMap(player2->getPositionY());
		}
		this->setMapInfo(MapController::getInstance()->mapInfo);
		//����·��
		if ((start.posX - end.posX <= DISTANCE && start.posX - end.posX >= -DISTANCE) &&
			(start.posY - end.posY <= DISTANCE && start.posY - end.posY >= -DISTANCE) &&
			this->flag == 0) {
			PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
			this->flag = 1;
			//printf("\nflag = 1,BFS\n");
		}
		else {
			PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
			this->flag = 0;
			//printf("\nflag = 0,DFS\n");
		}
		if (!this->path.Empty()) {
			this->path.Pop(this->nextPos);
		}
	}
	if ((this->count % 20) == 0 && this->flag != -1) {
		this->curPos = this->nextPos;
		if (!this->path.Empty()) {
			this->path.Pop(this->nextPos);
		}
		if (this->curPos.posX == this->nextPos.posX&&
			this->curPos.posY == this->nextPos.posY) {
			this->start = this->nextPos;
			this->path.Clear();
			if (game)
			{
				this->end.posY = MapController::getInstance()->getXPositionInMap(player1->getPositionX());
				this->end.posX = MapController::getInstance()->getYPositionInMap(player1->getPositionY());
			}
			else
			{
				this->end.posY = MapController::getInstance()->getXPositionInMap(player2->getPositionX());
				this->end.posX = MapController::getInstance()->getYPositionInMap(player2->getPositionY());
			}
			this->setMapInfo(MapController::getInstance()->mapInfo);
			if (this->flag == 2) {
				PathGenerator::getInstance()->DFSPath(this->map, this->start, this->end, this->path);
				this->flag++;
				//printf("\nrestrat,DFS\n");
			}
			else {
				PathGenerator::getInstance()->BFSPath(this->map, this->start, this->end, this->path);
				if (this->flag == 5) {
					this->flag = 2;
				}
				//printf("\nrestrat,BFS\n");
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
void MonsterAI2::MoveByPath() {
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
void MonsterAI2::setMapInfo(int(*map)[40]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			this->map[i][j] = map[i][j];
		}
	}
}
