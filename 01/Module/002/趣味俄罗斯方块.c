#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

/*******��  ��  ��*******/
#define FrameX 13   		//��Ϸ�������Ͻǵ�X������
#define FrameY 3   			//��Ϸ�������Ͻǵ�Y������
#define Frame_height  20 	//��Ϸ���ڵĸ߶�
#define Frame_width   18 	//��Ϸ���ڵĿ��

/*******��  ��  ȫ  ��  ��  �� *******/
int i,j,Temp,Temp1,Temp2; 	//temp,temp1,temp2���ڼ�ס��ת�����������ֵ
int a[80][80]={0};   		//�����Ϸ��Ļ��ͼ����2,1,0�ֱ��ʾ��λ��Ϊ��Ϸ�߿򡢷��顢��ͼ��;��ʼ��Ϊ��ͼ��
int b[4];     				//���4��"��"���飺1��ʾ�з��飬0��ʾ�޷���
struct Tetris		//��������˹����Ľṹ��
{
 	int x;     		//���ķ����x������
 	int y;     		//���ķ����y������
 	int flag;    	//��Ƿ������͵����
 	int next;    	//��һ������˹�������͵����
 	int speed;    	//����˹�����ƶ����ٶ�
 	int number;    	//��������˹����ĸ���
 	int score;    	//��Ϸ�ķ���
 	int level;    	//��Ϸ�ĵȼ�
};
HANDLE hOut;		//����̨���

/*******��  ��  ��  �� *******/
void gotoxy(int x, int y);			//����Ƶ�ָ��λ��
void DrwaGameframe();				//������Ϸ�߿�
void Flag(struct Tetris *);			//��������������͵����
void MakeTetris(struct Tetris *);	//��������˹����
void PrintTetris(struct Tetris *);	//��ӡ����˹����
void CleanTetris(struct Tetris *);	//�������˹����ĺۼ�
int  ifMove(struct Tetris *);		//�ж��Ƿ����ƶ�������ֵΪ1�����ƶ������򣬲����ƶ�
void Del_Fullline(struct Tetris *);	//�ж��Ƿ����У���ɾ�����еĶ���˹����
void Gameplay();					//��ʼ��Ϸ
void regulation();                  //��Ϸ����
void explation();                   //����˵��
void welcom();                      //��ӭ����
void Replay(struct Tetris *);  		//���¿�ʼ��Ϸ
void title();                       //��ӭ�����Ϸ��ı���
void flower();                      //��ӭ�����ϵ��ַ�װ�λ�
void close();                       //�ر���Ϸ
/**
 * ��ȡ��Ļ���λ��
 */
void gotoxy(int x, int y)
{
 	COORD pos;
 	pos.X = x;  //������
 	pos.Y = y;  //������
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
 * ������ɫ����      �˺����ľ����ԣ�1��ֻ��Windowsϵͳ��ʹ��   2�����ܸı䱳����ɫ
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}
/**
 * �������Ϸ��ı���
 */
void title()
{
	color(15);
	gotoxy(24,3);
    printf("Ȥ  ζ  ��  ��  ˹  ��  ��\n");
	color(11);
	gotoxy(18,5);
    printf("��");
    gotoxy(18,6);
    printf("����");
    gotoxy(18,7);
    printf("��");

    color(14);
	gotoxy(26,6);
    printf("����");
    gotoxy(28,7);
    printf("����");//

    color(10);
	gotoxy(36,6);
    printf("����");
    gotoxy(36,7);
    printf("����");

    color(13);
	gotoxy(45,5);
    printf("��");
    gotoxy(45,6);
	printf("��");
	gotoxy(45,7);
	printf("��");
	gotoxy(45,8);
	printf("��");

	color(12);
	gotoxy(56,6);
    printf("��");
    gotoxy(52,7);
	printf("������");
}

/**
 * ��  ��  ��
 */
int main()
{
	title();            //��ӭ�����ϵı���
	flower();
	welcom();
}

void flower()
{
	gotoxy(66,11);   	//ȷ����Ļ��Ҫ�����λ��
	color(12);			//������ɫ
	printf("(_)");  	//�컨�ϱ߻���

	gotoxy(64,12);
	printf("(_)");      //�컨��߻���

	gotoxy(68,12);
	printf("(_)");      //�컨�ұ߻���

	gotoxy(66,13);
	printf("(_)");      //�컨�±߻���

	gotoxy(67,12);      //�컨����
	color(6);
	printf("@");

	gotoxy(72,10);
	color(13);
	printf("(_)");      //�ۻ���߻���

	gotoxy(76,10);
	printf("(_)");      //�ۻ��ұ߻���

	gotoxy(74,9);
	printf("(_)");      //�ۻ��ϱ߻���

	gotoxy(74,11);
	printf("(_)");      //�ۻ��±߻���

	gotoxy(75,10);
	color(6);
	printf("@");        //�ۻ�����

	gotoxy(71,12);
	printf("|");      	//���仨֮�������

	gotoxy(72,11);
	printf("/");      	//���仨֮�������

	gotoxy(70,13);
	printf("\\|");       //ע�⡢\Ϊת���ַ�����Ҫ����\��������ǰ����Ҫת��

	gotoxy(70,14);
	printf("`|/");

	gotoxy(70,15);
	printf("\\|");

	gotoxy(71,16);
	printf("| /");

	gotoxy(71,17);
	printf("|");

	gotoxy(67,17);
	color(10);
	printf("\\\\\\\\");      //�ݵ�

	gotoxy(73,17);
	printf("//");

	gotoxy(67,18);
	color(2);
	printf("^^^^^^^^");

	gotoxy(65,19);
	color(5);
	printf("�� ��  �� ��");

	gotoxy(68,20);
	printf("��С��");
}

/**
 * ��ӭ����
 */
void welcom()
{
	int n;
	int i,j = 1;
	color(14);          			//��ɫ�߿�
	for (i = 9; i <= 20; i++)   	//������±߿�===
	{
		for (j = 15; j <= 60; j++)  //������ұ߿�||
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
	color(12);
	gotoxy(25, 12);
	printf("1.��ʼ��Ϸ");
	gotoxy(40, 12);
	printf("2.����˵��");
	gotoxy(25, 17);
	printf("3.��Ϸ����");
	gotoxy(40, 17);
	printf("4.�˳�");
	gotoxy(21,22);
	color(3);
	printf("��ѡ��[1 2 3 4]:[ ]\b\b");
	color(14);
    scanf("%d", &n);    //����ѡ��
    switch (n)
    {
    	case 1:
    		system("cls");
        	break;
    	case 2:
        	break;
    	case 3:
        	break;
    	case 4:
        	break;
    }
}













