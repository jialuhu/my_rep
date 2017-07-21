/*************************************************************************
	> File Name: renwu25.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月21日 星期五 08时46分14秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int n;
    char st[100]={0};
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
    {
        scanf("%s",st);
        int len = strlen(st);
        st[len] = '\0';
        char *p = st;
        char *q = st+len-1;
        int flag = 1;
        while(q>=p)
        {
            if(*p == *q)
            {
                flag = 1;
            }
            if(*p!=*q)
            {
                flag = 0;
                break;
            }
            ++p;
            --q;
        }
        if(flag == 0)
        {
            printf("no\n");
        }
        if(flag == 1)
        {
            printf("yes\n");
        }
    }
}
