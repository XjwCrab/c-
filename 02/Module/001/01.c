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

































