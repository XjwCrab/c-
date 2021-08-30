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

/**
 * 获取屏幕光标位置
 */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //定位光标位置
}

/**
 * 文字颜色函数
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

/**
 * 设置标题
 */
void title()
{
	color(11);          						//浅淡绿色
    gotoxy(19,2);
    printf("■■■   ■■■■   ■  ■     ■■■■"); 	//输出2048字符画
    gotoxy(19,3);
    printf("    ■   ■    ■   ■  ■     ■    ■");
    gotoxy(19,4);
    printf("■■■   ■    ■   ■  ■     ■■■■");
    gotoxy(19,5);
    printf("■       ■    ■   ■■■■   ■    ■");
    gotoxy(19,6);
    printf("■■■   ■■■■       ■     ■■■■");
}

/**
 * 菜单选项
 */
void choice()
{
	int n;
    int i,j = 1;
    gotoxy(32,8) ;
    color(13);
    printf("挑 战 2 0 4 8");
	color(14);          					//黄色边框
    for (i = 9; i <= 20; i++)   			//输出上下边框===
	{
		for (j = 15; j <= 60; j++)  	//输出左右边框||
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}

	color(12);                              //红色字体
	gotoxy(25, 12);                        //设置显示位置
	printf("1.开始游戏");
	gotoxy(40, 12);
	printf("2.游戏规则");
	gotoxy(25, 16);
	printf("3.按键说明");
	gotoxy(40, 16);
	printf("4.退出");
	gotoxy(21,22);
	color(5);                             //深紫色字体
	printf("请选择[1 2 3 4]:[ ]\b\b");
    scanf("%d", &n);    					 //输入选项
    switch (n)                            //分支选择
    {
    	case 1:                          //输入数字"1"
        	break;
    	case 2:                          //输入数字"2"
        	break;
    	case 3:                          //输入数字"3"
        	break;
    	case 4:                          //输入数字"4"
       	 	exit(0);    					//退出游戏
        	break;
    }
}

/**
 * 绘制小兔子
 */
void Rabbit()
{
	color(3);
	gotoxy(64,10);
	printf("┏-┓  ┏-┓");		//打印兔子耳朵
	gotoxy(64,11);
	printf("┃ ┃  ┃ ┃");
	gotoxy(64,12);
	printf("┃ ┃  ┃ ┃");
	gotoxy(63,13);
	printf("_┃");					//打印兔子脸
	gotoxy(74,13);
	printf("┃_");
	gotoxy(62,14);
	printf("┃");
	gotoxy(76,14);
	printf("┃");
	gotoxy(62,15);
	printf("┃            ┃");
	gotoxy(62,16);
	printf("┃");
	gotoxy(76,16);
	printf("┃");
	gotoxy(62,17);
	printf("┃            ┃");	//打印兔子脸
	gotoxy(62,18);
	printf("┗━┳━━┳━┛");	//打印下巴
	gotoxy(64,19);
	printf("┏┫    ┣┓");		//打印胳膊
	gotoxy(62,20);
	printf("-┺┻━┻┻┹-");
	color(5);
	gotoxy(67,13);
	printf("`~⺌~`");				//打印刘海
	color(4);
	gotoxy(67,14);
	printf("○   ○");				//打印眼睛
	color(13);
	gotoxy(65,15);
	printf("〃");					//打印腮红
	gotoxy(74,15);
	printf("〃");
	color(12);
	gotoxy(69,17);
	printf("┻");					//打印嘴巴
}
/**
 * 主函数，程序入口
 */
int main() {

    title();            //打印标题
    Rabbit();           //打印字符画
    choice();           //菜单选项
}

/**
 * 绘制游戏界面4×4的网格
 */
void drawTheGameBox()
{
	int i,j,k;
	color(14);       			//黄色
	for(j = 2;j <= 22;j += 5)                                  //打印棋盘边框
	{
		gotoxy(15,j);
		for(k = 1;k<42;k++)
		{
			printf("-");	//打印棋盘的横向边框
		}
		printf("\n");
	}
	for (i = 3;i < 7;i ++)
	{
		gotoxy(15,i);		//9个空格
		printf("|         |         |         |         | ");	 //打印棋盘的纵向边框
	}
	for (i = 8;i<12;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	for (i = 13;i<17;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");	 //打印棋盘的纵向边框
	}
	for (i = 8;i<12;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	for (i = 13;i<17;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	for (i = 18;i<22;i++)
	{
		gotoxy(15,i);
		printf("|         |         |         |         | ");
	}
	gotoxy(16,1);   								//屏幕坐标位置
	color(11);      								//淡浅绿色
	printf("游戏分数: %ld",score);

	color(13);      								//粉色
	gotoxy(42,1);   								//屏幕坐标位置
	printf("执行步数: %d\n",step);

    gotoxy(44,23);
	color(10);                                  	//绿色
	printf("已用时：%d s",time(NULL) - Time);   //输出游戏运行时间

}



























