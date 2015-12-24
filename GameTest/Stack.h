/* Project:		PacMan
File Name:		Stack.h
Author:			林嘉栋
Date:			2015/12/11
Purpose:		ADT Stack的数据对象，数据关系，和基本操作的声明*/

#ifndef _Stack
#define _Stack

#include<iostream>
/*栈的储存初始分配量和储存分配增量*/
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

/*Stack类的定义，包括Stack的数据对象，数据关系和基本操作*/
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

	/*清空栈*/
	bool Clear() {
		top = base;
		return true;
	}

	/*判断栈是否为空，为空返回true,非空返回false*/
	bool Empty() {
		return base == top ? true : false;
	}

	/*获取栈的长度*/
	int Length() {
		return top - base;
	}

	/*获取栈S的栈顶元素*/
	T GetTop() {
		if (base == top) return NULL;
		return *(top - 1);				//返回栈顶元素
	}

	/*将元素e入栈*/
	bool Push(T e) {
		if (top - base >= stackSize) {		//栈满，追加存储空间
			base = (T *)realloc(base, (stackSize + STACKINCREMENT)*sizeof(T));
			if (!base) return false;				//分配失败，返回ERROR
			top = base + stackSize;
			stackSize += STACKINCREMENT;
		}
		*top++ = e;								//进行入栈
		return true;
	}

	/*将栈顶元素出栈，并用e返回*/
	bool Pop(T &e) {
		if (top == base) return false;		//栈空
		e = *--top;							//将栈顶元素出栈
		return true;
	}

	/*遍历访问栈S*/
	bool Traverse() {
		if (top == base) return false;		//栈空
		printf("---------------all elem------------\n");
		for (int i = 0; i < top - base; i++) {
			printf(" %d ", *(base + i));
		}
		printf("\n-----------------end---------------\n");
		return true;
	}
};

#endif