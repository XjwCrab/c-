//ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�洢Ա����Ϣ�Ľṹ��
typedef struct employee        	
{
    int num;                   	//Ա����
    char duty[10];             	//Ա��ְ��
    char name[10];             	//Ա������
    char sex[3];               	//Ա���Ա�
    unsigned char age;         	//Ա������
    char edu[10];              	//����ˮƽ
    int salary;                	//Ա������
    char tel_office[13];       	//�칫�绰
    char tel_home[13];         	//��ͥ�绰
    char mobile[13];           	//�ֻ�
    char qq[11];               	//qq����
    char address[31];          	//��ͥסַ
    struct employee *next;
}EMP;


//ȫ�ֱ���
char password[9];          		//ϵͳ����
EMP *emp_first,*emp_end;   		//����ָ�������ͷ����β�ڵ��ָ��
char gsave,gfirst;         		//�жϱ�ʾ

//�Զ��庯������
void addemp(void);         	 	//���Ա����Ϣ�ĺ���
void findemp(void);        	 	//����Ա����Ϣ�ĺ���
void listemp(void);        		//��ʾԱ����Ϣ�б�ĺ���
void modifyemp(void);      	 	//�޸�Ա����Ϣ�ĺ���
void summaryemp(void);     	 	//ͳ��Ա����Ϣ�ĺ���
void delemp(void);         	 	//ɾ��Ա����Ϣ�ĺ���
void resetpwd(void);       		//����ϵͳ�ĺ���
void readdata(void);       		//��ȡ�ļ����ݵĺ���
void savedata(void);       		//�������ݵĺ���
int modi_age(int s);       		//�޸�Ա������ĺ���
int modi_salary(int s);    	 	//�޸�Ա�����ʵĺ���
char *modi_field(char *field,char *s,int n);      		//�޸�Ա��������Ϣ�ĺ���
EMP *findname(char *name);                        		//��Ա����������Ա����Ϣ
EMP *findnum(int num);                            	 	//��Ա�����Ų���Ա����Ϣ
EMP *findtelephone(char *name);                   		//��Ա����ͨѶ�������Ա����Ϣ
EMP *findqq(char *name);                          	 	//��Ա����QQ�Ų���Ա����Ϣ
void displayemp(EMP *emp,char *field,char *name); 		//��ʾԱ����Ϣ
void checkfirst(void);                            		//��ʼ�����
void bound(char ch,int n);                        		//�����ֽ���
void login();                                     		//��¼���
void menu();                                      		//���˵��б�




