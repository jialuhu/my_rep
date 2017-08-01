/*************************************************************************
	> File Name: pthread_key.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月31日 星期一 16时13分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_key_t key;

void *thread2(void *arg)
{
    int tsd=5;
    printf("thread2 %lu is runing\n",pthread_self());
    //pthread_setspecific(key,(void *)tsd);
    printf("thread2 %ld returns %d \n",pthread_self(),pthread_getspecific(key));
}

void *thread1(void *arg)
{
    int tsd=1;
    pthread_t thid2;
    printf("thread1 %lu is running\n",pthread_self());
    pthread_setspecific(key,(void *)tsd);
    pthread_create(&thid2, NULL, thread2, NULL);
    sleep(3);
    printf("thread1 %lu returns %d\n",pthread_self(),pthread_getspecific(key));
}

int main()
{
    pthread_t thid1;
    printf("main thread begins running\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid1, NULL, thread1, NULL);
    sleep(8);
    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}
