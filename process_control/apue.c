/*************************************************************************
	> File Name: apue.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Sat 25 Jul 2015 02:40:52 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main()
{
    int var;
    pid_t pid;
    
    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1){
        perror("write error");
    }
    printf("before fork\n");
    

    if((pid = fork()) < 0){
        perror("fork");
    }else if(pid == 0){
        globvar ++;
        var ++;
    }else {
        sleep(2);
    }

    printf("pid = %ld, glob = %d,var = %d\n", (long)getpid(), globvar, var);
    exit(0);






}
