/*************************************************************************
	> File Name: ceshi2.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月21日 星期五 16时08分47秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
void R(char *path)
{
    char *dir_nm;
    printf("%s:\n",path);
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
    int i=0,j=0;
    char *p;
    int count = 0;
    /*第一次打开目录，读取当前目录下的文件，并且列出*/
    if((dir = opendir(path)) == NULL)
    {
        printf("打开目录错误\n");
        exit(0);
    }
    
    while((ptr = readdir(dir)) != NULL)
    {
        char c[256]={0};
        strcpy(c,ptr->d_name);
        if(c[0]!='.')//仅限于-R
        {
            printf("%s\t",ptr->d_name);
        }
    }
    printf("\n\n");
    closedir(dir);
    /*第二次打开目录，边读边判断并且边递归*/
    if((dir = opendir(path)) == NULL)
    {
        printf("打开目录错误\n");
        exit(0);
    }
    while((ptr = readdir(dir)) != NULL)
    {
        char a[256]={0};
        strcpy(a,ptr->d_name);
        if(a[0]!='.')
        {
            char b[256]={0};
            strcpy(b,path);
            strcat(b,"/");
            strcat(b,ptr->d_name);//使b中存入绝对路径
            b[strlen(path)+strlen(ptr->d_name)+1]='\0';
            if(lstat(b,&buf) ==-1)//获取该文件属性
            {
                printf("获取文件属性错误\n");
            }
            else{
                    if(S_ISDIR(buf.st_mode))//判断该文件是否是目录
                    {
                        if((strcmp(ptr->d_name,".")!=0)&&(strcmp(ptr->d_name,"..")!=0))//递归排查当前目录和父目录，只往下走
                        {
                        dir_nm = (char *)malloc(strlen(b)+1);//定义动态数组
                        strcpy(dir_nm,b);
                        R(dir_nm);//将动态数组地址传入函数，进行递归操作
                        free(dir_nm);//free动态数组
                        }
                    }
                }
        }
    }
    closedir(dir);
}
int main()
{
    char *p="../../jialu";
    R(p);
}
