/*************************************************************************
	> File Name: my_shell.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Thu Jul 23 12:23:43 2015
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

#define normal 0 //一般
#define out 1
#define input 2
#define pipe 3

void print_prompt();
void get_input(char *);
void explain_input(char *, int *, char a[100][256]);
void do_cmd(int, char a[100][256]);
int find_commman(char *);

void err_string(const char *string, int line)
{
    fprintf(stderr, "line:%d\n", line);
    perror(string);
    exit(-1);
}

void print_prompt(void)
{
    printf("[root@xylinux]:~# ");
}

void get_input(char *buf)
{
    int count;
    char ch;
    while(ch = getchar()){
        if(ch == '\n') {
            *buf++ = '\n';
            *buf = '\0';
            break;
        }    
        *buf++ = ch;
    }
}

void explain_input(char *buf, int *argcount, char arglist[100][256])
{
    int i = 0, flag = 0;
    char ch;
    while(1){
        ch = arglist[*argcount][i++] = *buf++;
        if(*buf == ' '){
            flag = 1;  
            arglist[*argcount][i] = '\0' ; 
        }

        if(flag == 1 && ch != ' '){
            i = 0;
            (*argcount)++;
        }

        if(ch == '\n')
            break;

    }   
}


void do_cmd(int argcount, char arglist[100][256])
{
    int flag = 0;
    int how = 0;
    int background = 0;
    int status;
    int i;
    int fd;
    char *arg[argcount + 1];
    char *argnext[argcount + 1];
    char *file;
    pid_t pid;
    
    for(i = 0; i < argcount; i++){
        arg[i] = (char *)arglist[i];
    }
    arg[argcount] = NULL;
    
    for(i = 0; i < argcount; i++) {
        if(strncmp(arg[i], "&", 1) == 0){
            if(i == argcount - 1){
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            }else {
                printf("wrong comman\n");
                return;
            }
        }        
    }

    for(i = 0; argv[i] != NULL; i++){
        if(strcmp(arg[i], ">") == 0) {
            flag++;
            how = out_redirect;
            if(arg[i + 1] == NULL)
                flag++;
        }
        if(strcmp(arg[i], "<") == 0){
            flag++;
            how = in_redirect;
            if(i == 0)
                flag++;
        }
        if(strcmp(arg[i], "|") == 0){
            flag++;
            how = have_pipe;
            if(arg[i + 1] == NULL)
                flag++;
            if(i == 0)
                flag++;
        }
    }
    
    if(flag > 1){
        printf("wrong comman\n");
        return ;
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
            if(strcmp(, "<") == 0){
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == have_pipe){
        for(i = 0; arg[i] != NULL; i++){
            if(strcmp(arg[i], "|") == 0){
                arg[i] = NULL;
                int j;
                for(j = i + 1; arg[j] != NULL; j++)
                {
                    argnext[j - i -1] = arg[j];
                }
                argnext[j - i -1] = arg[j];
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
            if(!find_comman(arg[0])){
                printf("%s :comman not found\n", arg[0]);
                exit(0);
            }
            execvp(arg[0],arg);
            exit(0);
        }
        break;
        case 1:
        if(pid == 0){
            if(!find_comman(arg[0])){
                printf("%s: comman not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
            dup2(fd ,1);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
        case 2:
        if(pid == 0){
            if(!find_comman(arg[0])){
                printf("%s:comman not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDONLY)
            dup2(fd ,0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
        case 3:
        if(pid == 0){
                int pid2;
                int status;
                int fd2;

            if((pid = fork()) < 0){
                 printf("fork2 error\n");
                retun ;
            }else if(pid2 == 0){
                if(!find_comman(arg[0]))
                    printf("%s: comman can't found\n");
                    exit(0);
            }
            fd2 = open("/tmp/c", O_WRONLY|O_CREAT|TRUNC, 0664);
            dup2(fd2, 1);
            execvp(arg[0], arg);
             exit(0);
        }

    }
    if(waitpid(pid2, &status2, 0) == -1){
        printf("wait for child,error\n");
        if(!find_comman(argnext), 0){
            printf("%s: comman not found\n", argnext[0]);
            exit(0);
        }
        fd2 = open("/tmp/c, O_RDONLY");
        dup2(fd2, 0);
        execvp(argnext[0], argnext);

        if(remove("/tmp/c"))
            printf("remove error\n");
            exit(0);
    }
        break;
    default:break;
    }

    if(background == 1){
        printf("process is %d\n", pid);
        return;
    }
    if(waitpid(pid, &status, 0  == -1))
    printf("wait for child precess error\n")
}


int find_commman(char *comman)
{
    DIR *dir;
    struct dirent *ptr;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};
    if(strncmp(comman, "./", 2) == 0)
        comman += 2;

    int i = 0;
    while(path[i] != NULL){
         if((dir = opendir(comman)) == NULL){
            printf("can't open path\n");
         }
        while((ptr = readdir(dir)) != NULL){
            if(strcmp(ptr->d_name, comman) == 0){
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
        i++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    int argcount = 0;
    char arglist[100][256];
    char **arg = NULL;
    char *buf = NULL;
    
    buf = (char *)malloc(256);
    if(buf ==NULL){
        perror("malloc failed\n");
        exit(-1);
    }

    while(1){
            memset(buf, 0, 256);
            print_prompt();
            get_input(buf);
        if(strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") ==0 ){
            break;
        }
        for(i = 0; i < 100; i++){
            arglist[i][0] = '\0';
        }
        argcount = 0;
        explain_input(buf, &argcount, arglist);
        do_cmd(argcount, arglist);
    }
    if(buf != NULL){
        free(buf);
        buf = NULL;
    }
    exit(0);
}

