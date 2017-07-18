/*************************************************************************
	> File Name: 9.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月18日 星期二 14时21分49秒
 ************************************************************************/
/*邮箱格式判断，条件一不能在首和尾出现＠和.，条件二只能出现仅且一次出现@，条件三出现＠并且之后至少要有一个不与之相连的.之前也不能有.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int first(char st[],int len)//条件一
{
    int i;
    int flag=1;
    if(st[0]=='.'||st[len-1]=='.')
    {
        flag = 0;
    }
    if(st[0]=='@'||st[len-1]=='@')
    {
        flag = 0;
    }
    return flag;
}
int second(char st[],int len)
{
    int i;
    int j;
    int b=0;
    int flag = 1;
    for(i=1;i<len-1;i++)
    {
        if((st[i]=='@')&& (st[i+1]!='.') && (st[i-1]!='.'))//条件三
        {
            for(j=i+1;j<len;j++)
            {
                if(st[j]=='.')
                {
                    b = 1;
                    break;
                }
            }
            if(b==0)
            {
                flag = 0;
            }
        }
        if(st[i]=='@'&&(st[i+1]=='.'||st[i-1]=='.'))
        {
            flag = 0;
        }
    }
    return flag;
}
int three(char st[],int len)//条件二
{
    int i;
    int flag = 1;
    int count=0;
    for(i=0;i<len;i++)
    {
        if(st[i]=='@')
        {
            count++;
        }
    }
    if(count!=1)
    {
        flag = 0;
    }
    return flag;
}
int main()
{
    char email[100];
    int a1,a2,a3;
    while(scanf("%s",email) != EOF)
    {
        int len = strlen(email);
        email[len] = '\0';
        a1 = first(email,len);
        a2 = second(email,len);
        a3 = three(email,len);
        if(a1&a2&a3)//如果三个条件满足就符合条件，如果有一个不满足，就不符合
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}
