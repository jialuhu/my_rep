/*************************************************************************
	> File Name: myshell.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月26日 星期三 16时11分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<wait.h>
#include<time.h>
#include<dirent.h>
#include<fcntl.h>
#include<pwd.h>
#include<netdb.h>
#include<sys/socket.h>

#define  normal 0       //一般形式的命令
#define out_redir 1    //输出重定向>
#define in_redir 2    //输入重定向<
#define have_pipe 3 //命令中有管道
#define add_out 4   //追加输出>>
void input_command(char *buf);//输入命令行存在数组buf中
void print();//shell输出的格式
void explan_command(char *buf,int *arglist_count,char arglist[100][256]);//参数解析
void mysignal(int signal);//信号屏蔽函数
void sacve_command(char *buf);//存储命令函数
void do_command(int arglist_count,char arglist[100][256]);//查找到该命令并且执行
int find_command(char *command);//查找命令所在文件
int save_inf(char *buf);//存储函数
char* get_path();//获取当前目录
int history();//记录历史命令

int com_list(char *para)
{
    printf("do com_list:%s\n", para);
    return 0;
}
    
int com_view(char *para)
{
    printf("do com_view:%s\n", para);
    return 0;
}

int com_rename(char *para)
{
    printf("do com_rename:%s\n", para);
    return 0;
}
int com_stat(char *para)
{
    printf("do com_stat:%s\n", para);
    return 0;
}

int com_pwd(char *para)
{
    printf("do com_pwd:%s\n", para);
    return 0;
}
int com_delete(char *para)
{
    printf("do com_delete:%s\n", para);
    return 0;
}
int com_help(char *para)
{
    printf("do com_help:%s\n", para);
    return 0;
}

int com_cd(char *para)
{
    printf("do com_cd:%s\n", para);
    return 0;
}
int com_quit(char *para)
{
    printf("do com_quit:%s\n", para);
    exit(0);
}


typedef struct {
    char *name;            
    rl_icpfunc_t *func;     
    char *doc;           
} COMMAND;

COMMAND commands[] = {
  { "cd", com_cd, "Change to directory DIR" },
  { "delete", com_delete, "Delete FILE" },
  { "help", com_help, "Display this text" },
  { "?", com_help, "Synonym for `help'" },
  { "list", com_list, "List files in DIR" },
  { "ls", com_list, "Synonym for `list'" },
  { "pwd", com_pwd, "Print the current working directory" },
  { "quit", com_quit, "Quit using Fileman" },
  { "rename", com_rename, "Rename FILE to NEWNAME" },
  { "stat", com_stat, "Print out statistics on FILE" },
  { "view", com_view, "View the contents of FILE" },
  { (char *)NULL, (rl_icpfunc_t *)NULL, (char *)NULL }
};
char* dupstr(char *s)
{
  char *r;
  r = malloc (strlen (s) + 1);
  strcpy(r, s);
  return (r);
}
char* stripwhite (char *string)
{
    register char *s, *t;
    
    for (s = string; whitespace (*s); s++)
        ;
    
    if (*s == 0)
        return (s);

    t = s + strlen (s) - 1;
    while (t > s && whitespace (*t))
        t--;

    *++t = '\0';

    return s;
}
COMMAND *Find_command (char *name)
{
    register int i;
    
    for (i = 0; commands[i].name; i++)
        if (strcmp (name, commands[i].name) == 0)
            return (&commands[i]);

    return ((COMMAND *)NULL);
}
char* command_generator (const char *text, int state)
{
    static int list_index, len;
    char *name;
    if (!state)
    {
         list_index = 0;
        len = strlen (text);
    }
    while (name = commands[list_index].name)
    {
         list_index++;
    
         if (strncmp (name, text, len) == 0)
             return (dupstr(name));
    }
   return ((char *)NULL);
}
char** fileman_completion (const char *text, int start, int end)
{
    char **matches;
    matches = (char **)NULL;
    if (start == 0)
        matches = rl_completion_matches (text, command_generator);
    return (matches);
}

void initialize_readline ()
{
    rl_readline_name = ">";
    rl_attempted_completion_function = fileman_completion;
}
void input (char *buf)
{
    char *line, *s;
    struct passwd *pwd;
    struct hostent *hp;
    char *path;
    char *home;
    char st[256] = {0};
    char host[100] = {0};
    char N_path[2560]={0};//N_path[0]='~';
    char *p;
    char *q;
     home = (char *)malloc(20);
    line = (char *)malloc(256);
     path = (char *)malloc(2560);
    /*获取主机名称和用户名称*/
    if(gethostname(host,sizeof(host))<0)
    {
        perror("gethostname");
    }
    hp = gethostbyname(host);
    pwd = getpwuid(getuid());
    /*获取当前目录显示*/
    home = getenv("HOME");
    home[strlen(home)+1]='\0';
    p = home;
    getcwd(path,256);
    path[strlen(path)]='\0';
    q = path;
    while(*p!='\0')
    {
        p++;//home
        q++;//path
    }
    strcpy(N_path,q);
    N_path[strlen(N_path)+1]='\0';
    sprintf(st,"\033[;36m %s@%s \033[0m:\033[;34m ~%s \033[0m",pwd->pw_name,hp->h_name,N_path);
    initialize_readline();
    line = readline (st);
    strcpy(buf,line);
    if (!line)
        return;
    s = stripwhite (line);
    strcpy(buf,s);
    if (*s)
    {
        add_history(s);
    }
    free(line);
}
int main()
{
    char *buf;
    char *line;
    char **arg=NULL;
    int arglist_count=0;
    char arglist[100][256];
    buf = (char *)malloc(256);
   if(buf == NULL)
    {
        perror("malloc failed");
        exit(-1);
    }
    signal(SIGINT,mysignal);//屏蔽信号
    while(1)
    {
        memset(buf, 0, 256);//数组初始化，动态开辟的
        input(buf);
        if((strcmp(buf,"logout")==0)||(strcmp(buf,"exit"))==0)
        {
            exit(0);
        }
       // save_inf(buf);
        if((strcmp(buf,"exit\n")==0)||(strcmp(buf,"logout\n")==0))
        {
            break;
        }
        for(int i =0;i<100;i++)
        {
            arglist[i][0]=0;//初始化
        }
        arglist_count=0;
        int b=0;
        explan_command(buf,&arglist_count,arglist);//分解出命令,一个模块站一个一维数组
        do_command(arglist_count,arglist);//查找到该命令并且执行
    }
    if(buf!=NULL)
    {
        free(buf);
        exit(0);
    }
    return 0;
}
void mysignal(int signal)
{
}
void print()//shell输出的格式
{
    struct passwd *pwd;
    struct hostent *hp;
    char host[100]={0};
    if(gethostname(host,sizeof(host))<0)
    {
        perror("gethostname");
    }
    hp = gethostbyname(host);
    pwd = getpwuid(getuid());
    printf("\033[;34m %s@%s \033[0m",pwd->pw_name,hp->h_name);
    printf(">>: ");
}

