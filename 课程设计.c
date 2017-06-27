/*************************************************************************
	> File Name: keshe.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年06月21日 星期三 20时32分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>

int Count=0;
char yes[4] = "yes";
char no[3] = "no";

struct student//学生信息结构体
{
    char name[40];
    char ID[20];
    char sex[4];//linux操作系统下一个汉字三个字节
    char score[5][200];
    int all;
    struct student *next;
};
struct teacher//老师登陆密码结构体
{
    char user[20];
    char pass[18];
    struct teacher *next;
};



void user_in(struct student *phead,char *name);//用户登陆选择操作界面
void menu_sign_in_teacher();//教师用户登陆界面
void menu_sign_in_student();//学生登陆界面
void menu_sign_in();//全部用户登陆界面
void menu_techer();//教师用户登陆成功后的界面
void my_err();//错误函数
char *zhuce();//教师用户注册函数
int save_inf(struct student *phead,char *name);//存文件函数
int teacher(struct student *phead,char *name);//老师登陆后操作
void chakan(struct student *phead);//遍历学生信息从链表
void output(struct student *phead);//打印学生信息
struct student *creat_inf();//录入学生信息函数
struct student *read_inf(char *name);//从文件读入链表
struct student *find(struct student *phead);//查找学生信息
struct student *danfind(struct student *phead,char *id);//单独查找函数，为之后的删除修改做准备
struct student *insert(struct student *phead);//学生信息的插入
struct student *revise(struct student *phead);//自定义修改函数
struct student *delet(struct student *phead);//删除学生信息
char *denglu();//登陆界面
struct student *down_score(struct student *phead);//降序查看
struct student *up_score(struct student *phead);//升序查看


void my_err(const char *err_string,int line)//程序错误查找函数
{
    fprintf(stderr,"line:%d\n",line);
    perror("err_string");
    exit(1);
}

void menu_sign_in()//全部用户登陆界面
{
    system("clear -l");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t┌──────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---------------------欢迎来到班级成绩管理系统---------------------│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---------------------------１、教师登陆---------------------------│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---------------------------２、学生登陆---------------------------│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---------------------------３、注　　册---------------------------│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---------------------------４、说　　明---------------------------│\n");
    printf("\t\t\t\t│──────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---新教师用户请阅读说明后注册登陆，学生用户请用所给账号直接登陆---│\n");
    printf("\t\t\t\t└──────────────────────────────────────────────────────────────────┘\n");

}
char *zhuce()
{
    system("clear -l");
    char pass[100];
    char name[PATH_MAX]={0};
    char name1[PATH_MAX]={0};
    char *p = name1;//记录该用户下的学生成绩文件studet.txt
    char name2[PATH_MAX]={0};//该路径用来储存文件用户名
    int med;//记录mkdir返回值
    int all = 0;//记录二次密码输入的次数
    DIR *dir;//记录打开目录的返回值
    struct teacher *st;
    int fd;
    FILE *fp;
    st = (struct teacher *)malloc(sizeof(struct teacher));
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t用户:\n\t\t\t\t");
    scanf("%s",st->user); 
    strcpy(name2,st->user);
    if((med = mkdir(st->user,S_IRWXU|S_IRWXO)) == -1)
    {
        system("clear -l");
        printf("\n\t\t\t\t\t该用户名已经被注册!\n\t\t\t\t");
        printf("\n\t\t\t\t\t请重新注册!\n\t\t\t\t");
        return (zhuce());
    }
    printf("\n\t\t\t\t密码:\n\t\t\t\t");
    scanf("%s",st->pass);
    if(strlen(st->pass) > 10)
    {
        printf("\t\t\t\t\t\t密码格式错误请重新输入！\n\t\t\t\t");
        return (zhuce());
    }
    printf("\n\t\t\t\t请再次输入密码:");
    scanf("%s",pass);
    while(strcmp(pass,st->pass) != 0)
    {
        system("clear -l");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t密码错误请重新输入！\n\t\t\t\t");
        printf("\n\t\t\t\t若重复三次将重新回到注册页面!\n\t\t\t\t");
        memset(pass, 0, sizeof(pass));
        printf("\n\t\t\t\t请您重新输入密码:\n\t\t\t\t");
        scanf("%s",pass);
        all++;
        if(all==3)
        {
            rmdir(st->user);
            return (zhuce());
        }
    }
    strcat(name,st->user);//复制文件路径
    strcat(name,"/");
    strcat(name1,name);
    strcat(name1,"student.txt");//每一个教师用户目录下存一份学生信息的文件stu->user/student.txt
    strcat(name,"user.txt");//stu->user/user.txt
    strcpy(pass,st->pass);//将密码复制到数组中
    if(med == 0)
    {
        if((dir = (opendir(st->user))) == NULL)
           {
               printf("\n\t\t\t\t注册失败，请重新注册！\n\t\t\t\t");
           }
        else
        {
            if((creat(name, S_IRWXU))==-1)
            {
                printf("\n\t\t\t\t失败!\n\t\t\t\t");
            }
            else{
               /* if((fd = fopen(name,"wt+"))!=NULL)
                {
                    if((fwrite(pass, sizeof(pass), 1, fd))!= 1)
                    {
                        printf("失败\n");
                        fclose(fd);
                    }
                    else{
                        printf("注册成功!\n");
                        fclose(fd);
                    }
                }*/
                if((fd = open(name,O_CREAT|O_RDWR,S_IRWXU))!= -1)
                {
                    if((write(fd, pass, strlen(pass)))!= strlen(pass))
                    {
                        printf("\n\t\t\t\t失败\n\t\t\t\t");
                        close(fd);
                    }
                    else{
                        if((fp = fopen("users.txt","a+"))!=NULL)
                        {
                            int i =0;
                           if((i = (fprintf(fp, "%s\n", name2))) != (strlen(name2)+1))
                            {
                                printf("\n\t\t\t\t注册失败，请重新注册!\n\t\t\t\t");
                                fclose(fp);
                                return (zhuce());
                            }
                            else{
                                printf("\n\t\t\t\t\t注册成功!\n\t\t\t\t");
                                fclose(fp);
                                //return (zhuce());
                            }
                        }
                        if(fp == NULL)
                        {
                            printf("\n\t\t\t\t注册失败!\n\t\t\t\t");
                            fclose(fp);
                            return (zhuce());
                        }
                        return p;
                        close(fd);
                    }
                }
            }

        }
        closedir(dir);
    }
}
char *denglu()//教师登陆函数
{
    system("clear -l");
    printf("\n\n\n\n\n\n");
    DIR *dir;
    struct teacher *st;
    FILE *fp;
    FILE *fp2;
    char name1[PATH_MAX]={0};//储存登陆的用户名
   // char name2[PATH_MAX]={0};
    char *p = name1;//获取用户名，为student.txt路径做准备
    char pass_user[100] = {0};
    char password[20]={0};//储存登陆输入的密码
    char Read_buf[20]={0};//存从文件中读出来的密码
    st = (struct teacher *)malloc(sizeof(struct teacher));
    printf("\n\t\t\t\t用户名:\n\t\t\t\t");
    scanf("%s",st->user);
    strcpy(name1,st->user);
    strcpy(pass_user,st->user);
    strcat(pass_user,"/user.txt");
    printf("\n\t\t\t\t密码:\n\t\t\t\t");
    scanf("%s",st->pass);
    strcpy(password,st->pass);
    if((fp = fopen("users.txt","rt")) == NULL)//打开存放所有用户名的文件
    {
        printf("\n\t\t\t\t登陆失败请重新登陆！\n\t\t\t\t");
        return (denglu());
    }
    else//成功打开用户名组文件users.txt fp
    {
        
        while(fscanf(fp, "%s\n", name1) != EOF)//从用户名文件中读取用户名存入数组
        {
            if(strcmp(st->user,name1) == 0)//判断所有用户名中是否有符合的名称
            {
              if((dir =  opendir(name1))!=NULL)//符合打开该用户的目录
                {
                    if((fp2 = fopen(pass_user,"rt")) !=NULL)//成功打开密码文件fp2
                       {
                                int i=0,a=0;
                                i = fread(Read_buf,sizeof(password),1,fp2);
                                a = sizeof(password);
                                if(strcmp(Read_buf,password) == 0)
                                {
                                    system("echo '\033[;34m\n\t\t\t\t登陆成功，请稍后.....\033[0m'|pv -qL 10\n\t\t\t\t");
                                    strcat(name1,"/");
                                    strcat(name1,"student.txt");
                                    fclose(fp);
                                    fclose(fp2);
                                    return p;
                                }
                       
                           else
                           {
                               fclose(fp);
                               fclose(fp2);
                               printf("\n\t\t\t\t密码或用户名不匹配，请核对后再登陆！\n\t\t\t\t");
                               return denglu();
                           }

                       fclose(fp2);     
                       }
                    else//未成功打开用户密码文件
                    {
                        printf("\n\t\t\t\t密码或者用户名不匹配，请核对后再登陆！\n\t\t\t\t");
                        fclose(fp);
                        //fclose(fp2);
                        return denglu();
                    }
                    closedir(dir);
                }
                else//未成功打开用户目录文件
                {
                    printf("\n\t\t\t\t登陆失败，请稍后再登陆！\n\t\t\t\t");
                    return denglu();
                }

            } 
        }
        if(fscanf(fp, "%s\n", name1) == EOF)//检索完用户名文件user.txt未发现该用户名
        
        {
            int back = 0;
            printf("\n\t\t\t\t请核对用户名!\n\t\t\t\t");
            fclose(fp);//返回函数之前需要关闭用户名组文件user.txt
            printf("\n\t\t\t\t若是新教师注册用户请输入１，若用户名错误输入２返回登陆界面\n\t\t\t\t");
            if(back == 1)
            {
                return zhuce();
            }
            if(back == 2)
            {
                return denglu();
            }


        }

    }
    fclose(fp);
    
}
int save_inf(struct student *phead,char *name)//将每次的信息变动存入文件
{
    struct student *stu;
   // struct student *p = phead->next;
    FILE *fp;
    char *filename = name;
    int a;

    if((fp = fopen(filename,"wt")) == NULL)
    {
        printf("\n\t\t\t\t打开文件错误!\n\t\t\t\t");
    }
    for(stu = phead->next;stu != NULL;stu = stu->next)
    {
       if((a = (fwrite(stu, sizeof(struct student), 1, fp)))!= 1)
        {
            printf("\n\t\t\t\t写文件错误\n\t\t\t\t");
        }

    }
    fclose(fp);
    return 0;
}

