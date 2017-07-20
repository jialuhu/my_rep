/*************************************************************************
	> File Name: renwu22.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月20日 星期四 09时33分50秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void r(char *p)
{
    if(*p==' ')
    {
        return;
    }
    r(p+1);
    printf("%c",*p);
}
void R(char *p)
{
    if(*p=='\0')
    {
        return;
    }
    R(p+1);
    printf("%c",*p);
}
int main()
{
    int n;
    char article[1000]={0};
    scanf("%d",&n);
    getchar();
    for(int j=0;j<n;j++)
    {
        int len;
        int i=0;
        gets(article);
        char *q = article;
        char *ch = article;
        len = strlen(article);
        article[len]='\0';
        while(i<=len)
        {
            i++;
            if(*ch == ' ')
            {
                r(q);
                q = ch+1;
                printf(" ");
            }
            if(*ch == '\0')
            {
               // printf("%s",q);
                R(q); 
            }
            ch++;
        }
        printf("\n");

    }
}
