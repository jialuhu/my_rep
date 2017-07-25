/*************************************************************************
	> File Name: wait.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月24日 星期一 17时09分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;

    printf("how to use the wait\n");
    pid = fork();
    printf("进入选择语句\n");
    switch(pid)
    {
        case 0:
        {
            printf("子进程\n");
            msg = "子函数正在运行\n";
            k=5;
            exit_code = 37;
            break;
        }
        case -1:
        {
            perror("process creat falit\n");
            exit(1);
        }
        default:
        {
            printf("父进程\n");
            exit_code = 0;
            break;
        }
    }
    printf("父子进程都会进行这段代码\n");
    if(pid != 0)
    {
        int stat_val;
        pid_t child_pid;
        printf("jinru\n");
        child_pid = wait(&stat_val);
        printf("子进程结束，退出码为:%d\n",child_pid);
        if(WIFEXITED(stat_val))
        {
            printf("正常结束，退出码:%d\n",WEXITSTATUS(stat_val));
        }
        else
        {
            printf("子进程不正常结束\n");
        }
    }
    else
    {
        while(k-->0)
        {
            puts(msg);
            sleep(1);
        }
    }
exit(exit_code);
}
