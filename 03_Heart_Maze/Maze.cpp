/***************************************************************************************************/
/*                     由于本人比较笨，所以注释有点多，而且还很丑                                   */
/****************************************************************************************************/
/*                     代码是：自动生成心型迷宫+广度遍历自动寻路                                    */
/****************************************************************************************************/
/*                     代码是从github上下载的，原作者采用的深度遍历寻路                             */
/*                     我将代码改为了广度遍历寻路                                                   */
/****************************************************************************************************/
/*                      感谢原作者：https://github.com/neolay/HeartMaze                                 */

#include "stdafx.h"
#include "Maze.h"

//N=37,M=47
bool visited[N][M]; //被访问过的坐标点
bool mask[N][M]; //该点的周围8个坐标不全在方形中，遮罩
bool area[N][M];//心形坐标点，在心形中的坐标为true
int di[4][2] = { { 0,1 },
                 { 1,0 },
                 { 0,-1 },
                 { -1,0 } };

int main()
{
	system("mode con cols=96 lines=40");
	system("title Heart_Maze");
	system("color 0A");//0是背景色代号，A是前景色代号
	Maze maze[N][M];//最终布局地图
	Block in, out;  //入口，出口坐标点
	gotoxy(38, 38);
	printf("心形地图生成中。。。");
	initMaze(maze, in, out);//布局地图
	gotoxy(34, 38);
	printf("正在自动寻找最短路。。。");
	findPath(maze, in, out);//自动寻路
	gotoxy(38, 38);
	system("pause");
	return 0;
}

//布局地图
void initMaze(Maze maze[N][M], Block &in, Block &out)
{
	initHeart();//利用函数构建心形坐标,存放到数组area中
	srand(static_cast<unsigned int>(time(NULL)));//随机数种子

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{                                  //如果该坐标点在心形中且上下左右只要有一个false,就将该点设置成外墙
			if (area[i][j] && !(area[i][j - 1] && area[i][j + 1] && area[i - 1][j] && area[i + 1][j]))
				maze[i][j] = OUTWALL; //外墙
			else if (area[i][j] && i % 2 == 0 && j % 2 == 0) //如果该坐标点在心形中且横纵坐标点都为偶数
				maze[i][j] = ROAD;    //路
			else if (area[i][j])                  //如果该坐标点在心形中且不满足上面条件，就是内墙
				maze[i][j] = INWALL;  //内墙
			else                          //如果该坐标点在心形坐标外面，就将该点设置成空白
				maze[i][j] = EMPTYWALL;//空白
			visited[i][j] = false;//未被访问过的点
			mask[i][j] = true;//不显示的点
		}
	}
	//入口坐标
	in.x = 1;         
	in.y = 6;
	//出口坐标
	out.x = 27;       
	out.y = 36;
	maze[in.x][in.y] = maze[out.x][out.y] = ROAD;//设置入口/出口
	SqQueue S;     //队列
	Block start;   //坐标点
	initQueue(S);  //为队列分配1000个坐标空间
	start.x = 2;   //入口点下面的坐标
	start.y = 6;
	enQueue(S, start);  //将坐标点放入队列
	visited[start.x][start.y] = true;
	clearMask(start.x, start.y);//判断该坐标点周围8个坐标点是否全在该方形地图中
	while (!isEmpty(S))//判断队列是否为空
	{
		Block curBlock;
		deQueue_rand(S, curBlock);//随机取出队列中的一个坐标点
		for (int i = 0; i < 4; i++)
		{              //该坐标点的：下 左 上 右 两个单元
			int nextBlockX = curBlock.x + di[i][0] * 2; //0 2 0 -2
			int nextBlockY = curBlock.y + di[i][1] *2;  //2 0 -2 0

			//是先假设地图上有相间隔的点，然后将这些点进行打通，
      		//只要这个点是孤立的，就可以与其他点连通，

			    //如果该点的周围有孤立点且在方形坐标中且是路且未被访问过
			if (inMaze(nextBlockX, nextBlockY) && maze[nextBlockX][nextBlockY] == ROAD && !visited[nextBlockX][nextBlockY])
			{
				Block nextBlock;
				nextBlock.x = nextBlockX;
				nextBlock.y = nextBlockY;
				enQueue(S, nextBlock);   //将该孤立点加入队列           
				maze[curBlock.x + di[i][0]][curBlock.y + di[i][1]] = ROAD;   //将该点和孤立点之间联通
				visited[nextBlockX][nextBlockY] = true; //标记该孤立点已被访问过
				clearMask(nextBlockX, nextBlockY);//去掉该点周围的遮掩，对于当前没有遍历到的格点不给予显示，随着遍历的进行逐个显示出已遍历到的格点。
				updateMaze(maze);//为地图布局，刷新地图
			}
		}
	}
	//心形图案的最外层，将遮掩掉的外传显示出来
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (maze[i][j] == OUTWALL)
			{
				mask[i][j] = false;
				updateMaze(maze);
			}
		}
	}
}