struct student *read_inf(char *name)//从文件读入链表
{
    struct student *phead,*r,*stu;
    int fp;
    char read_buf[sizeof(struct student)];
    char *filename=name;
    if((fp = open(filename,O_CREAT|O_RDWR,S_IRWXU)) == -1)//用open打开student.txt文件
    {
        printf("\n\t\t\t\t读文件出错!\n\t\t\t\t");
    }
    /*尾插入法读入数据存入链表中*/
    phead = (struct student *)malloc(sizeof(struct student));
    phead->next = NULL;
    r = phead;
    
    while((read(fp, read_buf, sizeof(struct student))) > 0)
    {
        stu = (struct student *)malloc(sizeof(struct student));//开辟指针空间
 
        memcpy(stu,read_buf,sizeof(struct student));//从字符串中的一个结构体大小的内容复制到链表stu中
        r -> next = stu;
        r = stu;
    }
    r -> next = NULL;
    close(fp);
    return phead;
}
void user_in(struct student *phead,char *name)//用户登陆选择操作界面
{
    char yes[4]="yes";
    char no[3]="no";
    int choice = 0;
    int a;
        menu_sign_in();
        printf("\n\t\t\t\t根据要进入的界面输入数字:\n\t\t\t\t");
        scanf("%d",&a);
        switch(a)
        {
            case 1:
            {
               name =  denglu();
                teacher(phead,name);
                break;
            }
            case 2:
            {
                name = denglu();
                break;
            }
            case 3:
            {
                name = zhuce();
                return user_in(phead,name);
                //注册函数，仅限于老师注册
                break;
            }
            case 4:
            {
                break;
            }
            default:
            {
                printf("\n\t\t\t\t请检查输入的功能数字格式是否符合\n\t\t\t\t");
                //return (user_in());
            }
        }
}
void menu_sign_in_teacher()//老师登陆界面
{
    char user[20];
    char pass[11];
    system("clear -l");
    printf("\t\t欢迎教师进入登陆界面！\n");
   // printf("\n\n\n\n\n\n\n\n\n\n");
   // printf("\t\t\t\t                         账号:");
    scanf("密码:%s",user);
  // printf("\n\t\t\t\t                         密码:");
   // scanf("%s",pass);

}
void menu_sign_in_student()//学生登陆界面
{
    char name[20];
    char pass[11];
    system("clear -l");
    printf("\t\t欢迎学生进入登陆界面!\n");
    printf("\t\t\t\t                         账号:");
    scanf("%s",name);
    printf("\n\t\t\t\t                         密码:");
    scanf("%s",pass);
}
void menu_techer()//老师菜单显示函数
{
    system("clear -l");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│--------------------------1、录入学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------2、增加学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------3、查找学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------4、删除学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------5、修改学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------6、查看所有学生信息----------------------│\n");
    printf("\t\t\t\t│--------------------------7、降序查看成绩--------------------------│\n");
    printf("\t\t\t\t│--------------------------8、升序查看成绩--------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照功能选项输入您的选择！----------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    
}


struct student *creat_inf()//学生信息的录入,创建一个有内容的链表
{
    struct student *stu,*phead,*r;
    char choise[5];
    int choice = 1;
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------1、录入学生信息--------------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    phead = (struct student *)malloc(sizeof(struct student));//创建头节点开辟空间
    phead->next = NULL;
    r = phead;
    do{
        stu = (struct student *)malloc(sizeof(struct student));
        printf("\n\t\t\t\t请输入学生姓名:\n\t\t\t\t");
        scanf("%s",stu->name);
        printf("\n\t\t\t\t请输入学生的学号:\n\t\t\t\t");
        scanf("%s",stu->ID);
        printf("\n\t\t\t\t请输入学生性别:\n\t\t\t\t");
        scanf("%s",stu->sex);
        printf("\n\t\t\t\t请输入学生成绩:\n\t\t\t\t");
        printf("\n\t\t\t\t数学:\n\t\t\t\t");
        scanf("%s",stu->score[0]);
        printf("\n\t\t\t\t英语:\n\t\t\t\t");
        scanf("%s",stu->score[1]);
        printf("\n\t\t\t\t语文:\n\t\t\t\t");
        scanf("%s",stu->score[2]);
        printf("\n\t\t\t\t物理:\n\t\t\t\t");
        scanf("%s",stu->score[3]);
        printf("\n\t\t\t\t化学:\n\t\t\t\t");
        scanf("%s",stu->score[4]);
        r->next = stu;
        r = stu;
        Count++;
        printf("\n\t\t\t\t是否继续，继续请输入yes，不继续请输入no\n\t\t\t\t");
        scanf("%s",choise);
      // printf("%d\n",strcmp(choise,yes));
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }
       /* else{
            my_err("input",__LINE__);
        }*/
        
    }while(choice);
    r->next = NULL;
    return phead;    
}
struct student *insert(struct student *phead)//学生信息的插入
{
    struct student *p = phead;
    struct student *r,*stu;
    char choise[5];
   // char yes[4]="yes";
   // char no[4]="no";
    int choice = 0;
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------2、增加学生信息--------------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    while(p && p->next!= NULL)
    {
        p = p->next;//找出链表末尾
    }
    printf("\n\t\t\t\t请输入要加入学生的详细信息\n");
    do
    {
        stu = (struct student *)malloc(sizeof(struct student));
        printf("\n\t\t\t\t请输入学生姓名:\n\t\t\t\t");
        scanf("%s",stu->name);
        printf("\n\t\t\t\t请输入学生的学号:\n\t\t\t\t");
        scanf("%s",stu->ID);
        printf("\n\t\t\t\t请输入学生性别:\n\t\t\t\t");
        scanf("%s",stu->sex);
        printf("\n\t\t\t\t请输入学生成绩:\n\t\t\t\t");
        printf("\n\t\t\t\t数学:\n\t\t\t\t");
        scanf("%s",stu->score[0]);
        printf("\n\t\t\t\t英语:\n\t\t\t\t");
        scanf("%s",stu->score[1]);
        printf("\n\t\t\t\t语文:\n\t\t\t\t");
        scanf("%s",stu->score[2]);
        printf("\n\t\t\t\t物理:\n\t\t\t\t");
        scanf("%s",stu->score[3]);
        printf("\n\t\t\t\t化学:\n\t\t\t\t");
        scanf("%s",stu->score[4]);
        p->next = stu;
        stu->next = NULL;
        p = stu;
        Count++;
        printf("\n\t\t\t\t是否继续增加学生信息,继续请输入yes,不继续输入no:\n\t\t\t\t");
        scanf("%s",choise);
       // printf("%d\n",strcmp(choise,yes));
        if(strcmp(choise,yes) == 0)
        {
            //printf("%d",strcmp(choise,yes));
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }
    }while(choice);
    return phead;
}

