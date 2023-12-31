#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include "MyIOLib.h"
int ReadLine(char *str, int max_size)
{/*读入一行字符串存入str中*/
    char ch;
    int i = 0;
    while((ch = getchar()) != '\n')
        if(i < max_size) str[i++] = ch;
        /*最多读入max_size个字符(不包含结尾标记'\0')*/
    str[i] = '\0';
    return i;/*返回实际读入的字符数量(不包含结尾标记'\0')*/
}

int ReadLineFromFile(FILE *fp, char *str, int max_size)
/*从fp指向的文件读入一行字符存入str中*/
/*最多读入max_size个字符*/
{
    char ch;
    int i = 0;
    while( 1 )
    {
        ch = fgetc(fp);
        if(ch == EOF || ch == '\n') break;
        if(i < max_size) str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}
