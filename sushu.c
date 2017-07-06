/*************************************************************************
	> File Name: sushu.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月03日 星期一 13时46分56秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int sushu(int n)
{
    int i = 0;
    int flag = 1;//是素数
    for(i = 2; i<n; i++)
    {
       if(n%i == 0)
        {
            flag = 0;//不是素数
            break;
            //return 0;
        }
    }
    if(n == 1)
    {
        flag = 1;
    }
    if(flag == 0)
    {
        return 0;
    }
    if(flag == 1)
    {
        return n;
    }
}

int fac(int n)
{
    int sum = 0;
    int f=0;
    if(n == 1)
    {
       // f = 1;
        return 1;
    }
    if(sushu(n) == n)
    {
        sum = fac(n-1) + n;
        return sum;
    }
    else
    {
        f = fac(n-1);
        return f;
    }
}

int main()
{
    int i ,j ;
    int n;
    int sum = 0;
    printf("请输入n:\n");
    scanf("%d",&n);
    sum = fac(n);
    printf("%d\n",sum);
    
}
