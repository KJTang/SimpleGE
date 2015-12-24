/* Project:		PacMan
File Name:		Stack.h
Author:			�ּζ�
Date:			2015/12/11
Purpose:		ADT Stack�����ݶ������ݹ�ϵ���ͻ�������������*/

#ifndef _Stack
#define _Stack

#include<iostream>
/*ջ�Ĵ����ʼ�������ʹ����������*/
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

/*Stack��Ķ��壬����Stack�����ݶ������ݹ�ϵ�ͻ�������*/
template<typename T>
class Stack {
private:
	T *base;
	T *top;
	int stackSize;
public:
	Stack() {
		base = (T *)malloc(STACK_INIT_SIZE * sizeof(T));
		top = base;
		stackSize = STACK_INIT_SIZE;
	}
	
	~Stack() {

	}

	/*���ջ*/
	bool Clear() {
		top = base;
		return true;
	}

	/*�ж�ջ�Ƿ�Ϊ�գ�Ϊ�շ���true,�ǿշ���false*/
	bool Empty() {
		return base == top ? true : false;
	}

	/*��ȡջ�ĳ���*/
	int Length() {
		return top - base;
	}

	/*��ȡջS��ջ��Ԫ��*/
	T GetTop() {
		if (base == top) return NULL;
		return *(top - 1);				//����ջ��Ԫ��
	}

	/*��Ԫ��e��ջ*/
	bool Push(T e) {
		if (top - base >= stackSize) {		//ջ����׷�Ӵ洢�ռ�
			base = (T *)realloc(base, (stackSize + STACKINCREMENT)*sizeof(T));
			if (!base) return false;				//����ʧ�ܣ�����ERROR
			top = base + stackSize;
			stackSize += STACKINCREMENT;
		}
		*top++ = e;								//������ջ
		return true;
	}

	/*��ջ��Ԫ�س�ջ������e����*/
	bool Pop(T &e) {
		if (top == base) return false;		//ջ��
		e = *--top;							//��ջ��Ԫ�س�ջ
		return true;
	}

	/*��������ջS*/
	bool Traverse() {
		if (top == base) return false;		//ջ��
		printf("---------------all elem------------\n");
		for (int i = 0; i < top - base; i++) {
			printf(" %d ", *(base + i));
		}
		printf("\n-----------------end---------------\n");
		return true;
	}
};

#endif