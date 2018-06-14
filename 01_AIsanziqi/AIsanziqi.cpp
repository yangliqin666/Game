

/****************************AI�Ź���������***********************************************/
/****************************�ܹ�ʵ������������Ķ�ս*************************************/
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

void Pos(int x, int y);              //��ȡ���λ��
void gamestart();                    //��Ϸ��ʼ��
void welcometogame();                //��Ϸ��ʼ����
void instructions();
char hunmanPriece();                  //�ж�����Ƿ��һ������
char askYesNo();                      //ѯ���ж���ҵ�����
char opponent(char piece);			  //����һ��������Ϊ����(X/O)�����ض��ֵ�����
void displayBoard(const vector<char>& board);	  //ˢ������
char winner(const vector<char>& board);    //�ж��Ƿ�ʤ��
int humanMove(const vector<char>& board, char human);		 //�������ϣ������ķ������
int askNumber();					 //�ж�������������
bool isLegal(int move, const vector<char>& board);    //�ж�ѡȡλ���Ƿ��ѱ�ѡȡ
int computerMove(vector<char> board, char computer);			 //���ص��Ե�����
void announceWinner(char winner, char computer, char human);    //��ʾ�������
void start();	//��Ϸѭ����

void main()
{
	gamestart();                     //��Ϸ��ʼ��
	start();
	char begin;
	do
	{	
		Pos(30, 19);
		cout << "����Ǽ������ǽ���(y/n)��";
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
			cout << "��л�������������Ϸ���ټ�������";
			Pos(30, 17);
			system("pause");
			return;
		}
	} while (begin != 'y'&&begin != 'n');

}

//��Ϸѭ����
void start()
{
	instructions();                  //��ʾ��Ϸ����ָ��
	char human = hunmanPriece();                  //ѯ������Ƿ��һ������
	char computer = opponent(human);

	const int NUM_SQUARES = 9;
	vector<char>board(NUM_SQUARES, EMPTY);
	displayBoard(board);                    //ˢ������
	int move;                               //ѡ���ƶ���λ��
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
		displayBoard(board);                    //ˢ������
		turn = opponent(turn);
	}

	announceWinner(winner(board), computer, human);

}


//���ù��λ��
void Pos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //���ر�׼�����롢����������豸�ľ����
	SetConsoleCursorPosition(hOutput, pos);     //��λ���λ�õĺ���
}


//��Ϸ��ʼ��
void gamestart()
{
	system("mode con cols=100 lines=30");       //��������ڴ�С ��=100/2�ֽ� ��=30�ֽ�  ���Ͻ����꣨0��0��
	welcometogame();                           
}


//������Ϸ��ʼ����
void welcometogame()
{
	Pos(36, 12);
	cout << "��ӭ�����Ź�����������Ϸ��" << endl;
	Pos(40, 25);
	system("pause");
	system("cls");
}


//��ʾ��Ϸ����ָ��
void instructions()        
{
	Pos(36, 5);
	cout << "��ӭ�����Ź��������壡����"<<endl;
	Pos(36, 6);
	printf("������0~8������ѡȡ����λ��\n");
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

//ѯ������Ƿ��һ������
char hunmanPriece()   
{
	char go_first=askYesNo();             //ѯ���ж���ҵ�����
	if (go_first == 'y')
	{
		Pos(36, 16);
		cout << "��ѡ�������֣�����";
		Pos(36, 20);
		cout << "���:X       �����:O";
		return X;
	}
	else
	{
		Pos(36, 16);
		cout << "��ѡ���˺����֣�����";
		Pos(36, 20);
		cout << "���:O       �����:X";
		return O;
	}
}

char askYesNo()    //ѯ���ж���ҵ�����
{
	char response;
	do
	{
		Pos(36, 15);
		cout << "��������Ƿ�ѡ�����֣�" << endl;
		Pos(36, 16);
		cout << "                        ";
		Pos(36, 16);
		cout << "���루y/n����";
		cin >> response;
	} while (response != 'y'&&response != 'n');
	return response;
}

//����һ��������Ϊ����(X/O)�����ض��ֵ�����
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


//ˢ������
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
	//���л�ʤ�Ŀ���
	const int WINNING_ROWS[8][3] = { { 0,1,2 },
									 { 3,4,5 },
									 { 6,7,8 },
									 { 0,3,6 },
									 { 1,4,7 },
									 { 2,5,8 },
									 { 0,4,8 },
									 { 2,4,6 } };

	const int TOTAL_ROWS = 8;
	//�ж�Ӯ�� ������Ӯ�ҵ�����
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}

	}
	//���û����һ�ʤ�������Ƿ����
	if (count(board.begin(), board.end(), EMPTY) == 0)//STL�е�count()�㷨,����EMPTY���ֵĴ���
	{
		return TIE;
	}
	//û�����ʤ������û�к���
	return NO_ONE;
}

//�������ϣ������ķ������
int humanMove(const vector<char>& board, char human)
{
	
	int move=askNumber();
	while (!isLegal(move, board))  //��λ���ѱ�ѡȡ
	{
		Pos(36, 16);
		cout << "��λ���ѱ�ѡȡ��������ѡ��λ�ã�";
	    move = askNumber();
	}
	Pos(36, 16);
	cout << "�ȴ���������.......                     ";
	return move;
}
//�ж�������������
int askNumber()
{
	int number;
	
	do
	{
		Pos(36, 15);
		cout << "                                      ";
		Pos(36, 15);
		cout << "��ѡ����Ҫ�����λ��(0~8)��";
		cin >> number;
	} while (number > 8 || number < 0);
	return number;
}

//�ж�ѡȡλ���Ƿ��ѱ�ѡȡ
inline bool isLegal(int move,const vector<char>& board)
{
	return (board[move] == EMPTY);  
}

//���ص��Ե�����
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool fond = false;

	//����������һ����ʤ����ѡ�����λ��
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

	////�������һ����ʤ���ͼ����������Ƿ�����һ����ʤ
	if (!fond)
	{
		move = 0;
		char human= opponent(computer);    //��ת����
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

	//������ʣ�µķ�����ѡȡ���ŵ�һ���������ŵ������ģ����ŵ����ĸ����䣬��ε���ʣ�µķ���
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
	cout << "��������ѡ�������λ��(0~8)�ǣ�"<<move;
	Pos(36, 16);
	cout << "�ȴ��������...                 ";
	return move;
}

//��ʾ�������
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
		cout << "��ϲ���������ѻ�ʤ������������" << computer;
	}
	else if(winner==human)
	{
		Pos(30, 18);
		cout << "��ϲ��������ѻ�ʤ������������" << human;
	}
	else
	{
		Pos(30, 18);
		cout << "����������������û�зֳ�ʤ��" ;
	}
}