#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED
#include "base.h"
/*����һ���ַ�����str��*/
/*������NAME_MAX_LEN���ַ�*/
int ReadLine(char *str, int NAME_MAX_LEN);
int ReadLineFromFile(FILE *fp, char *str, int NAME_MAX_LEN);
/*��fpָ����ļ�����һ���ַ�����str��*/
#endif // READ_H_INCLUDED
