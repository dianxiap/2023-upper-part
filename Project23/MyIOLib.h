#define _CRT_SECURE_NO_WARNINGS 1
#ifndef MYIOLIB_H_INCLUDED
#define MYIOLIB_H_INCLUDED

int ReadLine(char *str, int max_size);
/*读入一行字符串存入str中*/
/*最多读入max_size个字符(不包含结尾标记'\0')*/
/*返回实际读入的字符数量(不包含结尾标记'\0')*/

int ReadLineFromFile(FILE *fp,
char *str,int max_size);
/*从fp指向的文件读入一行字符串存入str中*/
/*最多读入max_size个字符(不包含结尾标记'\0')*/
/*返回实际读入的字符数量(不包含结尾标记'\0')*/

#endif // MYIOLIB_H_INCLUDED
