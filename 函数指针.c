/*************************************************************************
	> File Name: 函数指针.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月17日 星期一 16时10分40秒
 ************************************************************************/

#include<stdio.h>
int max(int i ,int j)
{
    return i<j?i:j;
}

int (*funcation(int a))(int,int)//返回值类型为int(*)(int,int),指向函数的指针
{
    printf("a = %d\n",a);
    return max;
}
int main()
{
    int i = 15,j=20;
    int max;
    int (*p)(int,int);
    p = funcation(100);
    max = p(i,j);
    printf("max = %d\n",max);
    return 0;
    
}
