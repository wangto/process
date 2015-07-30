/*************************************************************************
	> File Name: setuid.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Thu 23 Jul 2015 09:57:52 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    
    setuid(0);
    printf("getuid = %d\n geteuid = %d\n", getuid(),geteuid());
    return 0;
}
