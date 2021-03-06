//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//存储员工信息的结构体
typedef struct employee        	
{
    int num;                   	//员工号
    char duty[10];             	//员工职务
    char name[10];             	//员工姓名
    char sex[3];               	//员工性别
    unsigned char age;         	//员工年龄
    char edu[10];              	//教育水平
    int salary;                	//员工工资
    char tel_office[13];       	//办公电话
    char tel_home[13];         	//家庭电话
    char mobile[13];           	//手机
    char qq[11];               	//qq号码
    char address[31];          	//家庭住址
    struct employee *next;
}EMP;


//全局变量
char password[9];          		//系统密码
EMP *emp_first,*emp_end;   		//定义指向链表的头结点和尾节点的指针
char gsave,gfirst;         		//判断标示

//自定义函数声明
void addemp(void);         	 	//添加员工信息的函数
void findemp(void);        	 	//查找员工信息的函数
void listemp(void);        		//显示员工信息列表的函数
void modifyemp(void);      	 	//修改员工信息的函数
void summaryemp(void);     	 	//统计员工信息的函数
void delemp(void);         	 	//删除员工信息的函数
void resetpwd(void);       		//重置系统的函数
void readdata(void);       		//读取文件数据的函数
void savedata(void);       		//保存数据的函数
int modi_age(int s);       		//修改员工年龄的函数
int modi_salary(int s);    	 	//修改员工工资的函数
char *modi_field(char *field,char *s,int n);      		//修改员工其他信息的函数
EMP *findname(char *name);                        		//按员工姓名查找员工信息
EMP *findnum(int num);                            	 	//按员工工号查找员工信息
EMP *findtelephone(char *name);                   		//按员工的通讯号码查找员工信息
EMP *findqq(char *name);                          	 	//按员工的QQ号查找员工信息
void displayemp(EMP *emp,char *field,char *name); 		//显示员工信息
void checkfirst(void);                            		//初始化检测
void bound(char ch,int n);                        		//画出分界线
void login();                                     		//登录检测
void menu();                                      		//主菜单列表




/**
*  员工信息添加
*/
void addemp()
{
    FILE *fp;               //声明一个文件型指针
    EMP *emp1;              //声明一个结构型指针
    int i=0;
    char choice='y';
    
    if((fp=fopen("employee.dat","ab"))==NULL)       //判断信息文件中是否有信息
    {
        printf("打开文件employee.dat出错！\n");
        getch();
        return;                                         
    }     
    
    do{
         i++;
         emp1=(EMP *)malloc(sizeof(EMP));       	//申请一段内存
         if(emp1==NULL)                             //判断内存是否分配成功
         {
             printf("内存分配失败，按任意键退出！\n");
             getch();
             return;              
         }
         printf("请输入第%d个员工的信息，\n",i);
         bound('_',30);
         printf("工号：");
         scanf("%d",&emp1->num);
         
         printf("职务：");
         scanf("%s",&emp1->duty);
         
         printf("姓名：");
         scanf("%s",&emp1->name);
         
         printf("性别：");
         scanf("%s",&emp1->sex);
         
         printf("年龄：");
         scanf("%d",&emp1->age);
         
         printf("文化程度：");
         scanf("%s",&emp1->edu);
         
         printf("工资：");
         scanf("%d",&emp1->salary);
         
         printf("办公电话：");
         scanf("%s",&emp1->tel_office);
         
         printf("家庭电话：");
         scanf("%s",&emp1->tel_home);
         
         printf("移动电话：");
         scanf("%s",&emp1->mobile);
         
         printf("QQ:");
         scanf("%s",&emp1->qq);
         
         printf("地址：");
         scanf("%s",&emp1->address);
         
         emp1->next=NULL;
         if(emp_first==NULL)            //判断链表头指针是否为空
         {
             emp_first=emp1;
             emp_end=emp1;                   
         }else {
             emp_end->next=emp1;
             emp_end=emp1;      
         }
         
         fwrite(emp_end,sizeof(EMP),1,fp);  //对数据流添加数据项
         
         gfirst=0;
         printf("\n");
         bound('_',30);
         printf("\n是否继续输入?(y/n)");
         fflush(stdin);                     //清除缓冲区
         choice=getch();
         
         if(toupper(choice)!='Y')           //把小写字母转换成大写字母
         {
             fclose(fp);                    //关闭文件流
             printf("\n输入完毕，按任意键返回\n");
             getch();
             return;                        
         }
         system("cls");      
    }while(1);
}



