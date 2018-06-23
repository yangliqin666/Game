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
}Block;//坐标点