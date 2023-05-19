#define _CRT_SECURE_NO_WARNINGS 1
#ifndef MY_H_INCLUDED
#define MY_H_INCLUDED

int ReadLine(char *str, int max_size);
/*读入一行字符存入str中*/
/*最多读入max_size个字符*/

int ReadLineFromFile(FILE *fp, char *str, int max_size);
/*从fp指向的文件读入一行字符存入str中*/
/*最多读入max_size个字符*/

#endif // MY_H_INCLUDED
