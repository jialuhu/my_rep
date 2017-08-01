/*************************************************************************
	> File Name: pthread_once.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月31日 星期一 10时46分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//#include<iostream>
#include<pthread.h>

pthread_once_t one = 0;

void run(void)
{
    printf("该函数正在运行，线程号为:%lu\n",pthread_self());
}

void *thread1(void*arg)
{
    pthread_t thid=pthread_self();
    printf("1Current thread's ID is:%lu\n",thid);
    printf("1one=%d\n",one);
    pthread_once(&one,run);
    printf("1one=%d\n",one);
    printf("1 end\n");
}
void *thread2(void*arg)
{
    pthread_t thid=pthread_self();
    printf("2Current thread is ID:%lu\n",thid);
    printf("2one=%d\n",one);
    pthread_once(&one,run);
    printf("2one=%d\n",one);
    printf("2 end\n");

}
int main()
{
    pthread_t thid1,thid2;
    pthread_create(&thid2,NULL,thread2,NULL);
    pthread_create(&thid1,NULL,thread1,NULL);
    sleep(4);
    exit(0);
}