int save_inf(char *buf)//存储历史命令，为history函数做准备
{
    int fd;
    char temp[256];
    char *file="history.txt";
    char *p = buf;
    char *a="\n";
    int i = 0;
    char *q = buf;
    while(*p != '\0')
    {
        if(*q==' ')
        {
            q++;
        }
        if(*q != ' ')
        {
            p = q;
            if(*p !='\0')
            {
                if(*p == ' ')
                {
                    temp[i] =' ';
                }
                temp[i] = *p;
                i++;
            }
            p++;
            q++;
        }
        
    }
    temp[i]='\0';
    if((fd = open(file,O_CREAT|O_RDWR|O_APPEND,0666))==-1)
    {
        perror("open");
    }
    else
    {
        write(fd,buf,strlen(buf));
        write(fd,a,strlen(a));
    }
    close(fd);
    return 0;
}
void explan_command(char *buf,int *arglist_count,char arglist[100][256])
{
    int len=0;
    int lenth = strlen(buf);
    char *p,*q;
    p = buf;
    q = buf;
    for(int i=0;i<lenth;i++)
    {

        if(q[0]==' ')
        {
            q++;
            continue;
        }
        if(q[0]=='\0')
        {
            break;
        }
        
        else
        {
            p = q;
            len = 0;
            while((p[0]!=' ')&&(p[0]!='\0'))
            {
                len++;
                p++;
            }
            strncpy(arglist[*arglist_count], q, len+1);//包括空格和\n都要读入
            arglist[*arglist_count][len]='\0';
            printf("arglist[%d]=%s\n",*arglist_count,arglist[*arglist_count]);
            *arglist_count = *arglist_count+1;
            q = p;
        }
    
    }
    printf("arglist_count=%d\n",*arglist_count);
}

