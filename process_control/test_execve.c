/*************************************************************************
	> File Name: test_execve.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 28 Jul 2015 09:46:10 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    char *arg[]={"ls", "-a", "/",NULL};
    execvp(arg[0], arg);
    return 0;

}
