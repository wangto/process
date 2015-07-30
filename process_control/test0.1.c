/*************************************************************************
	> File Name: test0.1.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Sat 25 Jul 2015 10:40:38 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char array[100];
    memset(array, 0, 100);
    int i;
    while((array[i++] = getchar()) != '\n');
    puts(array);





}
