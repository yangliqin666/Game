

/****************************AI九宫格三子棋***********************************************/
/****************************能够实现玩家与计算机的对战*************************************/
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void Pos(int x, int y);              //获取光标位置
void gamestart();                    //游戏初始化
void welcometogame();                //游戏开始界面
void instructions();
char hunmanPriece();                  //判断玩家是否第一个下棋
char askYesNo();                      //询问判断玩家的输入
char opponent(char piece);			  //接受一个棋子作为参数(X/O)，返回对手的棋子
void displayBoard(const vector<char>& board);	  //刷新棋盘
char winner(const vector<char>& board);    //判断是否胜出
int humanMove(const vector<char>& board, char human);		 //返回玩家希望下棋的方格号码
int askNumber();					 //判断玩家输入的数字
bool isLegal(int move, const vector<char>& board);    //判断选取位置是否已被选取
int computerMove(vector<char> board, char computer);			 //返回电脑的输入
void announceWinner(char winner, char computer, char human);    //显示最终玩家
void start();	//游戏循环体

void main()
{
	gamestart();                     //游戏初始化
	start();
	char begin;
	do
	{	
		Pos(30, 19);
		cout << "玩家是继续还是结束(y/n)：";
		cin >> begin;
		if (begin == 'y')
		{
			system("cls");
			start();
			begin = EMPTY;
		}
		if (begin == 'n')
		{
			system("cls");
			Pos(30, 16);
			cout << "感谢你能来玩这个游戏，再见！！！";
			Pos(30, 17);
			system("pause");
			return;
		}
	} while (begin != 'y'&&begin != 'n');

}

//游戏循环体
void start()
{
	instructions();                  //显示游戏操作指南
	char human = hunmanPriece();                  //询问玩家是否第一个下棋
	char computer = opponent(human);

	const int NUM_SQUARES = 9;
	vector<char>board(NUM_SQUARES, EMPTY);
	displayBoard(board);                    //刷新棋盘
	int move;                               //选择移动的位置
	char turn = X;

	while (winner(board) == NO_ONE)
	{
		if (human == turn)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);                    //刷新棋盘
		turn = opponent(turn);
	}

	announceWinner(winner(board), computer, human);

}


//设置光标位置
void Pos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //返回标准的输入、输出或错误的设备的句柄。
	SetConsoleCursorPosition(hOutput, pos);     //定位光标位置的函数
}


//游戏初始化
void gamestart()
{
	system("mode con cols=100 lines=30");       //设置命令窗口大小 宽=100/2字节 高=30字节  左上角坐标（0，0）
	welcometogame();                           
}


//创建游戏开始界面
void welcometogame()
{
	Pos(36, 12);
	cout << "欢迎来到九宫格三子棋游戏！" << endl;
	Pos(40, 25);
	system("pause");
	system("cls");
}


//显示游戏操作指南
void instructions()        
{
	Pos(36, 5);
	cout << "欢迎来到九宫格三子棋！！！"<<endl;
	Pos(36, 6);
	printf("用数字0~8来控制选取下棋位置\n");
	Pos(40,8);
	cout << " 0 | 1 | 2 " << endl;
	Pos(40, 9);
	cout << "----------" << endl;
	Pos(40, 10);
	cout << " 3 | 4 | 5 " << endl;
	Pos(40, 11);
	cout << "----------" << endl;
	Pos(40, 12);
	cout << " 6 | 7 | 8 " << endl;
	
	
}

//询问玩家是否第一个下棋
char hunmanPriece()   
{
	char go_first=askYesNo();             //询问判断玩家的输入
	if (go_first == 'y')
	{
		Pos(36, 16);
		cout << "你选择了先手！！！";
		Pos(36, 20);
		cout << "玩家:X       计算机:O";
		return X;
	}
	else
	{
		Pos(36, 16);
		cout << "你选择了后手手！！！";
		Pos(36, 20);
		cout << "玩家:O       计算机:X";
		return O;
	}
}

