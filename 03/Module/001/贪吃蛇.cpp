// ̰���ߴ���ս.cpp : Defines the entry point for the console application.
//

/*******ͷ  ��  ��*******/
#include<stdafx.h>			//vc�Դ�ͷ�ļ�
#include<stdio.h>			//��׼�������������
#include<time.h>			//���ڻ�������
#include<windows.h>			//����dos����
#include<stdlib.h>			//��standard library��־��ͷ�ļ������涨����һЩ���ͨ�ù��ߺ���
#include<conio.h>			//���ռ����������

/*******��  ��  ��*******/
#define U 1
#define D 2
#define L 3 
#define R 4      //�ߵ�״̬��U���� ��D���£�L:�� R����

/*******��  ��  ȫ  ��  ��  �� *******/
typedef struct snake 		//�����һ���ڵ�
{
    int x;
    int y;
    struct snake *next;
}snake;
int score=0,add=10;			//�ܵ÷���ÿ�γ�ʳ��÷�
int HighScore = 0;			//��߷�
int status,sleeptime=200;	//��ǰ��״̬��ÿ�����е�ʱ����
snake *head, *food;			//��ͷָ�룬ʳ��ָ��
snake *q;					//�����ߵ�ʱ���õ���ָ��
int endgamestatus=0;		//��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��
HANDLE hOut;				//����̨���


/*******��  ��  ��  �� *******/
void gotoxy(int x,int y);   //���ù��λ��
int color(int c);           //����������ɫ
void printsnake();          //�ַ���---��
void welcometogame();       //��ʼ����
void createMap();           //���Ƶ�ͼ
void scoreandtips();		//��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
void initsnake();           //��ʼ������������
void createfood();          //�������������ʳ��
int biteself();             //�ж��Ƿ�ҧ�����Լ�
void cantcrosswall();       //������ײǽ�����
void speedup();				//����
void speeddown();			//����
void snakemove();           //������ǰ������
void keyboardControl();     //���Ƽ��̰���
void Lostdraw();            //��Ϸ��������
void endgame();             //��Ϸ����
void choose();				//��Ϸʧ��֮���ѡ��
void File_out();            //���ļ��ж�ȡ��߷�
void File_in();            	//������߷ֽ��ļ�
void explation();           //��Ϸ˵��

/**
 * ������ɫ����  
*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}

/**
 * ���ù��λ��
 */
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);  //��λ���λ��
}

/*
*   �ַ���
*/
void printsnake()
{
	gotoxy(35,1);
	color(6);
	printf("/^\\/^\\");                     //���۾�

	gotoxy(34,2);
	printf("|__|  O|");                    //���۾�

	gotoxy(33,2);
	color(2);
	printf("_");

	gotoxy(25,3);
	color(12);
	printf("\\/");      		//���ţ���ͷ��

	gotoxy(31,3);
	color(2);
	printf("/");

	gotoxy(37,3);
	color(6);
	printf(" \\_/");     		//���۾�

	gotoxy(41,3);
	color(10);
	printf(" \\");

	gotoxy(26,4);
	color(12);
	printf("\\____");   		//��ͷ

	gotoxy(32,4);
	printf("_________/");

	gotoxy(31,4);
	color(2);
	printf("|");

	gotoxy(43,4);
	color(10);
	printf("\\");

	gotoxy(32,5);
	color(2);
	printf("\\_______");                    //����

	gotoxy(44,5);
	color(10);
	printf("\\");

	gotoxy(39,6);
	printf("|     |                  \\");  //���涼�ǻ�����

	gotoxy(38,7);
	printf("/      /                   \\");

	gotoxy(37,8);
	printf("/      /                    \\ \\");

	gotoxy(35,9);
	printf("/      /                       \\ \\");

	gotoxy(34,10);
	printf("/     /                          \\  \\");

	gotoxy(33,11);
	printf("/     /             _----_         \\   \\");

	gotoxy(32,12);
	printf("/     /           _-~      ~-_         |  |");

	gotoxy(31,13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoxy(32,14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoxy(33,15);
	printf("~-_           _-~          ~-_       _-~");

	gotoxy(35,16);
	printf("~--______-~                ~-___-~");
}
/**
* ������
*/
int main()
{
	system("mode con cols=100 lines=30");    	//���ÿ���̨�Ŀ��  30��100��
	printf(":");
//	printsnake();									//�����ַ���
    return 0;
}












