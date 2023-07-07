#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED
#include "base.h"
/*读入一行字符存入str中*/
/*最多读入NAME_MAX_LEN个字符*/
int ReadLine(char *str, int NAME_MAX_LEN);
int ReadLineFromFile(FILE *fp, char *str, int NAME_MAX_LEN);
/*从fp指向的文件读入一行字符存入str中*/
#endif // READ_H_INCLUDED
