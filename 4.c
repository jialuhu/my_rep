/*************************************************************************
	> File Name: 4.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月14日 星期五 16时53分17秒
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

char usr_name[PATH_MAX];

char *denglu()
{
    char name[PATH_MAX] = {0};
    printf("请输入登陆名称:\n");
    scanf("%s",name);
   // printf("hello\n");
   // printf("name = %s\n",name);
    strcat(name,"/");
    //printf("name = %s\n",name);
    strcpy(usr_name,name);
    //printf("usr_name = %s\n",usr_name);
    strcat(usr_name,"student_usr.txt");
    //printf("usr_name = %s\n",usr_name);
    return usr_name;
}
int juge_file(char *usr_name)//判断是否开启学生查询
{
    int fp;
    int a = 0;
    char *p;
    //strcpy(p,usr_name);
    //strcat(p,"/student_user.txt");
    if((fp = open(usr_name,O_EXCL,S_IRWXU)) == -1)
    {
        close(fp);
        return (a++);
    }
    else
    {
        close(fp);
        return a;
    }
}
int main()
{
    int a;
    char *p;
    p = denglu();
    a = juge_file(p);
    printf("a = %d\n",a);
    if(a == 0)
    {
        printf("已经成功打开学生查找功能\n");
    }
    if(a > 0)
    {
        printf("还未开启查询功能！\n");
        printf("是否开启查询:\n");
        int choice=0;
        scanf("%d",&choice);
        if(choice == 1)
        {
            printf("开启成功！\n");
        }
        if(choice == 0)
        {
            if(unlink(p) < 0)
            {
                printf("cuowu!\n");
            }
            else
            {
                printf("jieshu!\n");
            }
        }
    }
    return 0;
}



