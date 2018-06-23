#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAXQSIZE 1000
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//坐标点
typedef struct
{
	int x;//x
	int y;//y
	int di;//方向
	int node_id;   //当前节点的序号，以便传递给孩子节点
	int parent_id; //保存父节点的位置 
}Block;//坐标点

