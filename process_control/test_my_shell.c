/*************************************************************************
	> File Name: test_my_shell.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Wed 22 Jul 2015 11:06:33 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

#define normal 0
#define out_redirect 1
#define in_redirect 2
#define have_pipe 3

void print_prompt(void);
void get_input(char *);
void explain_input(char *, int *, char a[50][50]);
void do_cmd(int count, char a[50][50]);
int  find_comman(char *);

int main(int argc, char **argv)
{
    char _comman[100][50];
    int count = 0;
    char comman[50];
    
    while(1){
        memset(_comman, 0, 100);
        print_prompt();
        get_input(comman);
        if(strcmp(comman, "logout") == 0 || strcmp(comman, "exit") == 0)
            break;
        explain_input(comman, &count, _comman);
        do_cmd(count, _comman);
    }
    return 0;
}

void print_prompt()
{
    printf("[root@xylinux]:~# ");
}

void get_input(char *buf)
{
    int i = 0;
    while((*buf++ = getchar()) != '\n');
    *(buf - 1) = '\0'; 
}

void explain_input(char *buf, int *count, char array[50][50])
{
    int i, j = 0;
    for(i = 0; buf[i] != '\0'; i++){
        if(buf[i] == ' '){
            if(buf[i + 1] != ' ' && buf[i + 1] != '\0'){
                j = 0;
                (*count)++;
                continue;
            }
        }
    array[(*count)][j++] = buf[i];
    }
    (*count)++;
}


void do_cmd(int count, char a[50][50])
{
    int i = 0, flag = 0, pid, fd, status, how = 0;
    char *arg[50], *argnext[50], *file;
    for(i = 0; i < 50; i++)
        memset(arg, 0, 50);
    for(i = 0; i < count; i++)
        arg[i] = (char *) a[i];
    arg[count] = NULL;

    for(i = 0; arg[i] != NULL; i++) {
        if(strcmp(arg[i], ">") == 0){
            how = out_redirect;
            flag++;
            if(arg[i + 1] == NULL)
                flag++;
        }
        if(strcmp(arg[i], "<") == 0){
            how = in_redirect;
            flag++;
            if(i == 0)
                flag++;
        }
        if(strcmp(arg[i], "|") == 0){
            how = have_pipe;
            flag++;
            if(arg[i + 1] == NULL)
                flag++;
            if(i == 0)
                flag++;
        }
    }
    
    if(flag > 1){
        printf("wrong comman\n");
        return;
    }
    
    if(how == out_redirect){
        for(i = 0; arg[i] != NULL; i++){
            if(strcmp(arg[i], ">") == 0){
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == in_redirect){
        for(i = 0; arg[i] != NULL; i++){
            if(strcmp(arg[i], "<") == 0){
                file = arg[i + 1];
                arg[i] = NULL;
            } 
        }    
    }

    if(how == have_pipe){
        for(i = 0; arg[i] != NULL; i++){
            if(strcmp(arg[i], "|") == 0){
                arg[i] == NULL;
                int j;
                for(j = i + 1; arg[j] != NULL; j++)
                    argnext[j - i - 1] = arg[j];
                argnext[j - i - 1] = arg[j];
            break;
            }
        }
    }


    if((pid = fork()) < 0){
        printf("fork error\n");
        return;
    }

    switch(how){
        case 0:
        if(pid == 0){
            if(find_comman(arg[0])){
                printf("Comman not search\n");
                    exit(0);
            }
            execvp(arg[0], arg);
            exit(0);
        }
        break;
        case 1:
        if(pid == 0){
            if(find_comman(arg[0])){
                printf("Comman not search\n");
                    exit(0);
            }
            fd = open(file, O_RDONLY|O_CREAT|O_TRUNC,0644);
            dup2(fd ,1);
            execvp(arg[1], arg);
            exit(0);
        }
        break;
        case 2:
        if(pid == 0){
            if(find_comman(arg[0])){
                printf("Comman not search\n");
                exit(0) ;                
            }
            fd = open(file, O_RDONLY);
            dup2(fd, 0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
        case 3:
        if(pid == 0){
            int pid2;
            int status2;
            int fd2;

            if((pid2 = fork()) < 0){
                printf("fork2 error\n");
                return;
            }else if(pid2 == 0){
                if(find_comman(arg[0])){
                    printf("%s is not search\n", arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                dup2(fd2, 1);
                execvp(arg[0], arg);
                exit(0);
            }
    
            if(waitpid(pid2, &status2, 0) == -1)
                printf("wait for child error\n");
            if(find_comman(argnext[0])){
                printf("%s :comman not found\n", argnext[0]);
                exit(0);      
            }
            fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
            dup2(fd2, 0);
            execvp(argnext[0], argnext);
        
            if(remove("/tmp/youdonotknowfile"))
                printf("remove error\n");
            exit(0);
        }
        break;
        default:
                break;
    }
    if(pid > 0)
   if(waitpid(pid, &status, 0) == -1)
        printf("wait for child process error\n");
    
}

int find_comman(char *comman)
{
    DIR *dir;
    struct dirent *ptr;
    int i = 0;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};
    if(strncmp(comman, "./", 2) == 0)
        comman += 2;
    while(path[i] != NULL){
        if((dir = opendir(path[i])) == NULL)
            printf("NOT SEARCH PATH\n");
        while((ptr = readdir(dir)) != NULL){
            if(strcmp(ptr->d_name, comman) == 0){
                    closedir(dir);
                    return 0;
                
            }
        }
        closedir(dir);
        i++;
    }
    return 1;
}