void bound(char ch,int n)
{
   while(n--)
       putch(ch);
       
   printf("\n");
   return;     
}


/*首次使用，进行用户信息初始化*/
void checkfirst()
{
    FILE *fp,*fp1;                              //声明文件型指针
    char pwd[9],pwd1[9],pwd2[9],pwd3[9],ch;
    int i;
    char strt='8';    
    
    if((fp=fopen("config.bat","rb"))==NULL)     //判断系统密码文件是否为空
    {
        printf("\n新系统，请进行相应的初始化操作！\n");
        bound('_',50);
        getch();
        
        do{
            printf("\n设置密码，请不要超过8位：");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n再确认一次密码：");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)             //判断两次新密码是否一致
            {
                printf("\n两次密码输入不一致，请重新输入！\n\n");
            }
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\n系统创建失败，请按任意键退出！");
            getch();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
                 
            pwd2[i]=(pwd[i]^ strt);        
            putw(pwd2[i],fp1);                  //将数组元素送入文件流中
            i++;             
        }
        
        fclose(fp1);                            //关闭文件流
        printf("\n\n系统初始化成功，按任意键退出后，再重新进入！\n");
        getch();
        exit(1);
        
    }else{
        i=0;
        while(!feof(fp)&&i<8)                   //判断是否读完密码文件
            pwd[i++]=(getw(fp)^strt);           //从文件流中读出字符赋给数组
            
            
        pwd[i]='\0';
        
        if(i>=8) i--;
        while(pwd[i]!=-1&&i>=0)
            i--;
        
        pwd[i]='\0';                            //将数组最后一位设定为字符串的结束符
        strcpy(password,pwd);                   //将数组pwd中的数据复制到数组password中
    } 
}


void delemp()
{
    int findok=0;
    EMP *emp1,*emp2;
    char name[10],choice;
    system("cls");              //对屏幕清屏
    printf("\n输入要删除的员工姓名：");
    scanf("%s",name);
    
    emp1=emp_first;
    emp2=emp1;
    while(emp1)
    {
        if(strcmp(emp1->name,name)==0)
        {
            findok=1;
            system("cls");
            
            printf("员工：%s的信息如下：\n",emp1->name);
            bound('_',40);
            printf("工号：%d\n",emp1->num);
            printf("职务：%s\n",emp1->duty);
            printf("姓名：%s\n",emp1->name);
            printf("性别：%s\n",emp1->sex);
            printf("年龄：%d\n",emp1->age);
            printf("文化程度：%s\n",emp1->edu);
            printf("工资：%d\n",emp1->salary);
            printf("办公电话：%s\n",emp1->tel_office);
            printf("家庭电话：%s\n",emp1->tel_home);
            printf("移动电话：%s\n",emp1->mobile);
            printf("QQ号码：%s\n",emp1->qq);
            printf("住址:%\n",emp1->address);
            bound('_',40);
            printf("您真的要删除该员工吗？(y/n)");
            
            fflush(stdin);          //清除缓冲区
            choice=getchar();
            
            if(choice!='y' && choice!='Y')
            {
            	return;
			}
            if(emp1==emp_first)
			{
				emp_first=emp1->next;
			}
            else
			{
				emp2->next=emp1->next;
            }
            printf("员工%s已被删除",emp1->name);
            getch();
            free(emp1);
            gsave=1;
            savedata();             //保存数据
            return;                           
        }  else{        
            emp2=emp1;
            emp1=emp1->next;
        }
    }    
    if(!findok)
    {
        bound('_',40);
        printf("\n没有找到姓名是：%s的信息！\n",name);  //没找到信息后的提示
        getch();           
    } 
    return;
}


void displayemp(EMP *emp,char *field,char *name)
{
    if(emp)
    {
        printf("\n%s:%s信息如下：\n",field,name);
        bound('_',30); 
        printf("工号：%d\n",emp->num);
        printf("职务：%s\n",emp->duty);
        printf("姓名：%s\n",emp->name);
        printf("性别：%s\n",emp->sex);
        printf("年龄：%d\n",emp->age);
        printf("文化程度：%s\n",emp->edu);
        printf("工资：%d\n",emp->salary);
        printf("办公电话：%s\n",emp->tel_office);
        printf("家庭电话：%s\n",emp->tel_home);
        printf("移动电话：%s\n",emp->mobile);
        printf("QQ号码：%s\n",emp->qq);
        printf("住址:%s\n",emp->address);
        bound('_',30);      
    }else {
    bound('_',40);
    printf("资料库中没有%s为：%s的员工！请重新确认！",field,name);
    }
    return;
}

