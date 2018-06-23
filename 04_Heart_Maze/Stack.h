#pragma once
#include "public.h"
//栈
typedef struct
{
	Block *base;//栈底
	Block *top;//栈顶
	int stacksize;//栈长度
}SqStack;

//为栈开辟空间
void initStack(SqStack &S)
{
	S.base = (Block*)malloc(STACK_INIT_SIZE * sizeof(Block));
	if (!S.base)
		return;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

//将坐标点入栈
void push(SqStack &S, Block e)
{
	if (S.top - S.base >= S.stacksize)
	{                             //如果栈满了，重新分配更大的空间
		S.base = (Block*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(Block));
		if (!S.base)
			return;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
}

//坐标点出栈
void pop(SqStack &S, Block&e)
{
	if (S.top == S.base)
		return;
	S.top--;
	e = *S.top;
}

//栈是否为空
bool isEmpty(SqStack S)
{
	if (S.top == S.base)
		return true;
	else
		return false;
}