/*************************************************************************
	> File Name: Manage1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月25日 星期四 17时30分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 20
struct student
{
    char ID[6];
    char name[20];
    int score[4];
};
int inCount;
int menu()
{
    printf("|----------------------------------------------------|\n");
    printf("|                   学生成绩管理系统                 |\n");
    printf("|----------------------------------------------------|\n");
    printf("|                   1、录入学生信息                  |\n");
    printf("|                   2、增加学生信息                  |\n");
    printf("|                   3、查找学生信息                  |\n");
    printf("|                   4、修改学生信息                  |\n");
    printf("|                   5、删除学生信息                  |\n");
    printf("|                   6、查看学生信息                  |\n");
    printf("|----------------------------------------------------|\n");
    printf("|            注：根据以上提示输入数字进入功能        |\n");
    printf("|----------------------------------------------------|\n");
    return 0;
}
int enter(struct student st[],int n)
{
    
    int i ,j;
    printf("|----------------1、录入学生信息---------------------|\n");
    printf("|----------------------------------------------------|\n");
    printf("|学号      姓名      数学      语文      英语    物理|\n");
    printf("|----------------------------------------------------|\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",st[i].ID);
        scanf("%s",st[i].name);
        for(j=0;j<n;j++)
        {
            scanf("%d",&st[i].score[j]);
        }
    }
    iCount = i;
    return 0;
}

int insert(struct student st[])
{
    int i,j;
    int n;
    printf("|----------------2、增加学生信息---------------------|\n");
    printf("|          注意：请输入要增加几个学生的信息：         |\n");
    scanf("%d",&n);
    printf("|---------------------------------------------------|\n");
    printf("|学号      姓名      数学      语文      英语    物理|\n");
    printf("|---------------------------------------------------|\n");
    for(i = iCount;i<iCount+n;i++)
    {
        scanf("%s",st[i].ID);
        scanf("%s",st[i].name);
        for(j = 0;j<4;j++)
        {
            scanf("%d",&st[i].score[j]);
        }
    }
    iCount = i;
    return 0;

}
int find(struct student st[])
{
    char id[6];
    int i,j;
    printf("|----------------3、查找学生信息---------------------|\n");
    printf("|          注意：请输入要查找学生的ID：              |\n");
    printf("-----------------------------------------------------|\n");
    gets(id);
    for(i =0;i<iCount;i++)
    {
        if(id==st[i].ID)
        {
            printf("%s\t",st[i].ID);
            printf("%s\t",st[i].name);
            for(j=0;j<4;j++)
            {
                printf("%d\t",st[i].score[j]);
            }
        }
    }
    return 0;
}
int revise(struct student st[])
{
    int i ,j;
    struct student t;
    char id[6];
    printf("|----------------4、修改学生信息---------------------|\n");
    printf("|          注意：请输入要修改学生的学号：            |\n");
    printf("|----------------------------------------------------|\n");
    gets(id);
    for(i=0;i<iCount;i++)
    {
        if(id==st[i].ID)
        {
            printf("已经找到该学生的信息，请完整输入该学生的新信息\n");
            printf("学号：\n");
            scanf("%s",t.ID);
            printf("姓名：\n");
            scanf("%s",t.name);
            printf("数学\t语文\t英语\t物理\n");
            for(j=0;j<4;j++)
            {
                scanf("%d",&t.score[j]);
            }
            strcpy(st[i].ID,t.ID);
            strcpy(st[i].name,t.name);
            for(j=0;j<4;j++)
            {
                st[i].score[j] = t.score[j];
            }
            printf("该生信息修改为：\n");
            printf("%s\t",st[i].ID);
            printf("%s\t",st[i].name);
            for(j=0;j<4;j++)
            {
                printf("%d\t",st[i].score[j]);
            }
            break;
        }
    }
    return 0;
}

int delet(struct student st[])
{
    int i ,j;
    char id[6];
    char t;
    printf("|----------------5、删除学生信息--------------------|\n");
    printf("|          注意：请输入要删除的学生的学号：         |\n");
    printf("|---------------------------------------------------|\n");
    gets(id);
    for(i=0;i<iCount;i++)
    {
        if(st[i].ID==id)
        {
            printf("查到该学生信息：\n");
            printf("是否删除（Y,N）：\n");
            scanf("%c",&t);
            if(t=='Y'||t=='y')
            {
                for(j = i;j<=iCount-1;j++)
                {
                    st[i] = st[j+1];
                }
                iCount = iCount-1;
                break;
            }
            else
            {
                break;    
            }
        }
        else
        {
            printf("未找到该学生的信息，请核对学生学号：\n");
        }
     return 0;

}

int input(struct student st[])
 {
     int i ,j;
     printf("|---------------6、查看学生信息--------------------|\n");
     printf("|           输出全部学生的成绩信息                 |\n");
     printf("|--------------------------------------------------|\n");
     printf("|学号     姓名    数学     语文     英语      物理 |\n");
     printf("|--------------------------------------------------|\n");
     for(i = 0;i<iCount;i++)
     {
         printf("%s\t",st[i].ID);
         printf("%s\t",st[i].name);
         for(j = 0;j<4;j++)
         {
             printf("%d\t",st[i].score[j]);
         }
     }
     return 0;
 }
int main()
{
    struct student st[N];
    int choise;
    int n;
    int C;
    menu();
    do
    {
        scanf("%d",&choise);
        switch(choise)
        {
            case 1:
            {
                printf("要输入几个学生的信息：\n");
                scanf("%d",&n);
                enter(st,n);
                break;
            }
            case 2:
            {
                insert(st);
                break;
            }
            case 3:
            {
                find(st);
                break;
            }
            case 4:
            {
                revise(st);
                break;
            }
            case 5:
            {
               delet(st);
                break;
            }
            case 6:
            {
                input(st);
                break;
            }
        }
        printf("是否返回功能目录:\n");
        printf("返回输入1：\n");
        printf("不返回输入0：\n");
        scanf("%d",&C);
    }while(C);
return 0;
}

