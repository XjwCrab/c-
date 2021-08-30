#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*******定 义 头 文 件*******/
#include <stdio.h>		//标准输入输出函数库（printf、scanf）
#include <conio.h>  	//为了读取方向键
#include <windows.h>	//控制dos界面（获取控制台上坐标位置、设置字体颜色）
#include <math.h>   	//pow函数

/*******定  义  全  局  变  量*******/
int step=0;				//已执行步数
int score=0;				//存储游戏分数
long int Time;				//游戏运行时间
int BOX[4][4]={0,0,0,0, 	//游戏中的16个格子
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
HANDLE hOut;				//控制台句柄

/*******函  数  声  明*******/
void gotoxy(int x, int y); 		//获取屏幕光标位置
int color(int c);               	//设置文字颜色
int	TextColors(int i);				//根据数字修改颜色
void drawTheGameBox(); 			//绘制游戏界面
int *add(int item[]);   			//合并数字
int ifMove(int item[]); 			//判断是否能够移动数字,返回1能动，0不能动
void Gameplay();    				//开始游戏
void Replay();			       		//重新游戏
int if2n(int x);         			//判断x是否是2的n次方
//判断是否能够上移，可以上移（格子中的两个数相加是2的n次方），则返回1；不能移动，则返回0
int ifup();
//判断是否能够下移，可以下移（格子中的两个数相加是2的n次方），则返回1；不能移动，则返回0
int ifdown();
//判断是否能够左移，可以左移（格子中的两个数相加是2的n次方），则返回1；不能移动，则返回0
int ifleft();
//判断是否能够右移，可以右移（格子中的两个数相加是2的n次方），则返回1；不能移动，则返回0
int ifright();
int BOXmax();						//返回棋盘最大数
int Gamefaile();					//判断是否失败
int Gamewin();						//判断是否胜利
int keyboardControl(int key);   	//键盘控制移动
void close();                   	//关闭游戏
void title();                   	//绘制标题（2048字符画）
void choice();                  	//选择框
void Rabbit();						//绘制字符画
void regulation();              	//游戏规则介绍
void explation();               	//按键说明

