/**
*  Ա����Ϣ���
*/
void addemp()
{
    FILE *fp;               //����һ���ļ���ָ��
    EMP *emp1;              //����һ���ṹ��ָ��
    int i=0;
    char choice='y';
    
    if((fp=fopen("employee.dat","ab"))==NULL)       //�ж���Ϣ�ļ����Ƿ�����Ϣ
    {
        printf("���ļ�employee.dat����\n");
        getch();
        return;                                         
    }     
    
    do{
         i++;
         emp1=(EMP *)malloc(sizeof(EMP));       	//����һ���ڴ�
         if(emp1==NULL)                             //�ж��ڴ��Ƿ����ɹ�
         {
             printf("�ڴ����ʧ�ܣ���������˳���\n");
             getch();
             return;              
         }
         printf("�������%d��Ա������Ϣ��\n",i);
         bound('_',30);
         printf("���ţ�");
         scanf("%d",&emp1->num);
         
         printf("ְ��");
         scanf("%s",&emp1->duty);
         
         printf("������");
         scanf("%s",&emp1->name);
         
         printf("�Ա�");
         scanf("%s",&emp1->sex);
         
         printf("���䣺");
         scanf("%d",&emp1->age);
         
         printf("�Ļ��̶ȣ�");
         scanf("%s",&emp1->edu);
         
         printf("���ʣ�");
         scanf("%d",&emp1->salary);
         
         printf("�칫�绰��");
         scanf("%s",&emp1->tel_office);
         
         printf("��ͥ�绰��");
         scanf("%s",&emp1->tel_home);
         
         printf("�ƶ��绰��");
         scanf("%s",&emp1->mobile);
         
         printf("QQ:");
         scanf("%s",&emp1->qq);
         
         printf("��ַ��");
         scanf("%s",&emp1->address);
         
         emp1->next=NULL;
         if(emp_first==NULL)            //�ж�����ͷָ���Ƿ�Ϊ��
         {
             emp_first=emp1;
             emp_end=emp1;                   
         }else {
             emp_end->next=emp1;
             emp_end=emp1;      
         }
         
         fwrite(emp_end,sizeof(EMP),1,fp);  //�����������������
         
         gfirst=0;
         printf("\n");
         bound('_',30);
         printf("\n�Ƿ��������?(y/n)");
         fflush(stdin);                     //���������
         choice=getch();
         
         if(toupper(choice)!='Y')           //��Сд��ĸת���ɴ�д��ĸ
         {
             fclose(fp);                    //�ر��ļ���
             printf("\n������ϣ������������\n");
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


/*�״�ʹ�ã������û���Ϣ��ʼ��*/
void checkfirst()
{
    FILE *fp,*fp1;                              //�����ļ���ָ��
    char pwd[9],pwd1[9],pwd2[9],pwd3[9],ch;
    int i;
    char strt='8';    
    
    if((fp=fopen("config.bat","rb"))==NULL)     //�ж�ϵͳ�����ļ��Ƿ�Ϊ��
    {
        printf("\n��ϵͳ���������Ӧ�ĳ�ʼ��������\n");
        bound('_',50);
        getch();
        
        do{
            printf("\n�������룬�벻Ҫ����8λ��");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n��ȷ��һ�����룺");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)             //�ж������������Ƿ�һ��
            {
                printf("\n�����������벻һ�£����������룡\n\n");
            }
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\nϵͳ����ʧ�ܣ��밴������˳���");
            getch();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
                 
            pwd2[i]=(pwd[i]^ strt);        
            putw(pwd2[i],fp1);                  //������Ԫ�������ļ�����
            i++;             
        }
        
        fclose(fp1);                            //�ر��ļ���
        printf("\n\nϵͳ��ʼ���ɹ�����������˳��������½��룡\n");
        getch();
        exit(1);
        
    }else{
        i=0;
        while(!feof(fp)&&i<8)                   //�ж��Ƿ���������ļ�
            pwd[i++]=(getw(fp)^strt);           //���ļ����ж����ַ���������
            
            
        pwd[i]='\0';
        
        if(i>=8) i--;
        while(pwd[i]!=-1&&i>=0)
            i--;
        
        pwd[i]='\0';                            //���������һλ�趨Ϊ�ַ����Ľ�����
        strcpy(password,pwd);                   //������pwd�е����ݸ��Ƶ�����password��
    } 
}


void delemp()
{
    int findok=0;
    EMP *emp1,*emp2;
    char name[10],choice;
    system("cls");              //����Ļ����
    printf("\n����Ҫɾ����Ա��������");
    scanf("%s",name);
    
    emp1=emp_first;
    emp2=emp1;
    while(emp1)
    {
        if(strcmp(emp1->name,name)==0)
        {
            findok=1;
            system("cls");
            
            printf("Ա����%s����Ϣ���£�\n",emp1->name);
            bound('_',40);
            printf("���ţ�%d\n",emp1->num);
            printf("ְ��%s\n",emp1->duty);
            printf("������%s\n",emp1->name);
            printf("�Ա�%s\n",emp1->sex);
            printf("���䣺%d\n",emp1->age);
            printf("�Ļ��̶ȣ�%s\n",emp1->edu);
            printf("���ʣ�%d\n",emp1->salary);
            printf("�칫�绰��%s\n",emp1->tel_office);
            printf("��ͥ�绰��%s\n",emp1->tel_home);
            printf("�ƶ��绰��%s\n",emp1->mobile);
            printf("QQ���룺%s\n",emp1->qq);
            printf("סַ:%\n",emp1->address);
            bound('_',40);
            printf("�����Ҫɾ����Ա����(y/n)");
            
            fflush(stdin);          //���������
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
            printf("Ա��%s�ѱ�ɾ��",emp1->name);
            getch();
            free(emp1);
            gsave=1;
            savedata();             //��������
            return;                           
        }  else{        
            emp2=emp1;
            emp1=emp1->next;
        }
    }    
    if(!findok)
    {
        bound('_',40);
        printf("\nû���ҵ������ǣ�%s����Ϣ��\n",name);  //û�ҵ���Ϣ�����ʾ
        getch();           
    } 
    return;
}


void displayemp(EMP *emp,char *field,char *name)
{
    if(emp)
    {
        printf("\n%s:%s��Ϣ���£�\n",field,name);
        bound('_',30); 
        printf("���ţ�%d\n",emp->num);
        printf("ְ��%s\n",emp->duty);
        printf("������%s\n",emp->name);
        printf("�Ա�%s\n",emp->sex);
        printf("���䣺%d\n",emp->age);
        printf("�Ļ��̶ȣ�%s\n",emp->edu);
        printf("���ʣ�%d\n",emp->salary);
        printf("�칫�绰��%s\n",emp->tel_office);
        printf("��ͥ�绰��%s\n",emp->tel_home);
        printf("�ƶ��绰��%s\n",emp->mobile);
        printf("QQ���룺%s\n",emp->qq);
        printf("סַ:%s\n",emp->address);
        bound('_',30);      
    }else {
    bound('_',40);
    printf("���Ͽ���û��%sΪ��%s��Ա����������ȷ�ϣ�",field,name);
    }
    return;
}

/**
* ������������Ա����Ϣ
*/
EMP *findname(char *name)
{
    EMP *emp1;
    emp1=emp_first;
    
    while(emp1)
    {
        if(strcmp(name,emp1->name)==0)      //�Ƚ�����������������еļ��������Ƿ���ͬ
        {
			return emp1;
		}
        emp1=emp1->next;          
    }    
    return NULL;
}

/**
* ����Ա���Ų�ѯ
*/
EMP *findnum(int num)                   //����һ���ṹ��ָ��
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
* ����ͨѶ�����ѯԱ����Ϣ
*/
EMP *findtelephone(char *name)
{
     EMP *emp1;
     
     emp1=emp_first;
     while(emp1)
     {
         if((strcmp(name,emp1->tel_office)==0)||
         (strcmp(name,emp1->tel_home)==0)||
         (strcmp(name,emp1->mobile)==0))        //ʹ���߼����ж�ͨѶ����
         return emp1;
         emp1=emp1->next;
                 
     }  
      return NULL;       
}

/**
* ����Ա��QQ�Ų�ѯԱ����Ϣ
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
* ��ѯԱ����Ϣ
*/
void findemp()
{
     int choice,ret=0,num;
     char str[13];
     EMP *emp1;
     
     system("cls");
     
     do{
         printf("\t��ѯԱ����Ϣ\n");
         bound('_',30);
         printf("\t1.��������ѯ\n");
         printf("\t2.�����Ų�ѯ\n");
         printf("\t3.���绰��ѯ\n");
         printf("\t4.��QQ�Ų�ѯ\n");
         printf("\t0.�������˵�\n");
         bound('_',30);
         printf("\n��ѡ��˵���");
         
         do{
             fflush(stdin);
             choice=getchar();
             system("cls");
             
             switch(choice)
             {
                 case '1':
                      printf("\n����Ҫ��ѯ��Ա��������");
                      scanf("%s",str);
                      
                      emp1=findname(str);
                      displayemp(emp1,"����",str);
                      getch();
                      break; 
                      
                 case '2':
                      printf("\n������Ҫ��ѯ��Ա���Ĺ���"); 
                      scanf("%d",&num); 
                      
                      emp1=findnum(num);
                      itoa(num,str,10);
                      displayemp(emp1,"����",str);
                      getch();
                      break;
                      
                  case '3':
                       printf("\n����Ҫ��ѯԱ���ĵ绰:");
                       scanf("%s",str);
                       
                       emp1=findtelephone(str); 
                       displayemp(emp1,"�绰",str);
                       getch();
                       break;
                       
                  case '4':
                       printf("\n����Ҫ��ѯ��Ա����QQ�ţ�");
                       scanf("%s",str);

					   emp1=findqq(str);
                       displayemp(emp1,"QQ����",str);
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
    printf("\n���Ͽ��е�Ա����Ϣ�б�\n");
    bound('_',40);
    emp1=emp_first;
    while(emp1) 
    {
        printf("���ţ�%d\n",emp1->num);
        printf("ְ��%s\n",emp1->duty);
        printf("������%s\n",emp1->name);
        printf("�Ա�%s\n",emp1->sex);
        printf("���䣺%d\n",emp1->age);
        printf("�Ļ��̶ȣ�%s\n",emp1->edu);
        printf("���ʣ�%d\n",emp1->salary);
        printf("�칫�绰��%s\n",emp1->tel_office);
        printf("��ͥ�绰��%s\n",emp1->tel_home);
        printf("�ƶ��绰��%s\n",emp1->mobile);
        printf("QQ���룺%s\n",emp1->qq);
        printf("סַ:%s\n",emp1->address);  
        bound('_',40);
        emp1=emp1->next;      
    }    
    printf("\n��ʾ��ϣ���������˳���\n");
    getch();
    return;
}


/*����¼����*/
void login()
{
    int i,n=3;
    char pwd[9];
    do{
        printf("���������룺");
        for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
        pwd[i]='\0';

       if(!strcmp(pwd,password))
        {
            printf("\n����������������룡\n");
            getch();
            system("cls");
            n--;
        }
		else
		 break;
    } while(n>0);                       //�����������εĿ���
    if(!n)
    {
        printf("���˳��������������δ������룡");
        getch();
        exit(1);
    }
}


void menu()
{
    char choice;
    system("cls");
    do{
    	printf("\n\t\t\t\t ��ҵԱ������ϵͳ\n\n");
        printf("\t\t\t-------------------------------------\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t1������Ա����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t2����ѯԱ����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t3����ʾԱ����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t4���޸�Ա����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t5��ɾ��Ա����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t6��ͳ��Ա����Ϣ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t7������ϵͳ����\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t|  \t0���˳�ϵͳ\t\t    |\n");
        printf("\t\t\t|\t\t\t\t    |\n");
        printf("\t\t\t-------------------------------------\n");
        printf("\n\t\t\t��ѡ������Ҫ�Ĳ�����");
        
        do{
          	fflush(stdin);
            choice=getchar();
            system("cls");
            switch(choice)
            {
                case '1':
                   addemp();        //����Ա����Ϣ��Ӻ���
                   break;
                case '2':
                   if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
                       getch();
                       break;          
                   }  
                   findemp();       //����Ա����Ϣ���Һ���
                   break;
                case '3':
                   if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
                       getch();
                       break;       
                   }
                   listemp();       //Ա���б���
                   break;
               case '4':
                   if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
                       getch();
                       break;       
                   }
                   modifyemp();     //Ա����Ϣ�޸ĺ���
                   break;
               case '5':
                    if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
                       getch();
                       break;       
                   }
                   delemp();        //ɾ��Ա����Ϣ�ĺ���
                   break;
               case '6':
                    if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
                       getch();
                       break;       
                   }
                   summaryemp();     //ͳ�ƺ���
                   break; 
               case '7':
                   resetpwd();      //����ϵͳ�ĺ���
                   break;
               case '0':
                   savedata();      //�������ݵĺ���
                   exit(0);
				default:
					printf("������0~7֮�������");
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
    printf("ԭ���Ĺ�����Ϊ��%d",salary);
    printf("�µĹ�������");
    scanf("%d",&newsalary);    
    return(newsalary);
}



int modi_age(int age)
{
	int newage;
    printf("ԭ��������Ϊ��%d",age);
    printf("�µ����䣺");
    scanf("%d",&newage);    
    return(newage);
}

char *modi_field(char *field,char *content,int len)
{
     char *str;
     str=malloc(sizeof(char)*len);
     if(str==NULL)
     {
         printf("�ڴ����ʧ�ܣ���������˳���");
         getch();
         return NULL;             
     }
     printf("ԭ��%sΪ��%s\n",field,content);
     printf("�޸�Ϊ�����ݲ�Ҫ����%d���ַ�������",len);
     scanf("%s",str);     
     return str;
}

void modifyemp()
{
     EMP *emp1;
     char name[10],*newcontent;
     int choice;
     
     printf("\n��������Ҫ�޸ĵ�Ա��������:");
     scanf("%s",&name);
     
     emp1=findname(name);
     displayemp(emp1,"����",name);
     
     if(emp1)
     {
     	 printf("\n ��������Ҫ�޸ĵ�����ѡ�\n");
         bound('_',40);
         printf("1.�޸�ְ��                2.�޸�����\n");
         printf("3.�޸��Ļ��̶�            4.�޸Ĺ���\n");
         printf("5.�޸İ칫�ҵ绰          6.�޸ļ�ͥ�绰\n");
         printf("7.�޸��ƶ��绰            8.�޸�QQ���� \n");
         printf("9.�޸�סַ                0.����\n  ");
         bound('_',40);
         
         do{
             fflush(stdin);         //���������
             choice=getchar();
             switch(choice)         //����ѡ����
             {
                 case '1':
                      newcontent=modi_field("ְ��",emp1->duty,10);  //�����޸ĺ����޸Ļ�����Ϣ
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
                      newcontent=modi_field("�Ļ��̶�",emp1->edu,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->edu,newcontent);         //��ȡ����Ϣ����
                          free(newcontent);                    
                      } 
                      break;
                  case '4':
                      emp1->salary=modi_salary(emp1->salary);
                      break;
                 case '5':
                      newcontent=modi_field("�칫�ҵ绰",emp1->tel_office,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_office,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '6':
                      newcontent=modi_field("��ͥ�绰",emp1->tel_home,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->tel_home,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '7':
                      newcontent=modi_field("�ƶ��绰",emp1->mobile,12);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->mobile,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '8':
                      newcontent=modi_field("QQ����",emp1->qq,10);
                      if(newcontent==NULL)
                      {
                          strcpy(emp1->qq,newcontent);
                          free(newcontent);                    
                      } 
                      break;  
                  case '9':
                      newcontent=modi_field("סַ",emp1->address,30);
                      if(newcontent!=NULL)
                      {
                          strcpy(emp1->address,newcontent);
                          free(newcontent);                 //�ͷ��ڴ�ռ�
                      } 
                      break;     
                  case '0':
                      return;             
             }             
         }while(choice<'0' || choice>'9');
         
         gsave=1;
         savedata();                                    //�����޸ĵ�������Ϣ
         printf("\n�޸���ϣ���������˳���\n");
         getch();
     }  
     return;   
}



/*��ȡ����*/ 
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
            printf("�ڴ����ʧ�ܣ�\n");
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
    
    printf("\n����������룺\n");
     for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(password,pwd))
        {
            printf("\n��������밴������˳���\n");       //�ȽϾ����룬�ж��û�Ȩ��
            getch();
            return;             
        }   
     do{
         	printf("\n���������룬�벻Ҫ����8λ��");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n��ȷ��һ�����룺");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');                             //��Ļ�������ʾ�ַ�
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n�����������벻һ�£����������룡\n\n");
            else break;
            
    }while(1);
        
    if((fp1=fopen("config.bat","wb"))==NULL)        //�������ļ�
    {
        printf("\nϵͳ����ʧ�ܣ��밴������˳���");
        getch();
        exit(1);
    }
        
    i=0;
    while(pwd[i])
    {
        putw(pwd[i],fp1);
        i++;
    }
        
    fclose(fp1);                                    //�ر��ļ���
    printf("\n�����޸ĳɹ�����������˳���\n");
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
        printf("���ļ�employee.dat����\n");
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
       	if((strcmp(strw,"ma")==0)||(strcmp(emp1->sex,"��")==0)) man++;
       	else woman++;
       	emp1=emp1->next;
   	}
   
  	printf("\n���������Ա����ͳ����Ϣ��\n");
   	bound('_',40);
   	printf("Ա�������ǣ�%d\n",num);
  	printf("Ա���Ĺ��������ǣ�%d\n",sum);
  	printf("��Ա����Ϊ��%d\n",man);
   	printf("ŮԱ����Ϊ��%d\n",woman);
   	bound('_',40);
   	printf("��������˳���\n");
   	getch();
   	return;
}


int main(void)
{
	system("color f0\n");		//�׵׺���
  	emp_first=emp_end=NULL;
  	gsave=gfirst=0;
  
  	checkfirst();
  	login();
  	readdata();
  	menu();
  	system("PAUSE");
  	return 0;
}
