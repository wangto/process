/*************************************************************************
	> File Name: test.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Fri 24 Jul 2015 03:11:34 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
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

void get_input(char *buf)
{
    /*while((*buf++ = getchar()) != '\n')
    ;
    *(buf - 1) = '\0';
*/
    gets(buf);
}
int main()
{
    char a[50][50], buf[50];
    int count = 0, i = 0;
    for(i = 0; i < 50; i++)
        memset(a[i], 0, 50);
    get_input(buf);
    explain_input(buf, &count, a);
    for(i = 0;i < count;i++)
    puts(a[i]);
}