void do_command(int arglist_count, char arglist[100][256])
{
    printf("\n");
    char *arg[arglist_count+1];//指针数组
    int i=0;
    int flag = 0;//标记是否合法字符
    int back=0;//后台运行符标记
    int refind=0;//重定向标记
    char *filename;
    int fd;
    char *anext[arglist_count+1];//存放管道命令的后面另一个命令
    pid_t pid;
    int status;
    for(i=0;i<arglist_count;i++)
    {
        arg[i] = (char *)arglist[i];
        printf("arg[i]=%s\n",arg[i]);
    }
    if(strcmp(arglist[0],"ls")==0)//使有ls命令的带上颜色
    {
        if(strcmp(arglist[arglist_count-1],"&")==0)
        {
            strcpy(arglist[arglist_count-1],"--color");
            arg[arglist_count-1]=(char *)arglist[arglist_count-1];
            back=1;
        }
        else{
        strcpy(arglist[arglist_count],"--color");
        arg[arglist_count]=(char *)arglist[arglist_count];
            arglist_count++;
        }
    }
    if((strcmp(arg[0],"history")==0)&&(arglist_count==1))
    {
        arg[0]="cat";
       arg[1]="-n";
        arg[2]="history.txt";
        arg[3]=NULL;
        arglist_count=3;
    }
    arg[arglist_count]=NULL;//指针数组保证最后一个指针为NULL
    if(arg[0]!=NULL)//当第一个命令不是\n的时候进行判断
    {
        if(strcmp(arg[0],"cd")==0)//判断是否是cd命令
        {
            if(arglist_count>2){printf("wrong command");return;}
            if(arglist_count<=2)
            {
                if((arg[1]==NULL)||(strcmp(arg[1],"~")==0))
                {
                    if(chdir("/home/jialu/")==-1)
                    {
                        perror("chdir is failed\n");
                    }
                    else{//printf("/home/jialu/: ");
                         return;}
                }
                if((arg[2]==NULL)&&(arg[1]!=NULL))
                {
                    if(chdir(arg[1])==-1)
                    {
                        perror("chdir is failed");
                    }
                    else{//printf("%s :",arg[1]);
                         return;}
                }
            }
        }
    }
    for(int j=0;j<arglist_count;j++)//查看是否有后台运行符号
    {
        if(strncmp(arg[j],"&",1)==0)
        {
            if(j==arglist_count-1)
            {
                back = 1;
               // printf("back:%d\n",back);
                arg[arglist_count-1]=NULL;
                break;
            }
            else{printf("wrong4 command\n");return;}
        }
    }
   // if(back!= 1)
    //{
        for(i=0;arg[i]!=NULL;i++)//判断是是哪种类型的命令，并且是否合法
        {
            if(strcmp(arg[i],"<")==0)//判断是否是重定向输入
            {
                flag++;
                refind = in_redir;
                if(arg[i+1]==NULL||i==0)
                {
                    flag++;
                }
            }
            if(strcmp(arg[i],">")==0)//判断是否是定向输出
            {
                flag++;
                refind = out_redir;
                if(i==0||arg[i+1]==NULL)
                {
                    flag++;
                }
            }
            if(strcmp(arg[i],"|")==0)//判断是否是管道命令
            {
                flag++;
                refind = have_pipe;
                if(arg[i+1]==NULL||i==0)
                {
                    flag++;
                }
            }
            if(strcmp(arg[i],">>")==0)//判断是否是追加输出
            {
                flag++;
                refind = add_out;
                if(i==0||arg[i+1]==NULL)
                {
                    flag++;
                }
            }
      //  }
    }

    if(flag>1)//flag>1命令格式错误
    {
        printf("wrong command\n");
        return;
    }
   /* for(i=0;arg[i]!=NULL;i++)//解析命令
    {
        if(strcmp(arg[i],"<") == 0)
        {
            filename = arg[i+1];
            arg[i] = NULL;
            break;
        }
        if(strcmp(arg[i],">")==0)
        {
            filename = arg[i+1];
            arg[i] = NULL;
            break;
        }
        if(strcmp(arg[i],"|")==0)
        {
            arg[i]=NULL;
            int j = i+1;
            int t=0;
            for(j=i+1;arg[j]!=NULL;j++)
            {
                anext[t] = arg[j];
                t++;
            }
            anext[t] = NULL;
            break;
        }
        if(strcmp(arg[i],">>")==0)
        {
            filename = arg[i+1];
            arg[i]=NULL;
            break;

        }
    }*/
    if(refind == in_redir)//如果该命令是重定向输入
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"<")==0)
            {
                filename = arg[i+1];
                arg[i]=NULL;
            }
        }
    }
    if(refind == out_redir)//如果该命令是重定向输入
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],">")==0)
            {
                filename = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if(refind == have_pipe)//如果该命令是管道命令
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"|")==0)
            {
                arg[i]=NULL;
                int j = i+1;
                int t=0;
                for(j=i+1;arg[j]!=NULL;j++)
                {
                    anext[t] = arg[j];
                    t++;
                }
                anext[t] = NULL;
                break;
            }
        }
    }
   if((pid = fork())<0)
   {
       printf("fork is errno");
       return;
   }
  // if(pid==0)
   //{
        switch(refind)
        {
            case 0://为普通命令格式
            {
               if(pid==0)
                {
                    if(!(find_command(arg[0])))
                    {
                        printf("%s command is not find\n",arg[0]);
                        exit(0);
                    }
                execvp(arg[0],arg);
                exit(0);
                }
            break;
            }
            case 1://命令为重定向输出>
            {
                if(pid==0)
                {
                    if((!find_command(arg[0])))
                    {
                        printf("%s command is not find\n",arg[0]);
                        exit(0);
                    }
                    fd = open(filename,O_CREAT|O_RDWR|O_TRUNC,0644);
                    dup2(fd,1);
                    execvp(arg[0],arg);
                    exit(0);
                }
                break;
            }
 	        case 2://命令为重定向输入<
            {
                if(pid==0)
                {
                   if(!find_command(arg[0]))
                    {
                        printf("%s :command is not fond\n",arg[0]);
                        exit(0);
                    }
                    fd = open(filename, O_RDONLY);
                    dup2(fd,0);
                    execvp(arg[0],arg);
                    exit(0);
                }
                break;
            }
            case 3://输出命令中含有管道
            {
                 if(pid==0)
                  {
                    int pid2;
                    int status2;
                    int fd2;
                    if((pid2 = fork()) < 0)
                    {
                        printf("fork2 errno\n");
                        return;
                    }
                    else if(pid2 == 0)
                    {
                        if(!find_command(arg[0]))
                        {
                            printf("%s :command is not fond\n",arg[0]);
                            exit(0);
                        }
                        fd2 = open("youdontknowfile.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
                        dup2(fd2,1);//标准输出到fd2
                        execvp(arg[0],arg);//在子进程2中执行前半部分的命令
                        exit(0);
                    }
                    if(waitpid(pid2,&status2,0) == -1)//等待子进程2结束，返回子进程1
                    {
                        printf("wait for child2 process errno\n");
                    }
                    if(!find_command(anext[0]))//由子进程1来执行后半部分的命令
                    {
                        printf("%s :command not fond \n",anext[0]);
                        exit(0);
                    }
                    fd2 = open("youdontknowfile.txt",O_RDONLY);
                    dup2(fd2,0);//从fd2中输入前半部分执行结束的结果
                    execvp(anext[0],anext);//在子进程1中执行后半部分命令
                    if(remove("youdontknowfile.txt"))
                    {
                        printf("remove errno\n");
                    }
                    exit(0);
                }
                    break;
            }
            case 4://命令为重定向追加>>
            {
                if(pid ==0 )
                {
                   if(!find_command(arg[0]))
                    {
                        printf("%s :command is not fond\n",arg[0]);
                        exit(0);
                    }
                    fd = open(filename, O_APPEND|O_WRONLY,0644);
                    dup2(fd,1);
                    execvp(arg[0],arg);
                    exit(0);
                }
                break;
            }
            default:break;
     //   }
   }
 if(back==1)
{
    printf("[process is %d]\n",pid);
    return;
}
   if(waitpid(pid,&status,0) == -1)//等待子进程1结束
   {
       printf("wati for child errno");
   }
   printf("\n");
}
int find_command(char *command)//查找命令所在的文件，并且返回1和0来判断是否执行
{
    DIR *dir;
    int i=0;
    struct dirent *ptr;
    char *path[]={"./","/bin","/usr/bin",NULL};
    int len = strlen(command);
    if(command[0]=='.'&&command[1]=='/')
    {
        command = command+2;
    }
    while(path[i]!=NULL)
    {
        if((dir=opendir(path[i])) == NULL)
        {
            printf("can not open the /bin");
        }
        else
        {
            while((ptr=readdir(dir))!=NULL)
            {
                if(strcmp(command,ptr->d_name)==0)
                {
                    closedir(dir);
                    return 1;
                }
            }
        }
            closedir(dir);
            i++;
    }
    return 0;
}

