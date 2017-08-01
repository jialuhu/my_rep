/*************************************************************************
	> File Name: conditon.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 10时19分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread1(void *arg)
{
    pthread_cleanup_push(pthread_mutex_unlock,&mutex);
    
    while(1)
    {
        printf("thread1 is running\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("thread1 applied the conditon\n");
        pthread_mutex_unlock(&mutex);
        sleep(20);
    }
    pthread_cleanup_pop(0);
}

void *thread2(void *arg)
{
    while(1)
    {
        printf("thread2 is running\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("thread2 applied the conditon\n");
        pthread_mutex_unlock(&mutex);
        sleep(10);
    }
}

int main()
{
    pthread_t tid1,tid2;

    printf("conditon variable study\n");
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1, NULL, (void *)thread1, NULL);
    pthread_create(&tid2, NULL, (void *)thread2, NULL);

    do{
        pthread_cond_signal(&cond);
        //printf("执行信号激活\n");

    }while(1);

    sleep(50);

    pthread_exit(0);
}

