/*************************************************************************
	> File Name: env.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 05:46:31 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>

extern char **environ;

int main()
{
    int i;
    for(i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
}
