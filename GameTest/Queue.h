#pragma once

#include<iostream>
using namespace std;

#define MAXQSIZE 100		//�����г���

template<typename T>
class Queue {
private:
	T *base;		//��ʼ���Ķ�̬����洢�ռ�
	int front;		//ͷָ�룬�����в��գ�ָ���ͷԪ��
	int rear;		//β��㣬�����в��գ�ָ���βԪ�ص���һ��λ��
public:

	Queue() {
		base = (T *)malloc(MAXQSIZE*sizeof(T));	//��̬�����ڴ�
		front = rear = 0;
	}
	
	~Queue() {

	}

	//��ն���
	bool Clear() {
		rear = front = 0;
		return true;
	}

	//�ж϶����Ƿ�Ϊ��
	bool Empty() {
		if (rear == front) return true; //����Ϊ��
		return false;					//���в���
	}

	//��ȡ����Ԫ�ظ���
	int Length() {
		return rear >= front ? rear - front : rear - front + MAXQSIZE;
	}

	//��ȡ��ͷԪ��
	bool GetHead(T &e) {
		if (rear == front) return false;	//����Ϊ��
		e = base[front];					//���ض�ͷԪ��
		return true;
	}

	//������Ԫ�����
	bool EnQueue(T e) {
		if ((rear + 1) % MAXQSIZE == front) return false;	//����
		base[rear] = e;										//��������Ԫ��
		rear = (rear + 1) % MAXQSIZE;						//��βָ�����
		return true;
	}

	//ɾ����ͷԪ��
	bool DeQueue(T &e) {
		if (rear == front) return false;	//�ӿ�
		e = base[front];					//��e����ɾ��������Ԫ��
		front = (front + 1) % MAXQSIZE;		//��ͷָ�����
		return true;
	}
};