//自动寻路
void findPath(Maze maze[N][M], Block in, Block out)
{
	Block block = in;
	block.node_id = 0;
	block.parent_id = -1;
	Block block_const;
	SqQueue S;     //队列
	initQueue(S);  //为队列分配1000个坐标空间
	enQueue(S, block);  //将坐标点放入队列
	int curBlockX = in.x;
	int curBlockY = in.y;
	int step = 1;
	do {  
		gotoxy(78,30);
		printf("第%d步", step);

		deQueue(S, block);//取出队列中的第一个
		block_const = block;
		for (int i = 0; i < 4; i++)
		{                        
			block = block_const;//每次保持中心节点不变
			int curBlockX = block.x + di[i][0];
			int curBlockY = block.y + di[i][1];//下左上右四个方向
	
		   //如果改点在方形地图中且所在点是路
			if (inMaze(curBlockX, curBlockY) && maze[curBlockX][curBlockY] == ROAD)
			{
				initBlock(block, curBlockX, curBlockY, BACK);//将其标记为走过的路
				block.node_id = step;//记录该节点所在队列序号
				block.parent_id = block_const.node_id; //记录该节点的父节点所在队列序号
				enQueue(S, block);//将该点入队
				maze[curBlockX][curBlockY] = block.di;
				updateMaze(maze);//更新地图
				//如果寻路成功
				if (curBlockX == out.x&&curBlockY == out.y)
				{
					SqStack Stack;//创建一个栈
					initStack(Stack);//为栈分配内存

					block.parent_id = S.rear - 1; //找到队列中出口点的下标
					while (block.parent_id != -1)//当该点不是入口时
					{      //将队列当作数组使用
						curBlockX = S.base[block.parent_id].x;
						curBlockY = S.base[block.parent_id].y;
						initBlock(block, curBlockX, curBlockY, ROAD);//将该点设置成路		
						push(Stack, block);//并将其如栈 ，先入后出
						block.parent_id = S.base[block.parent_id].parent_id;//修改其父节点序号
					}
					gotoxy(34, 38);
					printf("最短路径寻找成功。。。。");
					while (!isEmpty(Stack))
					{
						pop(Stack, block);//取出队列中的第一个
						maze[block.x][block.y] = block.di;//修改地图
						updateMaze(maze);
					}

					//沿着最短路径前行
					curBlockX = in.x;
					curBlockY = in.y;
					int num=1;
					gotoxy(34, 38);
					printf("正在沿着最短路径前行。。。。");
					do{
						gotoxy(78, 31);
						printf("第%d步", num);
						if (inMaze(curBlockX, curBlockY) && maze[curBlockX][curBlockY] == ROAD)
						{
							initBlock(block, curBlockX, curBlockY, EAST);//右边  设置该坐标点的方向
							maze[curBlockX][curBlockY] = block.di;
							updateMaze(maze);
							if (curBlockX == out.x&&curBlockY == out.y)
							{
								gotoxy(74, 31);
								printf("寻路成功,最短共%d步", num);
								Sleep(5000);
								gotoxy(74, 33);
								system("pause");
								return;
							}
							curBlockX = nextBlockX(block.x, block.di);
							curBlockY = nextBlockY(block.y, block.di);
							num++;
						}
						else
						{
							if (block.di < NORTH)//上
							{
								block.di++;
								maze[block.x][block.y] = block.di;
								curBlockX = nextBlockX(block.x, block.di);
								curBlockY = nextBlockY(block.y, block.di);
								updateMaze(maze);
							}

						}
					} while (true);
				}
			
				step++;
			}
		}
	
	} while (!isEmpty(S));
	gotoxy(78, 30);
	printf("寻路失败");
}

//标记该坐标点的方向
void initBlock(Block &block, int x, int y, int di)
{
	block.x = x;
	block.y = y;
	block.di = di;
}

//画地图
void showBlock(Maze maze[N][M])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (mask[i][j] == true)
				printf("  ");
			else if (maze[i][j] == INWALL)//内墙
				printf("█");
			else if (maze[i][j] == OUTWALL)//外墙
				printf("█");
			else if (maze[i][j] == EMPTYWALL)
				printf("  ");
			else if (maze[i][j] == ROAD)
				printf("  ");
			else if (maze[i][j] == BACK)
				printf("□");
			else if (maze[i][j] == EAST)
				printf("→");
			else if (maze[i][j] == SOUTH)
				printf("↓");
			else if (maze[i][j] == WEST)
				printf("←");
			else if (maze[i][j] == NORTH)
				printf("↑");
			if (j != 0 && j % (M - 1) == 0)
				printf("\n");
		}
	}
}

//为地图布局,刷新地图
void updateMaze(Maze maze[N][M])
{
	hideCursor();//设置指定的控制台光标的大小和可见性。
	gotoxy(0,0);//设置光标位置  左上角
	showBlock(maze);  //画地图
	Sleep(DELAY);
}

//判断下一个位置
int nextBlockX(int a, int di)
{
	int x = a;
	switch (di)
	{
		case SOUTH://下
			x++;
			break;
		case NORTH://上
			x--;
			break;
		default:
			break;
	}
	return x;
}

int nextBlockY(int b, int di)
{
	int y = b;
	switch (di)
	{
		case EAST://右
			y++;
			break;

		case WEST://左
			y--;
			break;
		default:
			break;
	}
	return y;
}

//判断该坐标点在方形地图中
bool inMaze(int x, int y)
{
	return x >= 0 && x < N&&y >=0 && y < M;
}

//判断该坐标点周围8个坐标点是否全在该方形地图中，用于显示该点周围的墙
void clearMask(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (inMaze(i, j)) //在地图中
				mask[i][j] = false;
}

//设置光标位置
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}




//设置指定的控制台光标的大小和可见性。
void hideCursor()
{                                               //光标厚度，是否隐藏
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //这个结构包含的是控制台光标的信息
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//用来设置指定的控制台光标的大小和可见性。
}

//利用函数构建心形坐标,存放到数组area中
void initHeart()
{
	int i = 0, j = 0;
	for (float y = 1.2f; y > -1.0f; y -= 0.06f)
	{
		for (float x = -1.1f; x < 1.2f; x += 0.05f)
		{
			float a = x * x + y * y - 1;
			if (a * a * a - x * x * y * y * y <= 0.0f)
				area[i][j] = true;
			else
				area[i][j] = false;
			j++;
		}
		i++;
		j = 0;
	}
}