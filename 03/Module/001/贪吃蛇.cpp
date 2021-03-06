// 贪吃蛇大挑战.cpp : Defines the entry point for the console application.
//

/*******头  文  件*******/
#include<stdafx.h>			//vc自带头文件
#include<stdio.h>			//标准输入输出函数库
#include<time.h>			//用于获得随机数
#include<windows.h>			//控制dos界面
#include<stdlib.h>			//即standard library标志库头文件，里面定义了一些宏和通用工具函数
#include<conio.h>			//接收键盘输入输出

/*******宏  定  义*******/
#define U 1
#define D 2
#define L 3 
#define R 4      //蛇的状态，U：上 ；D：下；L:左 R：右

/*******定  义  全  局  变  量 *******/
typedef struct snake 		//蛇身的一个节点
{
    int x;
    int y;
    struct snake *next;
}snake;
int score=0,add=10;			//总得分与每次吃食物得分
int HighScore = 0;			//最高分
int status,sleeptime=200;	//蛇前进状态，每次运行的时间间隔
snake *head, *food;			//蛇头指针，食物指针
snake *q;					//遍历蛇的时候用到的指针
int endgamestatus=0;		//游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
HANDLE hOut;				//控制台句柄


/*******函  数  声  明 *******/
void gotoxy(int x,int y);   //设置光标位置
int color(int c);           //更改文字颜色
void printsnake();          //字符画---蛇
void welcometogame();       //开始界面
void createMap();           //绘制地图
void scoreandtips();		//游戏界面右侧的得分和小提示
void initsnake();           //初始化蛇身，画蛇身
void createfood();          //创建并随机出现食物
int biteself();             //判断是否咬到了自己
void cantcrosswall();       //设置蛇撞墙的情况
void speedup();				//加速
void speeddown();			//减速
void snakemove();           //控制蛇前进方向
void keyboardControl();     //控制键盘按键
void Lostdraw();            //游戏结束界面
void endgame();             //游戏结束
void choose();				//游戏失败之后的选择
void File_out();            //在文件中读取最高分
void File_in();            	//储存最高分进文件
void explation();           //游戏说明

/**
 * 文字颜色函数  
*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

/**
 * 设置光标位置
 */
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);  //定位光标位置
}

/*
*   字符蛇
*/
void printsnake()
{
	gotoxy(35,1);
	color(6);
	printf("/^\\/^\\");                     //蛇眼睛

	gotoxy(34,2);
	printf("|__|  O|");                    //蛇眼睛

	gotoxy(33,2);
	color(2);
	printf("_");

	gotoxy(25,3);
	color(12);
	printf("\\/");      		//蛇信（舌头）

	gotoxy(31,3);
	color(2);
	printf("/");

	gotoxy(37,3);
	color(6);
	printf(" \\_/");     		//蛇眼睛

	gotoxy(41,3);
	color(10);
	printf(" \\");

	gotoxy(26,4);
	color(12);
	printf("\\____");   		//舌头

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
	printf("\\_______");                    //蛇嘴

	gotoxy(44,5);
	color(10);
	printf("\\");

	gotoxy(39,6);
	printf("|     |                  \\");  //下面都是画蛇身

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
* 主函数
*/
int main()
{
	system("mode con cols=100 lines=30");    	//设置控制台的宽高  30行100列
	printf(":");
//	printsnake();									//绘制字符蛇
    return 0;
}












