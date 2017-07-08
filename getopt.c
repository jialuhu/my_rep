/*************************************************************************
	> File Name: getopt.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年07月08日 星期六 21时45分26秒
 ************************************************************************/


#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int ch;                     /*选项字符 */
    char *b_opt_arg;            /*选项参数字串 */

    while((ch = getopt(argc, argv, "alr:a:l:")) != -1)
    {
        switch(ch)
        {
            case 'a':
                printf("输出参数a\n");
                break;
             case 'l':
                printf("输出参数l\n");
                break;
            case 'r':
                b_opt_arg = optarg;
                printf("输出参数r并且带参数 %s\n", optarg);
                break;
            case '?':
                printf("arguments error!\n");
                break;
        }
    }
    return 0;
}
