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

	//初始化地图信息
	this->setMapInfo(MapController::getInstance()->mapInfo);
	//生成怪物坐标及其状态
	this->start = { 10,20 };
	this->curPos = this->nextPos = this->start;
	this->flag = 0;
	//将怪物加载到地图上
	owner->setPositionX(MapController::getInstance()->getXPositionInWorld(this->start.posY));
	owner->setPositionY(MapController::getInstance()->getYPositionInWorld(this->start.posX));
	owner->setSize(10);
	//获取player坐标
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
		//更新player位置和地图信息
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
		//更新路径
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

//根据生成的路径行走
void MonsterAI2::MoveByPath() {
	auto owner = this->getOwner();
	//到达终点
	if (this->curPos.posX == this->nextPos.posX&&this->curPos.posY == this->nextPos.posY) {
		return;
	}
	//水平移动
	else if (this->curPos.posX == this->nextPos.posX) {
		if (this->curPos.posY < this->nextPos.posY) {
			owner->setPositionX(owner->getPositionX() + 1);		//向右运动
		}
		else {
			owner->setPositionX(owner->getPositionX() - 1);		//向左运动
		}
	}
	//垂直移动
	else if (this->curPos.posY == this->nextPos.posY) {
		if (this->curPos.posX < this->nextPos.posX) {
			owner->setPositionY(owner->getPositionY() - 1);		//向下运动
		}
		else {
			owner->setPositionY(owner->getPositionY() + 1);		//向上运动
		}
	}
}

//设置地图信息
void MonsterAI2::setMapInfo(int(*map)[40]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			this->map[i][j] = map[i][j];
		}
	}
}
