#pragma once

#include<iostream>
using namespace std;

#define MAXQSIZE 100		//最大队列长度

template<typename T>
class Queue {
private:
	T *base;		//初始化的动态分配存储空间
	int front;		//头指针，若队列不空，指向队头元素
	int rear;		//尾结点，若队列不空，指向队尾元素的下一个位置
public:

	Queue() {
		base = (T *)malloc(MAXQSIZE*sizeof(T));	//动态分配内存
		front = rear = 0;
	}
	
	~Queue() {

	}

	//清空队列
	bool Clear() {
		rear = front = 0;
		return true;
	}

	//判断队列是否为空
	bool Empty() {
		if (rear == front) return true; //队列为空
		return false;					//队列不空
	}

	//获取队列元素个数
	int Length() {
		return rear >= front ? rear - front : rear - front + MAXQSIZE;
	}

	//获取队头元素
	bool GetHead(T &e) {
		if (rear == front) return false;	//队列为空
		e = base[front];					//返回队头元素
		return true;
	}

	//将数据元素入队
	bool EnQueue(T e) {
		if ((rear + 1) % MAXQSIZE == front) return false;	//队满
		base[rear] = e;										//插入数据元素
		rear = (rear + 1) % MAXQSIZE;						//队尾指针后移
		return true;
	}

	//删除队头元素
	bool DeQueue(T &e) {
		if (rear == front) return false;	//队空
		e = base[front];					//用e返回删除的数据元素
		front = (front + 1) % MAXQSIZE;		//队头指针后移
		return true;
	}
};