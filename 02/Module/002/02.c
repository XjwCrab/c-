#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*******�� �� ͷ �� ��*******/
#include <stdio.h>		//��׼������������⣨printf��scanf��
#include <conio.h>  	//Ϊ�˶�ȡ�����
#include <windows.h>	//����dos���棨��ȡ����̨������λ�á�����������ɫ��
#include <math.h>   	//pow����

/*******��  ��  ȫ  ��  ��  ��*******/
int step=0;				//��ִ�в���
int score=0;				//�洢��Ϸ����
long int Time;				//��Ϸ����ʱ��
int BOX[4][4]={0,0,0,0, 	//��Ϸ�е�16������
               0,0,0,0,
               0,0,0,0,
               0,0,0,0};
HANDLE hOut;				//����̨���

/*******��  ��  ��  ��*******/
void gotoxy(int x, int y); 		//��ȡ��Ļ���λ��
int color(int c);               	//����������ɫ
int	TextColors(int i);				//���������޸���ɫ
void drawTheGameBox(); 			//������Ϸ����
int *add(int item[]);   			//�ϲ�����
int ifMove(int item[]); 			//�ж��Ƿ��ܹ��ƶ�����,����1�ܶ���0���ܶ�
void Gameplay();    				//��ʼ��Ϸ
void Replay();			       		//������Ϸ
int if2n(int x);         			//�ж�x�Ƿ���2��n�η�
//�ж��Ƿ��ܹ����ƣ��������ƣ������е������������2��n�η������򷵻�1�������ƶ����򷵻�0
int ifup();
//�ж��Ƿ��ܹ����ƣ��������ƣ������е������������2��n�η������򷵻�1�������ƶ����򷵻�0
int ifdown();
//�ж��Ƿ��ܹ����ƣ��������ƣ������е������������2��n�η������򷵻�1�������ƶ����򷵻�0
int ifleft();
//�ж��Ƿ��ܹ����ƣ��������ƣ������е������������2��n�η������򷵻�1�������ƶ����򷵻�0
int ifright();
int BOXmax();						//�������������
int Gamefaile();					//�ж��Ƿ�ʧ��
int Gamewin();						//�ж��Ƿ�ʤ��
int keyboardControl(int key);   	//���̿����ƶ�
void close();                   	//�ر���Ϸ
void title();                   	//���Ʊ��⣨2048�ַ�����
void choice();                  	//ѡ���
void Rabbit();						//�����ַ���
void regulation();              	//��Ϸ�������
void explation();               	//����˵��

/**
 * ��ȡ��Ļ���λ��
 */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //��λ���λ��
}

/**
 * ������ɫ����
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}

/**
 * ���ñ���
 */
void title()
{
	color(11);          						//ǳ����ɫ
    gotoxy(19,2);
    printf("������   ��������   ��  ��     ��������"); 	//���2048�ַ���
    gotoxy(19,3);
    printf("    ��   ��    ��   ��  ��     ��    ��");
    gotoxy(19,4);
    printf("������   ��    ��   ��  ��     ��������");
    gotoxy(19,5);
    printf("��       ��    ��   ��������   ��    ��");
    gotoxy(19,6);
    printf("������   ��������       ��     ��������");
}

/**
 * �˵�ѡ��
 */
void choice()
{
	int n;
    int i,j = 1;
    gotoxy(32,8) ;
    color(13);
    printf("�� ս 2 0 4 8");
	color(14);          					//��ɫ�߿�
    for (i = 9; i <= 20; i++)   			//������±߿�===
	{
		for (j = 15; j <= 60; j++)  	//������ұ߿�||
		{
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}

	color(12);                              //��ɫ����
	gotoxy(25, 12);                        //������ʾλ��
	printf("1.��ʼ��Ϸ");
	gotoxy(40, 12);
	printf("2.��Ϸ����");
	gotoxy(25, 16);
	printf("3.����˵��");
	gotoxy(40, 16);
	printf("4.�˳�");
	gotoxy(21,22);
	color(5);                             //����ɫ����
	printf("��ѡ��[1 2 3 4]:[ ]\b\b");
    scanf("%d", &n);    					 //����ѡ��
    switch (n)                            //��֧ѡ��
    {
    	case 1:                          //��������"1"
        	break;
    	case 2:                          //��������"2"
        	break;
    	case 3:                          //��������"3"
        	break;
    	case 4:                          //��������"4"
       	 	exit(0);    					//�˳���Ϸ
        	break;
    }
}

/**
 * ����С����
 */
void Rabbit()
{
	color(3);
	gotoxy(64,10);
	printf("��-��  ��-��");		//��ӡ���Ӷ���
	gotoxy(64,11);
	printf("�� ��  �� ��");
	gotoxy(64,12);
	printf("�� ��  �� ��");
	gotoxy(63,13);
	printf("_��");					//��ӡ������
	gotoxy(74,13);
	printf("��_");
	gotoxy(62,14);
	printf("��");
	gotoxy(76,14);
	printf("��");
	gotoxy(62,15);
	printf("��            ��");
	gotoxy(62,16);
	printf("��");
	gotoxy(76,16);
	printf("��");
	gotoxy(62,17);
	printf("��            ��");	//��ӡ������
	gotoxy(62,18);
	printf("�����ש����ש���");	//��ӡ�°�
	gotoxy(64,19);
	printf("����    �ǩ�");		//��ӡ�첲
	gotoxy(62,20);
	printf("-�ީߩ��ߩߩ�-");
	color(5);
	gotoxy(67,13);
	printf("`~�]~`");				//��ӡ����
	color(4);
	gotoxy(67,14);
	printf("��   ��");				//��ӡ�۾�
	color(13);
	gotoxy(65,15);
	printf("��");					//��ӡ����
	gotoxy(74,15);
	printf("��");
	color(12);
	gotoxy(69,17);
	printf("��");					//��ӡ���
}
/**
 * ���������������
 */
int main() {

    title();            //��ӡ����
    Rabbit();           //��ӡ�ַ���
    choice();           //�˵�ѡ��
}




























