/*************************************************************************
	> File Name: fork2.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 04:14:22 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

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
                printf("parent is running,Childpid is %d, Parentpid is %d\n", pid, getpid());
        default:
            msg = "parent process is running";
            k = 5;
            break;
    }

    while(k > 0){
            puts(msg);
//            sleep(1);
        k--;
    }







}
