/*************************************************************************
	> File Name: fork3.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 04:28:58 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    char * msg;
    int k;
    printf("process creat \n ");
    pid = fork();
    switch(pid){
        case 0:
            msg = "child process is running";
            k = 3;
            
            break;
        case -1:
            printf("error");
        default:
            msg = "parent process is running";
            k = 5;
            exit(1);
    }
    printf("%s %d\n", msg, getpid());
    sleep(3);
}

