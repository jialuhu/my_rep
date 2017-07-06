/*************************************************************************
	> File Name: xiaoming.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月06日 星期四 17时34分41秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f(int n)
{
    switch(n)
    {
        case 1:
        {
            return 1;
        }
        case 2:
        {
            return 2;
        }
        case 3:
        {
            return 4;
        }
        default:
        {
            return f(n-1)+f(n-2)+f(n-3);
        }
        return 0;
    }
}
int main()
{
    int n;
    printf("请输入要爬几层阶梯:\n");
    scanf("%d",&n);
    printf("小明有%d种方法爬楼梯\n",f(n));
    return 0;
}
