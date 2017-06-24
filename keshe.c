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
    struct student *next;
};
struct teacher//老师登陆密码结构体
{
    char user[20];
    char pass[18];
    struct teacher *next;
};


void menu_sign_in_teacher();//教师用户登陆界面
void menu_sign_in_student();//学生登陆界面
void menu_sign_in();//全部用户登陆界面
void menu_techer();//教师用户登陆成功后的界面
void my_err();//错误函数
char *zhuce();//教师用户注册函数
int save_inf(struct student *phead,char *name);//存文件函数
void teacher(struct student *phead,char *name);//老师登陆后操作
struct student *creat_inf();//录入学生信息函数
struct student *read_inf(char *name);//从文件读入链表
struct student *find(struct student *phead);//查找学生信息
struct student *insert(struct student *phead);//学生信息的插入
struct student *revise(struct student *phead);//自定义修改函数
struct student *delet(struct student *phead);//删除学生信息


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
    printf("\t\t\t\t│---------------------欢迎来到学生成绩管理系统---------------------│\n");
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
    char *p = name1;//记录目录文件及用户名路径
    char name2[PATH_MAX]={0};//该路径用来储存文件用户名
    int med;//记录mkdir返回值
    int all = 0;//记录二次密码输入的次数
    DIR *dir;//记录打开目录的返回值
    struct teacher *st;
    int fd;
    FILE *fp;
    st = (struct teacher *)malloc(sizeof(struct teacher));
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t用户:");
    scanf("%s",st->user); 
    strcpy(name2,st->user);
    if((med = mkdir(st->user,S_IRWXU|S_IRWXO)) == -1)
    {
        system("clear -l");
        printf("\t\t\t\t\t\t该用户名已经被注册!\n");
        printf("\t\t\t\t\t\t请重新注册!\n");
        return (zhuce());
    }
    printf("\t\t\t\t\t\t密码:");
    scanf("%s",st->pass);
    if(strlen(st->pass) > 10)
    {
        printf("\t\t\t\t\t\t密码格式错误请重新输入！\n");
        return (zhuce());
    }
    printf("\n\t\t\t\t\t\t请再次输入密码:");
    scanf("%s",pass);
    while(strcmp(pass,st->pass) != 0)
    {
        system("clear -l");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t密码错误请重新输入！\n");
        printf("\t\t\t\t\t\t若重复三次将重新回到注册页面!\n");
        memset(pass, 0, sizeof(pass));
        printf("\t\t\t\t\t\t请您重新输入密码:");
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
               printf("\t\t\t\t\t\t注册失败，请重新注册！\n");
           }
        else
        {
            if((creat(name, S_IRWXU))==-1)
            {
                printf("\t\t\t\t\t\t失败!\n");
            }
            else{
              
                if((fd = open(name,O_CREAT|O_RDWR,S_IRWXU))!= -1)
                {
                    if((write(fd, pass, strlen(pass)))!= strlen(pass))
                    {
                        printf("\n\t\t\t\t\t\t失败\n");
                        close(fd);
                    }
                    else{
                        if((fp = fopen("users.txt","a+"))!=NULL)
                        {
                            int i =0;
                           if((i = (fprintf(fp, "%s\n", name2))) != (strlen(name2)+1))
                            {
                                printf("注册失败，请重新注册!\n");
                                fclose(fp);
                                return (zhuce());
                            }
                            else{
                                printf("\n\t\t\t\t\t注册成功!\n");
                                fclose(fp);
                                //return (zhuce());
                            }
                        }
                        if(fp == NULL)
                        {
                            printf("注册失败!\n");
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

int save_inf(struct student *phead,char *name)//将每次的信息变动存入文件
{
    struct student *stu;
   // struct student *p = phead->next;
    FILE *fp;
    char *filename = name;
    int a;

    if((fp = fopen(filename,"wt")) == NULL)
    {
        printf("打开文件错误!\n");
    }
   /* else{
        printf("打开文件成功!\n");
    }*/
    for(stu = phead->next;stu != NULL;stu = stu->next)
    {
        printf("进入\n");
       if((a = (fwrite(stu, sizeof(struct student), 1, fp)))!= 1)
        {
            printf("写文件错误\n");
        }
        printf("%d\n",a);

    }
       // fclose(fp);
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
        printf("读文件出错!\n");
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
void user_in()//用户登陆选择操作界面
{
    char yes[4]="yes";
    char no[3]="no";
    int choice = 0;
    int a;
  //  do
   // {
        menu_sign_in();
        printf("\t\t\t\t\t\t\t\t根据要进入的界面输入数字:");
        scanf("%d",&a);
        switch(a)
        {
            case 1:
            {
                menu_sign_in_teacher();
                //增加一个登陆读取函数
                break;
            }
            case 2:
            {
                menu_sign_in_student();
                //增加一个登陆读取用户名和密码的函数
                break;
            }
            case 3:
            {
                //注册函数，仅限于老师注册
                break;
            }
            case 4:
            {
                //用户说明说显示函数
                break;
            }
            default:
            {
                printf("请检查输入的功能数字格式是否符合\n");
                return (user_in());
            }
        }
   // }while(choice);
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
void menu_sign_in_student()
{
    char name[20];
    char pass[11];
    system("clear -l");
    printf("\t\t欢迎学生进入登陆界面!\n");
   // printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t                         账号:");
    scanf("%s",name);
    printf("\n\t\t\t\t                         密码:");
    scanf("%s",pass);
}
void menu_techer()//老师菜单显示函数
{
    //system("echo '\033'[ ;34m\t\t\t\t\t您已登陆成功，正在进入系统，请稍后......\033[0m'|py -ql 10");
    system("clear -l");
   // printf("\t\t\t\t\t教师用户界面登陆成功！\n");
    printf("\n\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t┌───────────────────────────────────────────────────────────────────┐\n");
    printf("\t\t\t\t│-------------------------------------------------------------------│\n");
    printf("\t\t\t\t│--------------------------1、录入学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------2、增加学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------3、查找学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------4、删除学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------5、修改学生信息--------------------------│\n");
    printf("\t\t\t\t│--------------------------6、查看所有学生信息----------------------│\n");
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
    printf("|---------------------------1、录入学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|------------------------根据提示依次输入学生信息--------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    phead = (struct student *)malloc(sizeof(struct student));//创建头节点开辟空间
    phead->next = NULL;
    r = phead;
    do{
        stu = (struct student *)malloc(sizeof(struct student));
        printf("请输入学生姓名:\n");
        scanf("%s",stu->name);
        printf("请输入学生的学号:\n");
        scanf("%s",stu->ID);
        printf("请输入学生性别:\n");
        scanf("%s",stu->sex);
        printf("请输入学生成绩:\n");
        printf("数学:");
        scanf("%s",stu->score[0]);
        printf("\n英语:");
        scanf("%s",stu->score[1]);
        printf("\n语文:");
        scanf("%s",stu->score[2]);
        printf("\n物理:");
        scanf("%s",stu->score[3]);
        printf("\n化学:");
        scanf("%s",stu->score[4]);
        r->next = stu;
        r = stu;
        Count++;
        printf("是否继续，继续请输入yes，不继续请输入no\n");
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
    printf("|---------------------------2、增加学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|------------------------根据提示依次输入学生信息--------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    while(p && p->next!= NULL)
    {
        p = p->next;//找出链表末尾
    }
   // stu = (struct student *)malloc(sizeof(struct student));
    printf("请输入要加入学生的详细信息\n");
    do
    {
        stu = (struct student *)malloc(sizeof(struct student));
        printf("请输入学生姓名:\n");
        scanf("%s",stu->name);
        printf("请输入学生的学号:\n");
        scanf("%s",stu->ID);
        printf("请输入学生性别:\n");
        scanf("%s",stu->sex);
        printf("请输入学生成绩:\n");
        printf("数学:");
        scanf("%s",stu->score[0]);
        printf("\n英语:");
        scanf("%s",stu->score[1]);
        printf("\n语文:");
        scanf("%s",stu->score[2]);
        printf("\n物理:");
        scanf("%s",stu->score[3]);
        printf("\n化学:");
        scanf("%s",stu->score[4]);
        p->next = stu;
        stu->next = NULL;
        p = stu;
        Count++;
        printf("是否继续增加学生信息,继续请输入yes,不继续输入no:\n");
        scanf("%s",choise);
       // printf("%d\n",strcmp(choise,yes));
        if(strcmp(choise,yes) == 0)
        {
            printf("%d",strcmp(choise,yes));
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
    printf("|---------------------------3、查找学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|------------------------根据提示输入学生学号------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    do{
        printf("请输入学生学号查找学生详细信息:\n");
        scanf("%s",id);
        p = phead->next;
        printf("查找\n");
        while(p != NULL)
        {
            if(strcmp(id,p->ID) == 0)
            {
                printf("已经查找到该生信息！\n");
                printf("----姓名----学号----性别----数学----语文----英语----物理----化学----\n");//注意格式的修改
                printf("%8s\t",p->name);
                printf("%8s\t",p->ID);
                printf("%8s\t",p->sex);
                for(int i = 0;i<5;i++)
                {
                    printf("%8s",p->score[i]);
                }
                printf("\n");
            }
            p = p->next;
        }
        printf("是否继续查找学生信息,继续请输入yes,不继续输入no\n");
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
            printf("查找到该学生信息!\n");
            printf("----姓名----学号----性别----数学----语文----英语----物理----化学----\n");//注意格式的修改
            printf("%s\t",p->name);
            printf("%s\t",p->ID);
            printf("%s\t",p->sex);
            for(int i = 0;i<5;i++)
            {
                printf("%8s",p->score[i]);
            }
            printf("\n");
            break;
        }
        p = p->next;
    }
    if(p==NULL)
    {
        printf("未找到与该学号匹配的学生，请核对学号!\n");
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
    printf("|---------------------------4、删除学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|------------------------根据提示输入学生学号------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    do
    {
        printf("请输入被删除学生的学号:\n");
        scanf("%s",id);
        stu = danfind(phead,id);
        while(p != NULL)
        {
            if(strcmp(p->ID,id) == 0)
            {
                pre->next = p->next;
                free(p);
                printf("删除成功!\n");
                Count--;
                break;
            }
            pre = p;
            p = p->next;
        }
        printf("是否继续删除,继续请输入yes,不继续输入no\n");
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
    printf("|---------------------------5、修改学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|------------------------根据提示输入学生学号------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
   /* printf("请输入被修改学生原来录入的学号:\n");
    scanf("%s",id);*/
    do
    {
        printf("请输入被修改学生原来录入的学号:\n");
        scanf("%s",id);
        system("cls");
        new = (struct student *)malloc(sizeof(struct student));
        stu =danfind(phead,id);
        if(stu!=NULL)
        {
            printf("该生信息查找结果如上!\n");
            printf("若查找失败请核对学号,若查找成功请根据以下提示修改信息!\n");
            // printf("")
            printf("|---------------------------1、修改姓名--------------------------|\n");
            printf("|---------------------------2、修改学号--------------------------|\n");
            printf("|---------------------------3、修改性别--------------------------|\n");
            printf("|---------------------------4、修改成绩--------------------------|\n");
            printf("|---------------------------5、显示修改信息----------------------|\n");
            printf("|------------------------根据需要输入功能序号--------------------|\n");
            scanf("%d",&a);
            switch(a)
            {
                case 1:
                {
                    printf("请输入学生姓名:\n");
                    scanf("%s",new->name);
                    strcpy(stu->name,new->name);
                    break;
                }
                case 2:
                {
                    printf("请输入学生学号:\n");
                    scanf("%s",new->ID);
                    strcpy(stu->ID,new->ID);
                    break;
                }
                case 3:
                {
                    printf("请输入学生性别:\n");
                    scanf("%s",new->sex);
                    strcpy(stu->sex,new->sex);
                    break;
                }
                case 4:
                {
                    printf("请输入学生成绩:\n");
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
                    
                    printf("----姓名----学号----性别----数学----语文----英语----物理----化学----\n");//注意格式的修改
                    printf("%-8s",stu->name);
                    printf("%-8s",stu->ID);
                    printf("%-8s",stu->sex);
                    for(int i = 0;i<5;i++)
                    {
                        printf("%-8s",stu->score[i]);
                    }
                        printf("\n");
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
            printf("学号有错误请核对再输入！\n");
            return revise(phead);
        }
        printf("是否继续修改,继续请输入yes,不继续输入no!\n");
        scanf("%s",choise);
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }
        //free(new);

    }while(choice);
    return phead;

}

void chakan(struct student *phead)//遍历学生信息从链表
{
    struct student *p = phead->next;
    printf("|---------------------------6、显示学生信息--------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|--姓名--|---学号---|--性别--|--数学--|--语文--|--英语--|--物理--|--化学-|\n");//注意格式的修改
    while(p != NULL)
    {
        printf("%9s",p->name);
        printf("%10s",p->ID);
        printf("%8s",p->sex);
        for(int i = 0;i<5;i++)
        {
            printf("%9s",p->score[i]);
        }
        printf("\n");
        p = p->next;
    }
}

void teacher(struct student *phead,char *name)//老师登陆后操作
{
    
    int a;
    char choise[5];
    int choice = 0;
    do
    {

        menu_techer();
        scanf("%d",&a);
       // system("clear -l");//linux清屏
        switch(a)
        {
             case 1:
            {
                 phead = creat_inf(phead);
                 save_inf(phead,name);
                 break;
            }
            case 2:
             {
                phead = insert(phead);
                 save_inf(phead,name);
                break;
            }
            case 3:
            {
                phead = find(phead);
                save_inf(phead,name);
                break;
            }
            case 4:
            {
                phead = delet(phead);
                save_inf(phead,name);
                break;
            }
            case 5:
            {
                phead = revise(phead);
                save_inf(phead,name);
                break;
            }
            case 6:
            {
                chakan(phead);
                break;
            }
           /* case 7:
            {
                read_inf
            }*/
        }
        printf("yes or no:\n");
        scanf("%s",choise);
       // system("clear -l");
        if(strcmp(choise,yes) == 0)
        {
            choice = 1;
        }
        if(strcmp(choise,no) == 0)
        {
            choice = 0;
        }
    
    }while(choice);

}
int main()
{
    struct student *phead;
    int a=0;
    user_in();
    //menu_sign_in();
   // menu_sign_in_teacher();
   // menu_sign_in_student;
   // scanf("%d",&a);
   // system("clear -l");
   // menu_techer();
   // teacher(phead,name);
    return 0;
}