/**
* 按照姓名查找员工信息
*/
EMP *findname(char *name)
{
    EMP *emp1;
    emp1=emp_first;
    
    while(emp1)
    {
        if(strcmp(name,emp1->name)==0)      //比较输入的姓名和链表中的记载姓名是否相同
        {
			return emp1;
		}
        emp1=emp1->next;          
    }    
    return NULL;
}

/**
* 按照员工号查询
*/
EMP *findnum(int num)                   //声明一个结构体指针
{
   EMP *emp1;
   
   emp1=emp_first;
   while(emp1)
   {
       if(num==emp1->num)  return emp1;
       emp1=emp1->next;           
   }  
   return NULL;  
}
/**
* 按照通讯号码查询员工信息
*/
EMP *findtelephone(char *name)
{
     EMP *emp1;
     
     emp1=emp_first;
     while(emp1)
     {
         if((strcmp(name,emp1->tel_office)==0)||
         (strcmp(name,emp1->tel_home)==0)||
         (strcmp(name,emp1->mobile)==0))        //使用逻辑或判断通讯号码
         return emp1;
         emp1=emp1->next;
                 
     }  
      return NULL;       
}

/**
* 按照员工QQ号查询员工信息
*/
EMP *findqq(char *name)
{
    EMP *emp1;
    
    emp1=emp_first;
    while(emp1)
    {
        if(strcmp(name,emp1->qq)==0)  return emp1;
        emp1=emp1->next;           
    }  
    return NULL;  
}

/**
* 查询员工信息
*/
void findemp()
{
     int choice,ret=0,num;
     char str[13];
     EMP *emp1;
     
     system("cls");
     
     do{
         printf("\t查询员工信息\n");
         bound('_',30);
         printf("\t1.按姓名查询\n");
         printf("\t2.按工号查询\n");
         printf("\t3.按电话查询\n");
         printf("\t4.按QQ号查询\n");
         printf("\t0.返回主菜单\n");
         bound('_',30);
         printf("\n请选择菜单：");
         
         do{
             fflush(stdin);
             choice=getchar();
             system("cls");
             
             switch(choice)
             {
                 case '1':
                      printf("\n输入要查询的员工姓名：");
                      scanf("%s",str);
                      
                      emp1=findname(str);
                      displayemp(emp1,"姓名",str);
                      getch();
                      break; 
                      
                 case '2':
                      printf("\n请输入要查询的员工的工号"); 
                      scanf("%d",&num); 
                      
                      emp1=findnum(num);
                      itoa(num,str,10);
                      displayemp(emp1,"工号",str);
                      getch();
                      break;
                      
                  case '3':
                       printf("\n输入要查询员工的电话:");
                       scanf("%s",str);
                       
                       emp1=findtelephone(str); 
                       displayemp(emp1,"电话",str);
                       getch();
                       break;
                       
                  case '4':
                       printf("\n输入要查询的员工的QQ号：");
                       scanf("%s",str);

					   emp1=findqq(str);
                       displayemp(emp1,"QQ号码",str);
                       getch();
                       break;
                       
                   case '0':
                        ret=1;
                        break;          
             }                         
         }while(choice<'0'||choice>'4');
         
         system("cls");
         if(ret) break;
     }while(1);         
}


void listemp()
{
    EMP *emp1;
    printf("\n资料库中的员工信息列表\n");
    bound('_',40);
    emp1=emp_first;
    while(emp1) 
    {
        printf("工号：%d\n",emp1->num);
        printf("职务：%s\n",emp1->duty);
        printf("姓名：%s\n",emp1->name);
        printf("性别：%s\n",emp1->sex);
        printf("年龄：%d\n",emp1->age);
        printf("文化程度：%s\n",emp1->edu);
        printf("工资：%d\n",emp1->salary);
        printf("办公电话：%s\n",emp1->tel_office);
        printf("家庭电话：%s\n",emp1->tel_home);
        printf("移动电话：%s\n",emp1->mobile);
        printf("QQ号码：%s\n",emp1->qq);
        printf("住址:%s\n",emp1->address);  
        bound('_',40);
        emp1=emp1->next;      
    }    
    printf("\n显示完毕，按任意键退出！\n");
    getch();
    return;
}


