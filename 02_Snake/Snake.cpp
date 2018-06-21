/****************************贪吃蛇**********************************************/
/********************  一个简单的小游戏************************************************/


#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

#define U 1
#define D 2
#define L 3 
#define R 4 //蛇的状态，U：上 ；D：下；L:左 R：右

typedef struct SNAKE //蛇身的一个节点
{
	int x;
	int y;
	struct SNAKE *next;
}snake;

//全局变量//
int score = 0, add = 10;//总得分与每次吃食物得分。
int status, sleeptime = 100;//每次运行的时间间隔
snake *head, *food;//蛇头指针，食物指针
snake *q;//遍历蛇的时候用到的指针
int endgamestatus = 0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。

					   //声明全部函数//
void Pos(int x, int y);                      //选择控制台坐标点
void creatMap();                             //创建游戏地图
void initsnake();                            //初始化蛇身
void createfood();                           //随机刷新食物
int biteself();                              //判断是否咬到了自己
void cantcrosswall();                        //判断是否撞墙
void snakemove();                            //蛇前进,上U,下D,左L,右R
void pause();                                //暂停
void gamecircle();                           //控制游戏 
void welcometogame();                        //开始界面
void endgame();                              //结束游戏
void gamestart();                            //游戏初始化
void deletesnack();						     //释放蛇身





int main()
{
	gamestart();                      //游戏初始化  
	gamecircle();
	endgame();
	return 0;
}








void Pos(int x, int y)//设置光标位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//创建地图
void creatMap()
{
	int i;
	for (i = 0; i<58; i += 2)//打印上下边框
	{
		Pos(i, 0);
		printf("■");
		Pos(i, 26);
		printf("■");
	}
	for (i = 1; i<26; i++)//打印左右边框
	{
		Pos(0, i);
		printf("■");
		Pos(56, i);
		printf("■");
	}
}

//初始化蛇身
void initsnake()
{
	snake *tail;
	int i;
	tail = (snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	while (tail != NULL)//从头到为，输出蛇身
	{
		Pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

//判断是否咬到了自己
int biteself()
{
	snake *self;
	self = head->next;
	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)
		{
			return 1;
		}
		self = self->next;
	}
	return 0;
}

//释放蛇身
void deletesnack()
{
	q = head;
	while (q->next= NULL)
	{
		Pos(q->x, q->y);
		printf(" ");
		q = q->next;
	}
}





//随机出现食物
void createfood()
{
	snake *food_1;
	srand(static_cast<unsigned int>(time(0)));
	food_1 = (snake*)malloc(sizeof(snake));
	while ((food_1->x % 2) != 0) //保证其为偶数，使得食物能与蛇头对齐
	{
		food_1->x = rand() % 52 + 2;
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL)
	{
		if (q->x == food_1->x && q->y == food_1->y) //判断蛇身是否与食物重合
		{
			free(food_1);
			createfood();
		}
		q = q->next;
	}
	Pos(food_1->x, food_1->y);
	food = food_1;
	printf("■");
}

//不能穿墙
void cantcrosswall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		endgamestatus = 1;
		endgame();
	}
}

//蛇前进,上U,下D,左L,右R
void snakemove()
{
	snake * nexthead;
	cantcrosswall();

	nexthead = (snake*)malloc(sizeof(snake));
	if (status == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food->x && nexthead->y == food->y)//如果下一个有食物//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else //如果没有食物//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food->x && nexthead->y == food->y) //有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1) //判断是否会咬到自己
	{
		endgamestatus = 2;
		endgame();
	}
}

//暂停
void pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}

	}
}

//控制游戏 
void gamecircle()
{

	Pos(64, 15);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64, 16);
	printf("用↑.↓.←.→分别控制蛇的移动.");
	Pos(64, 17);
	printf("F1 为加速，F2 为减速\n");
	Pos(64, 18);
	printf("space：暂停游戏.");
	Pos(64, 19);
	printf("ESC ：退出游戏.");

	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("得分：%d ", score);
		Pos(64, 11);
		printf("每个食物得分：%d分", add);

		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus = 3;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				sleeptime = sleeptime - 30;
				add = add + 2;
				if (sleeptime == 320)
				{
					add = 2;//防止减到1之后再加回来有错
				}
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime<350)
			{
				sleeptime = sleeptime + 30;
				add = add - 2;
				if (sleeptime == 350)
				{
					add = 1; //保证最低分为1
				}
			}
		}
		Sleep(sleeptime);
		snakemove();
	}
}

//开始界面
void welcometogame()
{
	Pos(40, 12);

	system("title snake");//设置控制台标题
	printf("欢迎来到贪食蛇游戏！");
	Pos(40, 25);
	system("pause");
	system("cls");
	Pos(25, 12);
	printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，2 为减速\n");
	Pos(25, 13);
	printf("加速将能得到更高的分数。\n");
	Pos(25, 16);
	system("pause");
	system("cls");
}

//结束游戏
void endgame()
{

	system("cls");
	Pos(24, 12);
	if (endgamestatus == 1)
	{
		printf("对不起，您撞到墙了。游戏结束.");
	}
	else if (endgamestatus == 2)
	{
		printf("对不起，您咬到自己了。游戏结束.");
	}
	else if (endgamestatus == 3)
	{
		printf("您的已经结束了游戏。");
	}
	deletesnack();
	Pos(24, 13);
	printf("您的得分是%d\n", score);
	Pos(24, 18);
	system("pause");
	
}

//游戏初始化
void gamestart()
{
	system("mode con cols=100 lines=30"); //设置控制台的大小 宽100/2个字节 高30字节
	welcometogame();
	creatMap();
	initsnake();
	createfood();
}

