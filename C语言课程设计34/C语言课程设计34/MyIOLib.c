#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include "MyIOLib.h"
int ReadLine(char* str, int max_size)
{/*����һ���ַ�������str��*/
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n')
        if (i < max_size) str[i++] = ch;
    /*������max_size���ַ�(��������β���'\0')*/
    str[i] = '\0';
    return i;/*����ʵ�ʶ�����ַ�����(��������β���'\0')*/
}

int ReadLineFromFile(FILE* fp, char* str, int max_size)
/*��fpָ����ļ�����һ���ַ�����str��*/
/*������max_size���ַ�*/
{
    char ch;
    int i = 0;
    while (1)
    {
        ch = fgetc(fp);
        if (ch == EOF || ch == '\n') break;
        if (i < max_size) str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}
