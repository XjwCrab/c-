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
        	DrwaGameframe();       	//������Ϸ����
        	break;
    	case 2:
        	break;
    	case 3:
        	break;
    	case 4:
        	break;
    }
}

/**
 * ������Ϸ����
 */
void DrwaGameframe()
{
 	gotoxy(FrameX+Frame_width-7,FrameY-2);   	//������Ϸ���Ƶ���ʾλ��
	color(11);                                     //��������ɫ����Ϊ����ɫ
	printf("Ȥζ����˹����");                      //��ӡ��Ϸ����
 	gotoxy(FrameX+2*Frame_width+3,FrameY+7);    //�����ϱ߿����ʾλ��
 	color(2);                                      //��������ɫ����Ϊ����ɫ
	printf("**********");							//��ӡ��һ�����ַ�����ϱ߿�
	gotoxy(FrameX+2*Frame_width+13,FrameY+7);
 	color(3);                                      //��������ɫ����Ϊ������ɫ
	printf("��һ���ַ��飺");
 	gotoxy(FrameX+2*Frame_width+3,FrameY+13);
 	color(2);
	printf("**********");							//��ӡ��һ�����ַ�����±߿�
	gotoxy(FrameX+2*Frame_width+3,FrameY+17);
	color(14);                                    //��������ɫ����Ϊ��ɫ
	printf("��������ת");
	gotoxy(FrameX+2*Frame_width+3,FrameY+19);
	printf("�ո���ͣ��Ϸ");
 	gotoxy(FrameX+2*Frame_width+3,FrameY+15);
 	printf("Esc���˳���Ϸ");
 	gotoxy(FrameX,FrameY);
	color(12);                                     //��������ɫ����Ϊ��ɫ
	printf("�X");									//��ӡ���
 	gotoxy(FrameX+2*Frame_width-2,FrameY);
 	printf("�[");
 	gotoxy(FrameX,FrameY+Frame_height);
 	printf("�^");
 	gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
 	printf("�a");
	for(i=2;i<2*Frame_width-2;i+=2)
 	{
  		gotoxy(FrameX+i,FrameY);
  		printf("�T");         						//��ӡ�Ϻ��
 	}
 	for(i=2;i<2*Frame_width-2;i+=2)
 	{
  		gotoxy(FrameX+i,FrameY+Frame_height);
  		printf("�T");         						//��ӡ�º��
  		a[FrameX+i][FrameY+Frame_height]=2;    	//����º��Ϊ��Ϸ�߿򣬷�ֹ�������
 	}
 	for(i=1;i<Frame_height;i++)
	{
  		gotoxy(FrameX,FrameY+i);
  		printf("�U");        	 					//��ӡ������
  		a[FrameX][FrameY+i]=2;       			//���������Ϊ��Ϸ�߿򣬷�ֹ�������
 	}
 	for(i=1;i<Frame_height;i++)
 	{
  		gotoxy(FrameX+2*Frame_width-2,FrameY+i);
  		printf("�U");         						 //��ӡ������
  		a[FrameX+2*Frame_width-2][FrameY+i]=2;   //���������Ϊ��Ϸ�߿򣬷�ֹ�������
    }
}

/**
 * ��������˹����
 */