struct student *find(struct student *phead)//查找学生信息
{
    
    struct student *p = phead->next;
    char choise[5];
    int choice = 0;
    char id[20];
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------3、查找学生信息--------------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    do{
        printf("\n\t\t\t\t请输入学生学号查找学生详细信息:\n\t\t\t\t");
        scanf("%s",id);
        p = phead->next;
        while(p != NULL)
        {
            if(strcmp(id,p->ID) == 0)//看学号是否匹配
            {
                printf("\n\t\t\t\t已经查找到该生信息！\n");
                printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
                printf("\t\t\t\t│--------------------------该学生学生成绩---------------------------│\n");
                printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
		        printf("\t\t\t\t│---姓名---│--学号--│-性别-│-数学-│-语文-│-英语-│-物理-│-化学-│总 分│\n");
                printf("\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                printf("\n\t\t\t\t│%-10s│",p->name);
                printf("%-8s│",p->ID);
                printf("%-6s│",p->sex);
                for(int i = 0;i<5;i++)
                {
                    printf("%-6s│",p->score[i]);
                }
 		        printf("%-5d│",p->all);
                printf("\t\t\t\t");
 		        printf("\n\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                printf("\n\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
            }
            p = p->next;
        }
        if(p == NULL)
        {
            printf("\n\t\t\t\t未找到该生信息，请核对学号再输入!\n\t\t\t\t");
        }
        printf("\n\t\t\t\t是否继续查找学生信息,继续请输入yes,不继续输入no\n\t\t\t\t");
        scanf("%s",choise);
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice =0;
        }

    }while(choice);
    return phead;
}

struct student *danfind(struct student *phead,char *id)//单独查找函数，为之后的删除修改做准备
{
    struct student *p = phead->next;
    while(p!= NULL)
    {
        if(strcmp(p->ID,id) == 0)
        {
                printf("\n\t\t\t\t查找到该学生信息!\n\t\t\t\t");
                printf("\n\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
                printf("\t\t\t\t│--------------------------该学生学生成绩---------------------------│\n");
                printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
		        printf("\t\t\t\t│---姓名---│--学号--│-性别-│-数学-│-语文-│-英语-│-物理-│-化学-│总 分│\n");
                printf("\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                printf("\n\t\t\t\t│%-10s│",p->name);
                printf("%-10s│",p->ID);
                printf("%-8s│",p->sex);
                for(int i = 0;i<5;i++)
                {
                    printf("%-6s│",p->score[i]);
                }
 		printf("%-5d│",p->all);
                printf("\t\t\t\t");
 		printf("\n\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                printf("\n\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
            break;
        }
        p = p->next;
    }
    if(p==NULL)
    {
        printf("\n\t\t\t\t未找到与该学号匹配的学生，请核对学号!\n\t\t\t\t");
    }
    return p;
}

struct student *delet(struct student *phead)//删除学生信息
{
    struct student *p = phead;
    struct student *pre = p;
    struct student *stu;
    char choise[5];
    int choice = 0;
    char id[20];
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------4、删除学生信息--------------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    do
    {
        printf("\n\t\t\t\t请输入被删除学生的学号:\n\t\t\t\t");
        scanf("%s",id);
        stu = danfind(phead,id);//接受单个查找到的链表节点
        while(p != NULL)
        {
            if(strcmp(p->ID,id) == 0)
            {
                pre->next = p->next;
                free(p);
                printf("\n\t\t\t\t删除成功!\n");
                Count--;
                break;
            }
            pre = p;
            p = p->next;
        }
        printf("\n\t\t\t\t是否继续删除,继续请输入yes,不继续输入no\n\t\t\t\t");
        scanf("%s",choise);
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
            p = phead;
            pre = p;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
                
        }
    }while(choice);
    return phead;
}

struct student *revise(struct student *phead)//自定义修改函数
{
    struct student *p = phead;
    struct student *new;
    struct student *stu;
    char choise[5];
    int choice = 0;
    char fenshu[5][10]={"数学","语文","英语","物理","化学"};
    int a;//选择修改种类
    char id[20];
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------5、修改学生信息--------------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    do
    {
        printf("\n\t\t\t\t请输入被修改学生原来录入的学号:\n");
        scanf("%s",id);
        system("cls");
        new = (struct student *)malloc(sizeof(struct student));
        stu =danfind(phead,id);
        if(stu!=NULL)
        {
            printf("\n\t\t\t\t该生信息查找结果如上!\n\t\t\t\t");
            printf("\n\t\t\t\t若查找失败请核对学号,若查找成功请根据以下提示修改信息!\n\t\t\t\t");
            printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
            printf("\t\t\t\t│--------------------------1、修改姓名------------------------------│\n");
            printf("\t\t\t\t│--------------------------2、修改学号------------------------------│\n");
            printf("\t\t\t\t│--------------------------3、修改性别------------------------------│\n");
            printf("\t\t\t\t│--------------------------4、修改成绩------------------------------│\n");
            printf("\t\t\t\t│--------------------------5、显示修改信息--------------------------│\n");
            printf("\t\t\t\t│-----------------------根据需要输入功能序号------------------------│\n");
            printf("\t\t\t\t│-------------------------------------------------------------------│\n");
            printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
            scanf("%d",&a);
            switch(a)
            {
                case 1:
                {
                    printf("\n\t\t\t\t请输入学生姓名:\n\t\t\t\t");
                    scanf("%s",new->name);
                    strcpy(stu->name,new->name);
                    break;
                }
                case 2:
                {
                    printf("\n\t\t\t\t请输入学生学号:\n\t\t\t\t");
                    scanf("%s",new->ID);
                    strcpy(stu->ID,new->ID);
                    break;
                }
                case 3:
                {
                    printf("\n\t\t\t\t请输入学生性别:\n\t\t\t\t");
                    scanf("%s",new->sex);
                    strcpy(stu->sex,new->sex);
                    break;
                }
                case 4:
                {
                    printf("\n\t\t\t\t请输入学生成绩:\n\t\t\t\t");
                    for(int i =0; i<5;i++)
                    {
                        printf("%s:",fenshu[i]);
                        scanf("%s",new->score[i]);
                        strcpy(stu->score[i], new->score[i]);
                    }
                    break;
                }
                case 5:
                {
                    printf("\n\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
                    printf("\t\t\t\t│--------------------------该学生学生成绩---------------------------│\n");
                    printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
		            printf("\t\t\t\t│---姓名---│--学号--│-性别-│-数学-│-语文-│-英语-│-物理-│-化学-│总 分│\n");
                   printf("\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                   printf("\n\t\t\t\t│%-10s│",stu->name);
                   printf("%-8s│",stu->ID);
                   printf("%-6s│",stu->sex);
                  for(int i = 0;i<5;i++)
                  {
                    printf("%-6s│",stu->score[i]);
                  }
 		            printf("%-5d│",stu->all);
                    printf("\t\t\t\t");
 		            printf("\n\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
                    printf("\n\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
                    break;
                }
                default:
                {
                    my_err("switch",__LINE__);
                    break;
                }            
            }
        }
        if(stu == NULL)
        {
            printf("\n\t\t\t\t学号有错误请核对再输入！\n\t\t\t\t");
            return revise(phead);
        }
        printf("\n\t\t\t\t是否继续修改,继续请输入yes,不继续输入no!\n\t\t\t\t");
        scanf("%s",choise);
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }

    }while(choice);
    return phead;

}
struct student *all_score(struct student *phead)//将字符型分数转化为整型并且算出总分
{
    int sum = 0;
    int i = 0;
    char score[5][20]={0};
    struct student *p = phead;
    struct student *stu = p->next;
    for(stu; stu != NULL; stu = stu->next)
    {
        sum = 0;
        for(i=0; i<5; i++)
        {
            strcpy(score[i],stu->score[i]);
            sum = atoi(score[i]) + sum;
        }
        stu->all = sum;
    }
    return phead;
}
struct student *up_score(struct student *phead)//总成绩升序输出
{
    struct student *stu,*p = phead;
    struct student *r;
    struct student *stu1;
    int temp;
    int j=0;
    char id[11]={0};
    char name[20]={0};
    char score[500]={0};
    char sex[4]={0};
    int i = 0;
    int coun=0;
    for(stu = phead->next; stu !=NULL; stu = stu->next)
    { 
       for(stu1 = stu->next; stu1!=NULL; stu1 = stu1->next)
        {
            if(stu->all < stu1->all)
            {
                temp = stu->all;
                stu->all = stu1->all;
                stu1->all = temp;
                strcpy(id,stu->ID);
                strcpy(stu->ID,stu1->ID);
                strcpy(stu1->ID,id);

                strcpy(sex,stu->sex);
                strcpy(stu->sex,stu1->sex);
                strcpy(stu1->sex,sex);

                strcpy(name,stu->name);
                strcpy(stu->name,stu1->name);
                strcpy(stu1->name,name);

                for(j = 0; j<5; j++)
                {
                    strcpy(score,stu1->score[j]);
                    strcpy(stu1->score[j],stu->score[j]);
                    strcpy(stu->score[j],score);
                }
                memset(id, 0, 11*sizeof(char));//数组清零
                memset(name, 0, 20*sizeof(char));//数组清零
                memset(sex, 0, 4*sizeof(char));//数组清零
                memset(score, 0, 500*sizeof(char));//数组清零
            }
        }
    }
    return phead;
}

struct student *down_score(struct student *phead)//总成绩降序输出
{
    struct student *stu,*p = phead;
    struct student *r;
    struct student *stu1;
    int temp;
    int j=0;
    char id[11]={0};
    char name[20]={0};
    char score[500]={0};
    char sex[4]={0};
    int i = 0;
    int coun=0;
    for(stu = phead->next; stu !=NULL; stu = stu->next)
    { 
       for(stu1 = stu->next; stu1!=NULL; stu1 = stu1->next)
        {
            if(stu->all > stu1->all)
            {
                temp = stu->all;
                stu->all = stu1->all;
                stu1->all = temp;
                strcpy(id,stu->ID);
                strcpy(stu->ID,stu1->ID);
                strcpy(stu1->ID,id);

                strcpy(sex,stu->sex);
                strcpy(stu->sex,stu1->sex);
                strcpy(stu1->sex,sex);

                strcpy(name,stu->name);
                strcpy(stu->name,stu1->name);
                strcpy(stu1->name,name);

                for(j = 0; j<5; j++)
                {
                    strcpy(score,stu1->score[j]);
                    strcpy(stu1->score[j],stu->score[j]);
                    strcpy(stu->score[j],score);
                }
                memset(id, 0, 11*sizeof(char));//数组清零
                memset(name, 0, 20*sizeof(char));//数组清零
                memset(sex, 0, 4*sizeof(char));//数组清零
                memset(score, 0, 500*sizeof(char));//数组清零
            }
        }
    } 
    return phead;
}

void chakan(struct student *phead)//遍历学生信息从链表
{
   // int choice=0;
    struct student *p = phead->next;
    printf("\n\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------6、查看学生信息--------------------------│\n");
    printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│-----------------------请按照文字提示录入信息！--------------------│\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------该班级所有学生成绩-----------------------│\n");
    printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---姓名---│--学号--│-性别-│-数学-│-语文-│-英语-│-物理-│-化学-│总 分│\n");
    printf("\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
    while(p != NULL)
    {
        printf("\n\t\t\t\t│%-10s│",p->name);
        printf("%-8s│",p->ID);
        printf("%-6s│",p->sex);
        for(int i = 0;i<5;i++)
        {
            printf("%-6s│",p->score[i]);
        }
 	    printf("%-5d│",p->all);
        printf("\t\t\t\t");
        p = p->next;
	    printf("\n\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
    }
    printf("\n\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
}
void output(struct student *phead)//链表遍历函数
{
    struct student *p = phead->next;
    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│--------------------------该班级所有学生成绩-----------------------│\n");
    printf("\t\t\t\t│───────────────────────────────────────────────────────────────────│\n");
    printf("\t\t\t\t│---姓名---│--学号--│-性别-│-数学-│-语文-│-英语-│-物理-│-化学-│总 分│\n");
    printf("\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
    while(p != NULL)
    {
        printf("\n\t\t\t\t│%-10s│",p->name);
        printf("%-8s│",p->ID);
        printf("%-6s│",p->sex);
        for(int i = 0;i<5;i++)
        {
            printf("%-6s│",p->score[i]);
        }
 	    printf("%-5d│",p->all);
        printf("\t\t\t\t");
        p = p->next;
	    printf("\n\t\t\t\t│──────────│────────│──────│──────│──────│──────│──────│──────│─────│");
    }
    printf("\n\t\t\t\t└───────────────────────────────────────────────────────────────────┘\n");
}



int teacher(struct student *phead,char *name)//老师登陆后操作
{
    
    int a=0;
    int z=0;
    char choise[5];
    int choice = 0;
    do
    {

        menu_techer();
        printf("\n\t\t\t\t请根据需求输入选项:\n\t\t\t\t");
        scanf("%d",&a);
       // system("clear -l");//linux清屏
        switch(a)
        {
             case 1://用户添加学生信息
            {
                
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 phead = creat_inf(phead);
		         phead = all_score(phead);
                 save_inf(phead,name);
                 break;
            }
            case 2://用户增加信息
             {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\n\n\n\n\n\t\t\t\t请录入学生信息再添加!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                 phead = insert(phead);
		         phead = all_score(phead);
                 save_inf(phead,name);
                break;
            }
            case 3://用户查找学生信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\t\t\t\t\t\t");
                     printf("\n\t\t\t\t请录入学生信息再查找!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                    
                 }
                phead = find(phead);
                save_inf(phead,name);
                break;
            }
            case 4://用户删除信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\t\t\t\t请录入学生信息再删除!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                phead = delet(phead);
                save_inf(phead,name);
                break;
            }
            case 5://用户修改学生信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\t\t\t\t请录入学生信息再修改!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                phead = revise(phead);
		         phead = all_score(phead);
                save_inf(phead,name);
                break;
            }
            case 6://无排序法，用户查看录入信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\t\t\t\t请录入学生信息再查看!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                chakan(phead);
                break;
            }
            case 7://用户查看降序成绩信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\t\t\t\t请录入学生信息再查看!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                phead = up_score(phead);
               save_inf(phead,name);
                output(phead);
                break;
            }
            case 8://用户查看升序学生成绩信息
            {
                system("clear -l");
                printf("\n\n\n\n\n\n");
                 /*在增加信息前首先检测该用户是否录入信息*/
                phead = read_inf(name);
                 if(phead->next == NULL)
                 {
                     printf("\n\t\t\t\t请录入学生信息再查看!\n\t\t\t\t");
                     printf("\n\t\t\t\t返回主菜单请输入１，不返回并且退出请输入０:\n\t\t\t\t");
                     scanf("%d",&z);
                     if(z == 1)
                     {
                         return teacher(phead,name);
                     }
                     if(z == 0)
                     {
                         exit(0);
                     }
                 }
                phead = down_score(phead);
                save_inf(phead,name);
                output(phead);
                    
            }
        }
        printf("\n\t\t\t\t是否返回教师操作界面(yes or no):\n\t\t\t\t");
        scanf("%s",choise);
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }
    
    }while(choice);
return 0;
}

int main()
{
    struct student *phead;
    int a=0;
    char *name;
    user_in(phead,name);
    return 0;
}