/*检测登录密码*/
void login()
{
    int i,n=3;
    char pwd[9];
    do{
        printf("请输入密码：");
        for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
        pwd[i]='\0';

       if(!strcmp(pwd,password))
        {
            printf("\n密码错误，请重新输入！\n");
            getch();
            system("cls");
            n--;
        }
		else
		 break;
    } while(n>0);                       //密码输入三次的控制
    if(!n)
    {
        printf("请退出，你已输入三次错误密码！");
        getch();
        exit(1);
    }
}


void menu()
{
    char choice;
    system("cls");
    do{
    	printf("\n\t\t\t\t 企业员工管理系统\n\n");
        printf("\t\t\t-------------------------------------\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t1、输入员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t2、查询员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t3、显示员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t4、修改员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t5、删除员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t6、统计员工信息\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t7、重置系统密码\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t0、退出系统\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t-------------------------------------\n");
        printf("\n\t\t\t请选择您需要的操作：");
        
        do{
          	fflush(stdin);
            choice=getchar();
            system("cls");
            switch(choice)
            {
                case '1':
                   addemp();        //调用员工信息添加函数
                   break;
                case '2':
                   if(gfirst)
                   {
                       printf("系统信息中无员工信息，请先添加员工信息！\n");
                       getch();
                       break;          
                   }  
                   findemp();       //调用员工信息查找函数
                   break;
                case '3':
                   if(gfirst)
                   {
                       printf("系统信息中无员工信息，请先添加员工信息！\n");
                       getch();
                       break;       
                   }
                   listemp();       //员工列表函数
                   break;
               case '4':
                   if(gfirst)
                   {
                       printf("系统信息中无员工信息，请先添加员工信息！\n");
                       getch();
                       break;       
                   }
                   modifyemp();     //员工信息修改函数
                   break;
               case '5':
                    if(gfirst)
                   {
                       printf("系统信息中无员工信息，请先添加员工信息！\n");
                       getch();
                       break;       
                   }
                   delemp();        //删除员工信息的函数
                   break;
               case '6':
                    if(gfirst)
                   {
                       printf("系统信息中无员工信息，请先添加员工信息！\n");
                       getch();
                       break;       
                   }
                   summaryemp();     //统计函数
                   break; 
               case '7':
                   resetpwd();      //重置系统的函数
                   break;
               case '0':
                   savedata();      //保存数据的函数
                   exit(0);
				default:
					printf("请输入0~7之间的数字");
					getch();
					menu();
            }                             
        } while(choice<'0'||choice>'7');  
        system("cls");
    }while(1);    
}


int modi_salary(int salary)
{
    int newsalary;
    printf("原来的工资数为：%d",salary);
    printf("新的工资数：");
    scanf("%d",&newsalary);    
    return(newsalary);
}



int modi_age(int age)
{
	int newage;
    printf("原来的年龄为：%d",age);
    printf("新的年龄：");
    scanf("%d",&newage);    
    return(newage);
}

char *modi_field(char *field,char *content,int len)
{
     char *str;
     str=malloc(sizeof(char)*len);
     if(str==NULL)
     {
         printf("内存分配失败，按任意键退出！");
         getch();
         return NULL;             
     }
     printf("原来%s为：%s\n",field,content);
     printf("修改为（内容不要超过%d个字符！）：",len);
     scanf("%s",str);     
     return str;
}

void modifyemp()
{
     EMP *emp1;
     char name[10],*newcontent;
     int choice;
     
     printf("\n请输入您要修改的员工的姓名:");
     scanf("%s",&name);
     
     emp1=findname(name);
     displayemp(emp1,"姓名",name);
     
     if(emp1)
     {
     	 printf("\n 请输入你要修改的内容选项！\n");
         bound('_',40);
         printf("1.修改职务                2.修改年龄\n");
         printf("3.修改文化程度            4.修改工资\n");
         printf("5.修改办公室电话          6.修改家庭电话\n");
         printf("7.修改移动电话            8.修改QQ号码 \n");
         printf("9.修改住址                0.返回\n  ");
         bound('_',40);
         
         do{
             fflush(stdin);         //清除缓冲区
             choice=getchar();
             switch(choice)         //操作选择函数
             {
                 case '1':
                      newcontent=modi_field("职务",emp1->duty,10);  //调用修改函数修改基本信息
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->duty,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '2':
                      emp1->age=modi_age(emp1->age);
                      break;
                  case '3':
                      newcontent=modi_field("文化程度",emp1->edu,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->edu,newcontent);         //获取新信息内容
                          free(newcontent);                    
                      } 
                      break;
                  case '4':
                      emp1->salary=modi_salary(emp1->salary);
                      break;
                 case '5':
                      newcontent=modi_field("办公室电话",emp1->tel_office,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_office,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '6':
                      newcontent=modi_field("家庭电话",emp1->tel_home,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_home,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '7':
                      newcontent=modi_field("移动电话",emp1->mobile,12);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->mobile,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '8':
                      newcontent=modi_field("QQ号码",emp1->qq,10);
                      if(newcontent==NULL)
                      {
                          strcpy(emp1->qq,newcontent);
                          free(newcontent);                    
                      } 
                      break;  
                  case '9':
                      newcontent=modi_field("住址",emp1->address,30);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->address,newcontent);
                          free(newcontent);                 //释放内存空间
                      } 
                      break;     
                  case '0':
                      return;             
             }             
         }while(choice<'0' || choice>'9');
         
         gsave=1;
         savedata();                                    //保存修改的数据信息
         printf("\n修改完毕，按任意键退出！\n");
         getch();
     }  
     return;   
}



