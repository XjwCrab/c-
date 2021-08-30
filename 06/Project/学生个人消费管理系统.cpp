// 学生个人消费管理系统.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*#include <malloc.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define LEN sizeof(struct scorenode)
#define DEBUG

struct scorenode
{
	int number;/*学号*/
	char name[10];/*姓名*/
	int xiaofei;/*消费情况*/
	struct scorenode *next;
};
typedef struct scorenode score;
int n,k;/*n,k为全局变量，本程序中的函数均可以使用它*/
void menu();
score *creat(void);
score *load(score *head);
score *search(score *head);
score *del(score *head);
score *add(score *head,score *stu);
void print(score *head);
save(score *p1);

/*=========================创建链表，此函数带回一个指向链表头的指针=============================*/
score *creat(void)
{
	system("cls");
	score *head;
    score *p1,*p2,*p3,*max;
	int i,j;
    char t[10];
	n=0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t创建学生消费记录\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字	
    p1=p2=p3=(score *)malloc(LEN);/*head=p3; 开辟一个新单元*/
		printf("\n\n\t    请输入学生信息（输入number为0时，结束创建）：\n");
	repeat1: printf("\t    number:");/*输入学号，学号应大于0*/
       scanf("%d",&p1->number);
	   printf("\t    name:");
	   scanf("%s",&p1->name);/*输入学生姓名*/
	   printf("\t    money:");/*输入消费情况;*/
		scanf("%d",&p1->xiaofei);
		/*输入学号为字符或小于0时，程序报错，提示重新输入学号*/
	while(p1->number<0)
	{
		getchar();
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
		printf("\t    number不能小于0，请重新输入:");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字		
        scanf("%d",&p1->number);
	}
  
	if(p1->number==0)
		goto end;/*当输入的学号为0时，转到末尾，结束创建链表*/
	else
	{
		p3=head;
		if(n>0)
		{
			for(i=0;i<n;i++)
			{
				if(p1->number!=p3->number)
					p3=p3->next;
				else
				{
					SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
					printf("\t    number重复，请重新输入!\n");
					SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
					goto repeat1;	/*当输入的学号已经存在时，程序报错，返回前面重新输入*/   
			}
			}
		}
	 }


	while(p1->number!=0)/*当输入的学号不为0时，循环创建学生信息*/
	{
		n=n+1;
		if(n==1)	//第一个输入的放在第一位
		{
			head=p1;
		}
		else		//其后输入的依次放前面的后面
		{
			p2->next=p1;
		}
		p2=p1;
		p1=(score *)malloc(LEN);
		printf("\t    请输入学生信息（输入number为0时，结束创建）：\n");
		repeat2:
		printf("\t    number:");
		scanf("%d",&p1->number);/*输入学号，学号应大于0*/

		while(p1->number<0)/*输入学号为字符或小于0时，程序报错，提示重新输入学号*/
		{
			getchar();
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
			printf("\t    number不能小于0，请重新输入:");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字			
			scanf("%d",&p1->number);
		}			
		if(p1->number==0)
		{
			goto end;/*当输入的学号为0时，转到末尾，结束创建链表*/
		}
		else
		{
			p3=head;
			if(n>0)
			{
				for(i=0;i<n;i++)
				{
					if(p1->number!=p3->number)
					{
						p3=p3->next;
					}
					else/*当输入的学号已经存在，程序报错，返回前面重新输入*/
					{
						SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
						printf("\t    number重复，请重新输入!\n");
						SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字						
						goto repeat2;    
					}
				}
			}
		}
		printf("\t    name:");
		scanf("%s",&p1->name);/*输入学生姓名*/
		printf("\t    money:");
		scanf("%d",&p1->xiaofei);/*输入消费情况; */
	}//跳出循环
	end: p1=head;
    p3=p1;
	for(i=1;i<n;i++)
    {
		for(j=i+1;j<=n;j++)
		{
			max=p1;
			p1=p1->next;

			if(max->number>p1->number)/*交换前后结点中的消费情况，使之与学号相匹配*/
			{
				/*交换前后结点中的学号值，使得学号大者移到后面的结点中*/
				k=max->number;
				max->number=p1->number;
				p1->number=k;
				/*交换前后结点中的姓名，使之与学号相匹配*/
				strcpy(t,max->name); 
				strcpy(max->name,p1->name);
				strcpy(p1->name,t);                           
           }
         }
		max=head;p1=head;/*重新使max,p指向链表头*/
	}
	p2->next=NULL;/*链表结尾*/	
	printf("\t    共输入 ");  
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色 
	printf("%d  ",n);
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//改回文字颜色，白底黑字 
    printf("条学生消费记录!\n");
	getch();
    return(head);

}

