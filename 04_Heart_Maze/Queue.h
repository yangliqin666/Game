#pragma once
#include "public.h"

//队列
typedef struct {

	Block *base;
	int front;//队列尾
	int rear; //队列头
}SqQueue;

//为队列分配1000个坐标空间
void initQueue(SqQueue &Q)
{
	Q.base = (Block*)malloc(MAXQSIZE * sizeof(Block));
	if (!Q.base)
		return;
	Q.front = Q.rear = 0;
}

//将坐标点放入队列
void enQueue(SqQueue &Q, Block e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
		return;

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}

//该队列中的数量
int getLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//随机取出队列中的一个坐标点
void deQueue(SqQueue &Q, Block &e)
{
	if (Q.front == Q.rear)
		return;
	srand(static_cast<unsigned int>(time(NULL)));
	int randIdx = rand() % getLength(Q);
	e = Q.base[randIdx];
	Q.base[randIdx] = Q.base[Q.rear - 1];
	Q.base[Q.rear - 1] = e;

	Q.rear = (Q.rear - 1) % MAXQSIZE;
}

//判断队列是否为空
bool isEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}