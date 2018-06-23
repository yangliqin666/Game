#pragma once
#include "public.h"
//ջ
typedef struct
{
	Block *base;//ջ��
	Block *top;//ջ��
	int stacksize;//ջ����
}SqStack;

//Ϊջ���ٿռ�
void initStack(SqStack &S)
{
	S.base = (Block*)malloc(STACK_INIT_SIZE * sizeof(Block));
	if (!S.base)
		return;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

//���������ջ
void push(SqStack &S, Block e)
{
	if (S.top - S.base >= S.stacksize)
	{                             //���ջ���ˣ����·������Ŀռ�
		S.base = (Block*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(Block));
		if (!S.base)
			return;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
}

//������ջ
void pop(SqStack &S, Block&e)
{
	if (S.top == S.base)
		return;
	S.top--;
	e = *S.top;
}

//ջ�Ƿ�Ϊ��
bool isEmpty(SqStack S)
{
	if (S.top == S.base)
		return true;
	else
		return false;
}