/*************************************************************************
	> File Name: ls.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月02日 星期日 00时13分39秒
 ************************************************************************/
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<time.h>

#define LS_NONE 0
#define LS_A 1
#define LS_L 2
#define LS_R 30
#define LS_r 20

void my_err(const char *err_string,int line);//打印错误函数
void R(char *path,int flag);//-R函数
void output_l(struct stat buf,char *filename);//文件属性打印函数
char *Filename(char *pathname);//目录文件名解析函数
void open_dir(char *pathname,int flag);//打开目录来遍历该目录下的文件

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line: %d",line);//打印出错在几行
    perror(err_string);//将上一个函数错误输出到标准输出设备上stderr，参数中字符串首先输出
    exit(1);
}
void output_l(struct stat buf,char *filename)//打印文件属性函数
{
    char time[32];
    struct passwd *psd;
    struct group *grp;
    char st[10] = {0};
    char *p = filename;
    //获取文件类型
    if(S_ISLNK(buf.st_mode)) st[0]= 'l' ;
    if(S_ISREG(buf.st_mode)) st[0]= '-' ;
    if(S_ISDIR(buf.st_mode)) st[0]= 'd' ;
    if(S_ISCHR(buf.st_mode)) st[0] =  'c' ;
    if(S_ISBLK(buf.st_mode)) st[0] =  'b' ;
    if(S_ISFIFO(buf.st_mode))st[0] =  'f';
    if(S_ISSOCK(buf.st_mode))st[0] =  's';

    //获取文件所有者权限
    if((buf.st_mode)&(S_IRUSR)) st[1]='r'; else st[1]='-';
        // (buf.st_mode)&(S_IRUSR)?(st[1]='r'):(st[1]='-');
         (buf.st_mode)&(S_IWUSR)?(st[2]='w'):(st[2]='-');
         (buf.st_mode)&(S_IXUSR)?(st[3]='x'):(st[3]='-');

    //获取文件用户组的权限     
    (buf.st_mode)&(S_IRGRP)?(st[4]='r'):(st[4]='-');
    (buf.st_mode)&(S_IWGRP)?(st[5]='w'):(st[5]='-');
    (buf.st_mode)&(S_IXGRP)?(st[6]='x'):(st[6]='-');

    //获取文件其他用户的权限
    (buf.st_mode)&(S_IROTH)?(st[7]='r'):(st[7]='-');
    (buf.st_mode)&(S_IWOTH)?(st[8]='w'):(st[8]='-');
    (buf.st_mode)&(S_IXOTH)?(st[9]='x'):(st[9]='-');
    //printf(" ");
    
    for(int i=0;i < 10;i++)
    {
        printf("%c",st[i]);
    }
    printf("   ");
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%-4d",(int)buf.st_nlink);//打印文件的连接数
    printf("%-8s",psd->pw_name);//打印文件所有者的名称
    printf("%-8s",grp->gr_name);//打印用户组的名称
    printf("%6d",(int)buf.st_size);//打印文件的大小
    strcpy(time,ctime(&buf.st_mtime));
    time[strlen(time) - 1]='\0';
    printf(" %s",time);//打印时间
    printf("   %s\n",p);
}

char *Filename(char *pathname)//目录到文件名称的解析函数解析出文件名称
{
    int i ,j ,k ,count=0;  //记录‘/’出现次数
    char *name=(char *)malloc(sizeof(char)*(NAME_MAX+1));
    char *str = name;
    for(i=0;i<strlen(pathname);i++)
    {
        if(pathname[i]=='/')
        {
            count = i;
        }
    }
    k = 0;
    for(j=0;j<strlen(pathname);j++)
    {
        if(count==0)
        {
            strcpy(name,pathname);
        }
        if((j == count)&&count!=0)
        {
            while((j+1) < strlen(pathname))
            {
                name[k++] = pathname[j+1];//从最后一个‘/’来解析后面的文件名
                j = j+1;
            }
            name[k]='\0';//文件的名称
        }
    }
    return str;
}