void MakeTetris(struct Tetris *tetris)
{
 	a[tetris->x][tetris->y]=b[0];    //���ķ���λ�õ�ͼ��״̬
 	switch(tetris->flag)      //��7���࣬19������
 	{
  		case 1:         /*���ַ��� ����
		  			               ����  */
   		{
			color(10);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x+2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
   			break;
   		}
  		case 2:         /*ֱ�߷��� ��������*/
   		{
		   	color(13);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x+4][tetris->y]=b[3];
    		break;
   		}
  		case 3:         /*ֱ�߷��� ��
		  			               ��
								   ��
								   ��  */
   		{
		   	color(13);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y-2]=b[2];
    		a[tetris->x][tetris->y+1]=b[3];
    		break;
   		}
  		case 4:         /*T�ַ��� ������
		  			                ��  */
   		{
		   	color(11);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y]=b[2];
    		a[tetris->x][tetris->y+1]=b[3];
    		break;
   		}
  		case 5:         /* ˳ʱ��90��T�ַ���   ��
		  			                         ����
									           ��*/
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-2][tetris->y]=b[3];
    		break;
   		}
  		case 6:         /* ˳ʱ��180��T�ַ���     ��
		  			                            ������*/
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 7:         /* ˳ʱ��270��T�ַ���   ��
		  			                            ����
									            ��  */
   		{
		   	color(11);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 8:         /* Z�ַ���   ����
		  			                   ����*/
   		{
		   	color(14);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y+1]=b[3];
    		break;
   		}
  		case 9:         /* ˳ʱ��Z�ַ���      ��
		  			                        ����
									        ��  */
   		{
		   	color(14);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-2][tetris->y]=b[2];
    		a[tetris->x-2][tetris->y+1]=b[3];
    		break;
   		}
  		case 10:        /* ��תZ�ַ���      ����
		  			                      ����  */
   		{
		   	color(14);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 11:        /* ˳ʱ��Z�ַ���    ��
		  			                        ����
									          ��  */
   		{
		   	color(14);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-2][tetris->y-1]=b[2];
    		a[tetris->x-2][tetris->y]=b[3];
    		break;
   		}
  		case 12:        /* 7�ַ���    ����
		  			                    ��
									    ��  */
   		{
		   	color(12);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-2][tetris->y-1]=b[3];
    		break;
   		}
  		case 13:        /* ˳ʱ��90��7�ַ���        ��
		  			                            ������*/
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 14:        /* ˳ʱ��180��7�ַ���      ��
		  			                               ��
									               ����  */
   		{
		   	color(12);
    		a[tetris->x][tetris->y-1]=b[1];
   		 	a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y+1]=b[3];
    		break;
   		}
  		case 15:        /* ˳ʱ��270��7�ַ���    ������
		  			                             ��    */
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x-2][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 16:        /* ��ת7�ַ���    ����
		  			                      ��
										  ��    */
   		{
		   	color(12);
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y-1]=b[3];
    		break;
   		}
  		case 17:        /* ˳ʱ��ת90��7�ַ���    ������
		  			                                  ��*/
   		{
		   	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x+2][tetris->y+1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 18:        /* ˳ʱ��ת180��7�ַ���    ��
		  			                               ��
									             ����    */
   		{
		   	color(12);
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-2][tetris->y+1]=b[3];
    		break;
   		}
  		case 19:        /* ˳ָ��ת270��7�ַ���    ��
		  			                               ������*/
  		{
		  	color(12);
    		a[tetris->x-2][tetris->y]=b[1];
    		a[tetris->x-2][tetris->y-1]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
  	 	}
 	}
}
/**
 * ��ӡ����˹����
 */
void PrintTetris(struct Tetris *tetris)
{
 	for(i=0;i<4;i++)					//����b[4]����4��Ԫ�أ�ѭ����4��Ԫ�أ���ÿ��Ԫ�ص�ֵ��Ϊ
 	{
  		b[i]=1;         				//����b[4]��ÿ��Ԫ�ص�ֵ��Ϊ1
 	}
 	MakeTetris(tetris);      			//������Ϸ����
 	for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 	{
  		for(j=tetris->y-2;j<=tetris->y+1;j++)	//ѭ���������п��ܳ��ֵ�λ��
  		{
   			if( a[i][j]==1 && j>FrameY ) 		//������λ�����з���
   			{
    			gotoxy(i,j);
				printf("��");     					//��ӡ�߿��ڵķ���
   			}
  		}
	}
 	//��ӡ�˵���Ϣ
	gotoxy(FrameX+2*Frame_width+3,FrameY+1); 	//���ô�ӡλ��
	color(4);
 	printf("level : ");
 	color(12);
 	printf(" %d",tetris->level); 					//����ȼ�
	gotoxy(FrameX+2*Frame_width+3,FrameY+3);
	color(4);
 	printf("score : ");
 	color(12);
 	printf(" %d",tetris->score); 					//�������
	gotoxy(FrameX+2*Frame_width+3,FrameY+5);
	color(4);
 	printf("speed : ");
 	color(12);
	printf(" %dms",tetris->speed); 			//����ٶ�
}