char askYesNo()    //询问判断玩家的输入
{
	char response;
	do
	{
		Pos(36, 15);
		cout << "请问玩家是否选择先手？" << endl;
		Pos(36, 16);
		cout << "                        ";
		Pos(36, 16);
		cout << "输入（y/n）：";
		cin >> response;
	} while (response != 'y'&&response != 'n');
	return response;
}

//接受一个棋子作为参数(X/O)，返回对手的棋子
char opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}

}


//刷新棋盘
void displayBoard(const vector<char>& board)
{
	Pos(40, 8);
	cout <<" "<<board[0]<<" | "<<board[1] << " | " <<board[2] <<" "<< endl;
	Pos(40, 9);
	cout << "-----------" << endl;
	Pos(40, 10);
	cout << " " <<board[3] << " | " << board[4] << " | " << board[5] << " " << endl;
	Pos(40, 11);
	cout << "-----------" << endl;
	Pos(40, 12);
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " " << endl;
	
}


char winner(const vector<char>& board)
{
	//所有获胜的可能
	const int WINNING_ROWS[8][3] = { { 0,1,2 },
									 { 3,4,5 },
									 { 6,7,8 },
									 { 0,3,6 },
									 { 1,4,7 },
									 { 2,5,8 },
									 { 0,4,8 },
									 { 2,4,6 } };

	const int TOTAL_ROWS = 8;
	//判断赢家 并返回赢家的棋子
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}

	}
	//如果没有玩家获胜，则检查是否和棋
	if (count(board.begin(), board.end(), EMPTY) == 0)//STL中的count()算法,计数EMPTY出现的次数
	{
		return TIE;
	}
	//没有玩家胜出，且没有和棋
	return NO_ONE;
}

//返回玩家希望下棋的方格号码
int humanMove(const vector<char>& board, char human)
{
	
	int move=askNumber();
	while (!isLegal(move, board))  //当位置已被选取
	{
		Pos(36, 16);
		cout << "此位置已被选取，请重新选择位置！";
	    move = askNumber();
	}
	Pos(36, 16);
	cout << "等待计算机玩家.......                     ";
	return move;
}
//判断玩家输入的数字
int askNumber()
{
	int number;
	
	do
	{
		Pos(36, 15);
		cout << "                                      ";
		Pos(36, 15);
		cout << "请选择你要下棋的位置(0~8)：";
		cin >> number;
	} while (number > 8 || number < 0);
	return number;
}

//判断选取位置是否已被选取
inline bool isLegal(int move,const vector<char>& board)
{
	return (board[move] == EMPTY);  
}

//返回电脑的输入
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool fond = false;

	//如果计算机能一步获胜，则选择这个位置
	while (!fond&&move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			fond = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!fond)
			move++;
	}

	////如果不能一步获胜，就检查人类玩家是否在下一步获胜
	if (!fond)
	{
		move = 0;
		char human= opponent(computer);    //翻转棋子
		while (!fond&&move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				fond = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!fond)
				move++;
		}

	}

	//否则在剩下的方格中选取最优的一个方格，最优的在中心，次优的在四个角落，最次的是剩下的方格
	if (!fond)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		while (!fond&&i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				fond = true;
			}
			i++;
		}
	}
	Sleep(500);
	Pos(36, 17);
	cout << "计算机玩家选择下棋的位置(0~8)是："<<move;
	Pos(36, 16);
	cout << "等待人类玩家...                 ";
	return move;
}

//显示最终玩家
void announceWinner(char winner, char computer, char human)
{
	Pos(30, 15);
	cout << "                                                   ";
	Pos(30, 16);
	cout << "                                                   ";
	Pos(30, 17);
	cout << "                                                   ";

	if (winner == computer)
	{
		Pos(30, 18);
		cout << "恭喜计算机玩家已获胜，它的棋子是" << computer;
	}
	else if(winner==human)
	{
		Pos(30, 18);
		cout << "恭喜人类玩家已获胜，它的棋子是" << human;
	}
	else
	{
		Pos(30, 18);
		cout << "人类玩家与计算机玩家没有分出胜负" ;
	}
}