void R(char *path,int flag)//参数-R
{
    char *dir_nm;
    printf("%s:\n",path);
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
    int i=0,j=0;
    char *p;
    int count = 0;
    int A=0,R1=0,L=0,three=0;
    switch(flag)
    {
        case LS_R:
        {
            R1=1;
            break;
        }
        case LS_A+LS_R:
        {
            A=1;
            break;
        }
        case LS_L+LS_R:
        {
            L=1;
            break;
        }
        case LS_L+LS_R+LS_A:
        {
            three=1;
            break;
        }
    }
        if(L){open_dir(path,LS_L);printf("\n");}
        if(three){open_dir(path,LS_L+LS_A);printf("\n");}
   // if(L==0&&three==0)
   // {
        if((dir = opendir(path)) == NULL)
        {
            my_err("opendir:",__LINE__);
        }
    
        while((ptr = readdir(dir)) != NULL)
        {
            char c[256]={0};
            strcpy(c,ptr->d_name);
            if(L==1||three==1){break;}
            if(!A)
            {
                if(c[0]!='.')
                {
                    printf("%s\t",ptr->d_name);
                }
            }
            if(A)
            {
                printf("%s\t",ptr->d_name);
            }
        }
        printf("\n\n\n");
        closedir(dir);
        if((dir = opendir(path)) == NULL)
        {
            my_err("opendir:",__LINE__);
        }
        while((ptr = readdir(dir)) != NULL)
        {
            char a[256]={0};
            strcpy(a,ptr->d_name);
            if(!A)
            {
                char b[256]={0};
                if(a[0]!='.')
                {
                    strcpy(b,path);
                    strcat(b,"/");
                    strcat(b,ptr->d_name);
                    b[strlen(path)+strlen(ptr->d_name)+1]='\0';
                    if(stat(b,&buf) ==-1)
                    {
                        printf("\n\n\nb=%s\n\n\n",b);
                        my_err("lstat",__LINE__);
                    }
                    else{
                            if(S_ISDIR(buf.st_mode))
                            {
                                if((strcmp(ptr->d_name,".")!=0)&&(strcmp(ptr->d_name,"..")!=0))
                                {

                                    dir_nm = (char *)malloc(strlen(b)+1);
                                    strcpy(dir_nm,b);
                                    R(dir_nm,flag);
                                free(dir_nm);
                                }
                            }
                        }
                }
            }
            if(A)
            {
                char b[256]={0};
                strcpy(b,path);
                strcat(b,"/");
                strcat(b,ptr->d_name);
                b[strlen(path)+strlen(ptr->d_name)+1]='\0';
                if(lstat(b,&buf) ==-1)
                {
                    my_err("lstat",__LINE__);
                }
                else{
                        if(S_ISDIR(buf.st_mode))
                        {
                            if((strcmp(ptr->d_name,".")!=0)&&(strcmp(ptr->d_name,"..")!=0))
                            {
                            dir_nm = (char *)malloc(strlen(b)+1);
                            strcpy(dir_nm,b);
                            R(dir_nm,flag);
                            free(dir_nm);
                            }
                        }
                    }
            }
        }
    closedir(dir);

   // }
}
void open_dir(char *pathname,int flag)//打开目录来遍历该目录下的文件
{
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    int i =0;
    char finame[256][PATH_MAX+1];
    char temp[PATH_MAX+1];
    /*获取目录下的文件名*/
    if((dir = opendir(pathname)) == NULL)
    {
        my_err("open",__LINE__);
    }
    /*遍历这个目录*/
    while((ptr = readdir(dir)) !=NULL)
    {
        strcpy(finame[i],ptr->d_name);
        count++;
        i++;
    }
    /*将文件排序*/
    for(i=0;i<count-1;i++)
    {
        for(int j=i+1;j<count;j++)
        {
            if(strcmp(finame[i],finame[j])>0)
            {
                strcpy(temp,finame[i]);
                temp[strlen(finame[i])]='\0';
                strcpy(finame[i],finame[j]);
                finame[i][strlen(finame[j])]='\0';
                strcpy(finame[j],temp);
                finame[j][strlen(temp)]='\0';
            }
        }
    }
    closedir(dir);
   switch(flag)//根据引入标志来判断参数类型
    {
        case LS_NONE://ls 
        {
            for(i=0;i<count;i++)
            {
                if(finame[i][0] != '.')
                {
                    printf("%s\t",finame[i]);
                }
            }
            printf("\n");
            break;
        }
        case LS_A://ls -a
        {
            printf("ls a\n");
            for(i=0;i<count;i++)
            {
                printf("%s\t",finame[i]);
            }
            printf("\n");
            break;
            
        }
        case LS_L+LS_R:
        {
            R(pathname,flag);
            break;
        }
        case LS_L+LS_R+LS_A:
        {
            printf("jinru\n");
            R(pathname,flag);
            break;
        }
        case LS_L://-l
        {
            struct stat buf[256];
            for(i=0;i<count;i++)
            {
                char name[PATH_MAX]={0};
                strcpy(name,pathname);
                strcat(name,"/");
                strcat(name,finame[i]);
                if((stat(name,&buf[i])) == -1)//传入文件名获取文件属性
                {
                    my_err("stat",__LINE__);
                }
                if(finame[i][0] !='.')
                {
                    output_l(buf[i],finame[i]);
                }
            }
            break;
        }
        case LS_R:
        {
            R(pathname,flag);
            break;
        }
        case LS_R+LS_A:
        {
           R(pathname,flag);
            break;
        }
        case LS_r:
        {
            printf("r\n");
            break;
        }
        case LS_A + LS_L://-a -l
        {
            for(i=0;i<count;i++)
            {
                char name[PATH_MAX]={0};
                strcpy(name,pathname);
                strcat(name,"/");
                strcat(name,finame[i]);
                struct stat buf;
                if((stat(name,&buf)) == -1)
                {
                    my_err("stat",__LINE__);
                }
                output_l(buf,finame[i]);
            }
            break;
        }
        default:
            {
                printf("no flag\n");
            }
        
    }
}
int main(int argc,char **argv)
{
    int n = argc;
    int k = 0;//记录-的次数
    char param[3];//记录-a ,-l, -al
    char Param[PATH_MAX]={0};
    int i =0;
    int j = 0;
    int count=0;
    char *p;
    int flag = LS_NONE;//记录参数类型 -a -l -al 还是无
    char pathname[PATH_MAX+1]={0};//文件的路径
    int a;
    /*记录-的次数，看出现几次-，为判断有无文件名做准备*/
    for(i=1;i<n;i++)//如果不加文件，参数个数等于-的个数加上1
    {
        if(argv[i][0]=='-')
        {
            k = k+1;//加上-和ls一共有的参数个数
            continue;
        }
    }
    int c=0;
    for(i=1;i<n;i++)
    {
        if(argv[i][0]=='-')
        {
            int len = strlen(argv[i]);
            for(int b=1;b<len;b++,c++)
            {
                Param[c] = argv[i][b];
            
            }
        }
    }
    int L=0,R1=0,A=0,r=0;
    for(i=0;i<c;i++)
    {
        if(Param[i]=='a'){
            flag = LS_A+flag;A=1;
        }
        if(Param[i]=='l'){
            flag = LS_L+flag;L=1;
        }
        if(Param[i]=='R'){
            flag = LS_R+flag;R1=1;
        }
        if(Param[i]=='r'){
            flag = LS_r+flag;r=1;
        }
    }
    if((n-1) == k)//无文件名
    {
        /*无文件名将把当前目录传入函数中*/
        strcpy(pathname,".");
       // open_dir(pathname,flag);
        if(R1)
        {
            R(pathname,flag);
        }
        else{
            open_dir(pathname,flag); 
        }
    }
    else//printf("有文件名\n");
    {
        struct stat buf;
        strcpy(pathname,argv[n-1]);
        if((stat(pathname,&buf)) == -1)//获取目录路径属性
        {
            my_err("stat",__LINE__);
        }
        if(S_ISDIR(buf.st_mode))//该名称是一个目录
        {
            if(pathname[strlen(pathname)-1]!='/')
            {
                pathname[strlen(pathname)] = '/';
                pathname[strlen(pathname)+1] ='\0';
            }
            else
            {
                pathname[strlen(pathname)+1] ='\0';
            }
            open_dir(pathname,flag);
        }
        else//该名称是文件
        {
            char *p = Filename(pathname);//解析出文件名称
            /*判断出参数情况*/
            if(L)//-l
            {
                output_l(buf,pathname);
            }
            if(!L)//ls
            {
                printf("%s\n",pathname);
            }

        }
    }
}


