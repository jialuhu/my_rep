/*************************************************************************
	> File Name: myenv2.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月24日 星期一 15时34分37秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<malloc.h>
int main(int argc,char **argv,char **envp)
{
    int i;
    printf("打印参数:\n");
    for(i=0;i<argc;i++)
    {
        printf("a[%d]=%s\n",i,argv[i]);
    }
    printf("打印环境变量:\n");
    for(i=0;envp[i]!=NULL;i++)
    {
        printf("envp[%d]=%s\n",i,envp[i]);
    }
}
