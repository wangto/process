/*************************************************************************
	> File Name: test0.2.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Sat 25 Jul 2015 10:47:11 AM EDT
 ************************************************************************/

#include<stdio.h>


void get_input(char *buf)
{
    int i = 0;
    while((*buf++ = getchar()) != '\n')
    ;
    *(buf - 1) = '\0';
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaa");
}

int main()
{
    char a[50];
    get_input(a);
    puts(a);


}
