/*************************************************************************
	> File Name: 又见GCD.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月25日 星期二 07时44分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<iostream>  
//using namespace std;  

int gcd(int a,int b)  
{
    return b==0? a:gcd(b,a%b);
}  
int main()  
{  
    int t,a,b,c;  
    while(scanf("%d",&t)!=EOF)  
    {  
        while(t--)  
        {  
            scanf("%d%d",&a,&b);  
            c=2*b;  
            while(gcd(a,c)!=b)  
             c+=b;  
             printf("%d\n",c);  
            }  
    }  
    return 0;  
}  
