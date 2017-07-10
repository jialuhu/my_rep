/*************************************************************************
	> File Name: Fib.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月10日 星期一 17时09分33秒
 ************************************************************************/

#include<stdio.h>
int f(int n)
{
    int y;
    if(n<=2)
    {
        y = 1;
    }
    if(n>2)
    {
        y = f(n-1)+f(n-2);
    }
    return y;
}
int main()
{
    printf("Fibonacci:%d\n",f(6));
}
