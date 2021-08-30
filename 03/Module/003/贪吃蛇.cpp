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
	printsnake();									//�����ַ���
	welcometogame();
	File_out();
    return 0;
}
/**
 * ��ӭ����
 */
void welcometogame()
{
	int n;
	int i,j = 1;
	gotoxy(43,18);
	color(11);
	printf("̰ �� �� �� �� ս");
	color(14);          					 //��ɫ�߿�
	for (i = 20; i <= 26; i++)   			 //������±߿�
	{
		for (j = 27; j <= 74; j++)   	 //������ұ߿�
		{
			gotoxy(j, i);
			if (i == 20 || i == 26)
			{
				printf("-");
            }
			else if (j == 27 || j == 74)
            {
				printf("|");
            }
		}
	}
	color(12);                              //��ɫ
	gotoxy(35, 22);                        //����������ʾλ��
	printf("1.��ʼ��Ϸ");
	gotoxy(55, 22);
	printf("2.��Ϸ˵��");
	gotoxy(35, 24);
	printf("3.�˳���Ϸ");
	gotoxy(29,27);
	color(3);                                //������ɫ
	printf("��ѡ��[1 2 3]:[ ]\b\b");        //\bΪ�˸�ʹ�ù�괦��[]�м�
	color(14);                                //��ɫ
    scanf("%d", &n);    						//����ѡ��
    switch (n)									//����ѡ��
    {
    	case 1:									//ѡ��һ����û�����ѡ�����ݣ�֮�����
    		system("cls");						//����
			createMap();
			initsnake(); 
			createfood();
        	break;
    	case 2: 								//ѡ�������û�����ѡ�����ݣ�֮�����
        	break;
    	case 3: 								//ѡ��������û�����ѡ�����ݣ�֮�����
            exit(0);							//�˳�����
        	break;
    }
}

/**
 * ������ͼ
 */
void createMap()
{
    int i,j;
    for(i=0;i<58;i+=2)			//��ӡ���±߿�
    {
        gotoxy(i,0);
		color(5);			//����ɫ�ı߿�
        printf("��");
        gotoxy(i,26);
        printf("��");
    }
    for(i=1;i<26;i++)			//��ӡ���ұ߿�
    {
        gotoxy(0,i);
        printf("��");
        gotoxy(56,i);
        printf("��");
    }
	for(i=2;i<56;i+=2)			//��ӡ�м�����
	{
		for(j=1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("��\n\n");
		}
	}
}

/**
 *  ��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
 */
void scoreandtips()
{
	File_out();									//����File_out()����ȡ�ļ�save.txt�е�����
	gotoxy(64,4);									//ȷ����ӡ�����λ��
	color(11);										//������ɫ
	printf("����߼�¼�%d",HighScore);		//��ӡ��Ϸ��߷�
	gotoxy(64,8);
	color(14);
	printf("�÷֣�%d  ",score);
	color(13);
	gotoxy(73,11);
	printf("С �� ʾ");
	gotoxy(60,13);
	color(6);
	printf("�p ������������������������������ �p");	//��ӡ�߿�
	gotoxy(60,25);
	printf("�p ������������������������������ �p");
	color(3);
	gotoxy(64,14);
	printf("ÿ��ʳ��÷֣�%d��",add);
	gotoxy(64,16);
	printf("���ܴ�ǽ������ҧ���Լ�");
	gotoxy(64,18);
	printf("�á� �� �� ���ֱ�����ߵ��ƶ�");
	gotoxy(64,20);
	printf("F1 Ϊ���٣�F2 Ϊ����");
	gotoxy(64,22);
	printf("space����ͣ��Ϸ");
	gotoxy(64,24);
    printf("ESC ���˳���Ϸ");
}

/**
 * ���ļ��ж�ȡ��߷�
 */
void File_out()
{
	FILE *fp;
	fp = fopen("save.txt", "a+");       //���ļ�save.txt
	fscanf(fp, "%d", &HighScore);       //���ļ��е���߷ֶ�����
	fclose(fp);                         	 //�ر��ļ�
}

/**
 * ��ʼ������������
 */
void initsnake()
{
    snake *tail;
    int i;
    tail=(snake*)malloc(sizeof(snake));	//����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��
    tail->x=24;         						//�ߵĳ�ʼλ�ã�24,5��
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)       					//������������Ϊ5
    {
        head=(snake*)malloc(sizeof(snake)); //��ʼ����ͷ
        head->next=tail;        				//��ͷ����һλΪ��β
        head->x=24+2*i;         				//������ͷλ��
        head->y=5;
        tail=head;             	 				//��ͷ�����β��Ȼ���ظ�ѭ��
    }
    while(tail!=NULL)							//��ͷ��β���������
    {
        gotoxy(tail->x,tail->y);
		color(14);
        printf("��");       					//�����������ʹ�á����
        tail=tail->next;   	 				//��ͷ�����ϣ������ͷ����һλ��һֱ�������β
    }
}

/**
 * �������ʳ��
 */
void createfood()
{
    snake *food_1;
    srand((unsigned)time(NULL));        		//��ʼ�������
    food_1=(snake*)malloc(sizeof(snake));   	//��ʼ��food_1
    //��֤��Ϊż����ʹ��ʳ��������ͷ���룬Ȼ��ʳ����������������
    while((food_1->x%2)!=0)    		
    {
        food_1->x=rand()%52+2;              		//����ʳ���x����������֣�ʳ���x������2~53֮��
    }
    food_1->y=rand()%24+1;						//ʳ���y������1~24֮��
    q=head;
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y)	//�ж������Ƿ���ʳ���غ�
        {
            free(food_1);               			//��������ʳ���غϣ���ô�ͷ�ʳ��ָ��
            createfood();               			//���´���ʳ��
        }
        q=q->next;
    }
    gotoxy(food_1->x,food_1->y);					//����ʳ���λ��
    food=food_1;
	color(12);
    printf("��");           						//���ʳ��
}