/*读取数据*/ 
void readdata(void)
{
    FILE *fp;
    EMP *emp1;
    
    if((fp=fopen("employee.dat","rb"))==NULL)
    {
        gfirst=1;
        return;                                        
    }     
    
    while(!feof(fp))
    {
        emp1=(EMP *)malloc(sizeof(EMP));
        if(emp1==NULL)
        {
            printf("内存分配失败！\n");
            getch();
            return;              
        }          
        
        fread(emp1,sizeof(EMP),1,fp);
        if(feof(fp))  break;
        
        if(emp_first==NULL)
        {
           emp_first=emp1;
           emp_end=emp1;                   
        }else{
            emp_end->next=emp1;
            emp_end=emp1;   
        }
        emp_end->next=NULL;
    }
    gfirst=0;
    fclose(fp);
}


void resetpwd()
{
	char pwd[9],pwd1[9],ch;
    int i;
    FILE *fp1;
    
    system("cls");
    
    for(i = 0;i<9;i++)
    {
    	printf("%d",password[i]);
	}
    
    printf("\n请输入旧密码：\n");
     for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(password,pwd))
        {
            printf("\n密码错误，请按任意键退出！\n");       //比较旧密码，判断用户权限
            getch();
            return;             
        }   
     do{
         	printf("\n设置新密码，请不要超过8位：");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n再确认一次密码：");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');                             //屏幕中输出提示字符
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n两次密码输入不一致，请重新输入！\n\n");
            else break;
            
    }while(1);
        
    if((fp1=fopen("config.bat","wb"))==NULL)        //打开密码文件
    {
        printf("\n系统创建失败，请按任意键退出！");
        getch();
        exit(1);
    }
        
    i=0;
    while(pwd[i])
    {
        putw(pwd[i],fp1);
        i++;
    }
        
    fclose(fp1);                                    //关闭文件流
    printf("\n密码修改成功，按任意键退出！\n");
    getch();
    return;
}


void savedata()
{
	FILE *fp;
    EMP *emp1;
      
    if(gsave==0) return;
      
    if((fp=fopen("employee.dat","wb"))==NULL)
    {
        printf("打开文件employee.dat出错！\n");
        getch();
        return;
    }
      
    emp1=emp_first;
    while(emp1)
    {
        fwrite(emp1,sizeof(EMP),1,fp);
        emp1=emp1->next;
    }
      
    gsave=0;
     fclose(fp);
}


void summaryemp()
{
   	EMP *emp1;
   	int sum=0,num=0,man=0,woman=0;
   
   	emp1=emp_first;
   	while(emp1)
   	{
       	num++;
       	sum+=emp1->salary;
       	char strw[2];
       	strncpy(strw,emp1->sex,2);
       	if((strcmp(strw,"ma")==0)||(strcmp(emp1->sex,"男")==0)) man++;
       	else woman++;
       	emp1=emp1->next;
   	}
   
  	printf("\n下面是相关员工的统计信息！\n");
   	bound('_',40);
   	printf("员工总数是：%d\n",num);
  	printf("员工的工资总数是：%d\n",sum);
  	printf("男员工数为：%d\n",man);
   	printf("女员工数为：%d\n",woman);
   	bound('_',40);
   	printf("按任意键退出！\n");
   	getch();
   	return;
}


int main(void)
{
	system("color f0\n");		//白底黑字
  	emp_first=emp_end=NULL;
  	gsave=gfirst=0;
  
  	checkfirst();
  	login();
  	readdata();
  	menu();
  	system("PAUSE");
  	return 0;
}
