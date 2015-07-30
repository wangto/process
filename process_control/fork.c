/*************************************************************************
	> File Name: fork.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 03:53:15 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    printf("process creat\n");
    pid = fork();
    switch(pid){
            case -1:
                    printf("Process creat fail\n");
                    break;
            case 0:
                    printf("parent process id:%d, child process is %d\n", getppid(), pid);
                    break;
            default:
                    printf("parent process id:%d, child process is %d\n", getpid(), pid);
                    break;
    }








}
