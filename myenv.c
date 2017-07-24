/*************************************************************************
	> File Name: myenv.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月24日 星期一 15时24分50秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<malloc.h>

extern char **environ;

int main(int argc,char **argv)
{
    int i;
    printf("命令行参数：\n");
    for(i=0;i<argc;i++)
    {
        printf("a[%d]=%s\n",i,argv[i]);
    }
    printf("环境变量的值:\n");
    for(i=0;environ[i]!=NULL;i++)
    {
        printf("%s\n",environ[i]);
    }
    return 0;
}