/*===========================从文件读入学生记录=================================================*/
score *load(score *head)
{
	system("cls");
	score *p1,*p2;
    int m=0;
    char filepn[10];
	FILE *fp;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t从文件读入学生消费记录\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	printf("\n\n\t\t请输入文件路径和文件名称（如f:\\mr.txt）:\n\n\t\t\t    ");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为粉色
	scanf("%s",filepn);/*输入文件路径及名称*/
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	if((fp=fopen(filepn,"r+"))==NULL)
	{
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
		printf("\n\n\t    不能打开此文件!\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字			
		getch();
		return 0;
	}
	else
	{
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为紫色
		p1=(score *)malloc(LEN); /*开辟一个新单元*/
		fscanf(fp,"%d%s%d\n",&p1->number,p1->name,&p1->xiaofei);
		printf("\t\t-----------------------------------------\n");/*表格上线*/
		printf("\t\t  | %d\t   | %s\t   | %d\t\n",p1->number,p1->name,p1->xiaofei);		/*文件读入与显示*/
		head=NULL;
		do	
		{
			n=n+1;
			if(n==1)
				head=p1;
			else
				p2->next=p1;
			p2=p1;
			p1=(score *)malloc(LEN);  /*开辟一个新单元*/
			fscanf(fp,"%d%s%d\n",&p1->number,p1->name,&p1->xiaofei);
			printf("\t\t  | %d\t   | %s\t   | %d\t\n",p1->number,p1->name,p1->xiaofei);			/*文件读入与显示*/			
		}while(!feof(fp));
		p2->next=p1;
		p1->next=NULL;
		n=n+1;
	}
	printf("\t\t-----------------------------------------\n");/*表格下线*/
	getch();
	fclose(fp);/*结束读入，关闭文件*/
	return (head);
}


/*=====================查询学生消费=====================================================*/
score *search(score *head)
{
	system("cls");
	int number;
	score *p1,*p2;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t查询学生消费\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	printf("\n\n\t  请输入要查询的学生学号,输入0退出查询（number）:");
	scanf("%d",&number);
	getchar();
	while(number!=0)
	{
		if(head==NULL)
		{
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
			printf("\n\t\t 系统中还没有记录，请创建记录!\n");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
			getchar();
			return(head);
		}
		printf("\t\t---------------------------------------------\n");
		printf("\t\t  | number\t  | name\t  | consume\t \n");
		printf("\t\t---------------------------------------------\n");/*打印表格域*/
		p1=head;
		while(number!=p1->number&&p1->next!=NULL)
		{
			p2=p1;
			p1=p1->next;
		}
        if(number==p1->number)
		{
			 printf("\t\t  | %d\t\t  | %s\t\t   |%d\t\n",p1->number,p1->name,p1->xiaofei);
			 printf("\t\t---------------------------------------------\n");

		}/*打印表格域*/
        else
		{
			printf("\t\t学号为");
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
			printf(" %d ",number);
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
			printf("的学生不存在!\n");
		}
		printf("\n\n\t\t请输入要查询的学生学号（number）:");
		scanf("%d",&number);
		getchar();
	}
		return(head);
}

/*=======================删除学生资料================================================*/
score *del(score *head)
{
	system("cls");
	score *p1,*p2;
	int number;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t删除学生消费\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	printf("\n\n\t  请输入要删除的学生学号,输入0退出删除（number）:");
	scanf("%d",&number);
	getchar();
	while(number!=0)/*输入学号为0时退出*/
	{

		if(head==NULL)
		{
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
			printf("\n\t\t 系统中还没有记录，请创建记录!\n");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
			getchar();
			return(head);
		}

		p1=head;

		while(number!=p1->number&&p1->next!=NULL)   /*p1指向的不是所要找的首结点，并且后面还有结点*/
		{
			p2=p1;
			p1=p1->next;		/*p1后移一个结点*/
		} 
		if(number==p1->number)		/*找到了*/
		{
			if(p1==head)
				head=p1->next;   /*若p1指向的是首结点，把地二个结点地址赋予head*/
			else
			
				p2->next=p1->next;   /*否则将下一个结点地址 赋给前一结点地址*/
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//更改文字颜色，为墨绿色
				printf("\n\t\t\t学号为 ");
				SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色
				printf("%d",number);
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//更改文字颜色，为墨绿色				
				printf(" 的记录已删除!\n");
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
				n=n-1;
			
		}
		else
		{
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色
			printf("\n\t\t\t学号为");  /*找不到该结点*/
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
			printf(" %d ",number); 
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色			
			printf("的学生不存在!\n");  
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
		}
	printf("\n\n\t  继续输入要删除的学生学号,输入0退出删除（number）:");
	scanf("%d",&number);
	getchar();
	}

#ifdef DEBUG
	printf("\n\t\t\t  已经退出删除!\n\n");

#endif
	printf("\t\t    共删除 ");  
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色 
	printf("%d  ",n);
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//改回文字颜色，白底黑字 
    printf("条学生消费记录!\n");
	getch();
	return(head);
}


/*==========================增加记录===================================================*/
score *add(score *head,score *stu)
{
	system("cls");
	score *p0,*p1,*p2,*p3,*max;
    int i,j;
    char t[10];
	p3=stu=(score *)malloc(LEN);/*开辟一个新单元*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t增加学生消费记录\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	repeat4: 
	printf("\n\n\t  请输入要添加的学生学号,输入0退出（number）:");
	scanf("%d",&stu->number);  /*输入学号，学号应大于0*/
    while(stu->number<0)/*输入错误，重新输入学号*/
	{
		getchar();
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
		printf("\n\t    number不能小于0，请重新输入:");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
		scanf("%d",&stu->number);
	}
     /******************************************************/
    if(stu->number==0)/*输入0时，返回主界面*/
	goto end2;/*当输入的学号为0时，转到末尾，结束追加*/
	else
	{
		p3=head;
		if(n>0)
		{
			for(i=0;i<n;i++)
			{
				if(stu->number!=p3->number)
					p3=p3->next;
				else    /*当输入的学号已经存在，程序报错，返回前面重新输入*/
				{
					SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
					printf("\n\t    number重复，请重新输入!\n");
					SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
					goto repeat4; 
				}
			}
		}
	}

  /******************************************************/
   printf("\t    name:");
   scanf("%s",stu->name);            /*输入学生姓名*/
   printf("\t    consuming:");
   scanf("%d",&stu->xiaofei);    
   p1=head;
   p0=stu;
	if(head==NULL)/*当原来链表为空时，从首结点开始存放资料*/
	{
	   head=p0;
	   p0->next=NULL;
	}
	else/*原来链表不为空*/
	{
		if(p1->next==NULL)/*找到原来链表的末尾*/
		{
			p1->next=p0;
			p0->next=NULL;/*将它与新开单元相连接*/
		}
		else
		{
			while(p1->next!=NULL)/*还没找到末尾，继续找*/
			{
				p2=p1;
				p1=p1->next;
			}
			p1->next=p0;
			p0->next=NULL;
		}
	}
	n=n+1;
	p1=head;
	p0=stu;
	for(i=1;i<n;i++)
	{
		for(j=i+1;j<=n;j++)
        {
			max=p1;
			p1=p1->next;
			if(max->number>p1->number) /*交换前后结点中的学号值，使得学号大者移到后面的结点中*/
			{
			k=max->number;
			max->number=p1->number;
			p1->number=k;
        

			strcpy(t,max->name); /*交换前后结点中的姓名，使之与学号相匹配*/
			strcpy(max->name,p1->name);
			strcpy(p1->name,t); /*交换前后结点中的消费情况，使之与学号相匹配*/
    
                 
            }
			max=head;
			p1=head;/*重新使max,p指向链表头*/
		}
	}
	end2:
		printf("\t    现在共有 ");  
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色 
		printf("%d  ",n);
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//改回文字颜色，白底黑字 
		printf("条学生消费记录!\n");
		getch();
		return(head);
}



 /*=========================显示所有记录=================================================*/
void print(score *head)
{
	system("cls");
	score *p;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄,设置屏幕的背景色和文字颜色
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色 
	printf("\n\n\t\t\t\t显示所有学生消费记录\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	if(head==NULL)
	{
        SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
		printf("\n\t\t 系统中还没有记录，请创建记录!\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
	
	}else
	{
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为粉色 
		printf("\n\t\t共有%d名学生\n\n",n);
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//更改表格线颜色，为墨绿色
		printf("\t\t---------------------------------------------------\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//更改文字颜色，为紫色
		printf("\t\t  | number\t|\tname\t|    consume    |\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//更改表格线颜色，为墨绿色
		printf("\t\t---------------------------------------------------\n");//打印表格域
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//恢复文字颜色，白底黑字
		p=head;
		do
		{
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//更改文字颜色，为蓝色

			printf("\t\t     %d\t\t     %s\t      %d\t\n",p->number,p->name,p->xiaofei);
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//更改表格线颜色，为墨绿色
			printf("\t\t---------------------------------------------------\n");//打印表格
			p=p->next;
		}while (p!=NULL);/*打印完成*/
		getch();
		
	}
}



/*=============================保存记录到文件=========================================*/
save(score *p1)
{
	FILE *fp;
	if((fp=fopen("f:\\consume","wb"))==NULL)
	{
		printf("can't open this file!\n");
		return 0;
	}
	else
	{
		while(p1!=NULL)
		{
		fprintf(fp,"%d,%s,%d\t\t\t",p1->number,p1->name,p1->xiaofei);
		p1=p1->next;
		}
		printf("\t\t文件保存在  f:\\consume!\n");
		getch();
	}
	fclose(fp);
}


/*==================================主菜单===================================================*/
void menu()
{

	system("cls");
	printf("\n\n\n");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//获取控制台句柄  
	//printf("\t\t-----------------------------------------\n");	
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//更改文字颜色，为红色 
	printf("\t\t\t   学生个人消费管理系统\t\t\n\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//改回文字颜色，白底黑字 
	printf("\t\t-----------------------------------------\n");
	printf("\t\t\t  1    创建学生消费记录                    \n\n");
	printf("\t\t\t  2    读取学生消费记录                    \n\n");
	printf("\t\t\t  3    查询学生消费记录                    \n\n");
	printf("\t\t\t  4    删除学生消费记录                    \n\n");
	printf("\t\t\t  5    增加学生消费记录                    \n\n");
	printf("\t\t\t  6    显示所有记录                        \n\n");
	printf("\t\t\t  7    保存记录到文件                      \n\n");
	printf("\t\t\t  0    退出本系统                          \n\n");
	printf("\t\t-----------------------------------------\n");
	printf("\t\tchoose(0-7):");


}
/*===============================主函数================================================*/
main()
{
	system("color f0");			//设置控制台为白底黑字
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//获取控制台句柄
	int num;
	score *head=0,*stu=0;
	menu();
	scanf("%d",&num);
	while(1)
	{
		switch(num)
		{
			case 1: head=creat();break;
			case 2: head=load(head);break;
			case 3: head=search(head);break;
			case 4: head=del(head);break;
			case 5: head=add(head,stu);break;
			case 6: print(head);break;
			case 7: save(head);break;	
			case 0: exit(0); 
			default:
				SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);//更改文字颜色，为红色
				printf("\t\t   请输入0~7之间的数!");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//改回文字颜色，白底黑字			
			getch();
		}
		menu();
		scanf("%d",&num);
	}
}

