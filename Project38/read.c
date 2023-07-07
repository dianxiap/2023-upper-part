#include<stdio.h>
#include"read.h"
int ReadLine(char *str, int NAME_MAX_LEN){
if((ch=getchar())!='\n')
if(i<NAME_MAX_LEN){
    str[i]=ch;
    i++;
}
str[i]='\0';
return i;
}
int ReadLineFromFile(FILE *fp, char *str, int NAME_MAX_LEN){
    char ch;
    int i = 0;
    while( 1 )
    {
        ch = fgetc(fp);
        if(ch == EOF || ch == '\n') break;
        if(i < NAME_MAX_LEN){
             str[i] = ch;
             i++;
        }
    }
    str[i] = '\0';
    return i;
}
