/*************************************************************************
	> File Name: mynice.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 08:24:10 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<stdlib.h>

int main(void)
{
    pid_t pid;
    int stat_val = 0;
    int oldpri, newpri;
    
    printf("nice study\n");
    
    pid = fork();
    switch(pid){
            case 0:
                printf("Child is running,Curpid is %d, Parentpid is %d", pid, getppid());
             //   oldpri = getpriority(PRIO_PROCESS, 1);
               // printf("Old priority = %d \n", oldpri);
              //  newpri = nice(2);
             //   printf("New priority = %d\n", newpri);
                exit(0);
            case -1:
                perror("process creation failed\n");
                break;
            default:
                printf("parent is running,Childpid is %d, Parentpid is %d\n", pid, getpid());
                oldpri = getpriority(PRIO_PROCESS, 1);
                printf("Old priority = %d \n", oldpri);
                newpri = nice(19);
                printf("New priority = %d\n", newpri);
                break;
    }

    wait(&stat_val);
    exit(0);
}
