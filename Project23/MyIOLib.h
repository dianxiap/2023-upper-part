#define _CRT_SECURE_NO_WARNINGS 1
#ifndef MYIOLIB_H_INCLUDED
#define MYIOLIB_H_INCLUDED

int ReadLine(char *str, int max_size);
/*����һ���ַ�������str��*/
/*������max_size���ַ�(��������β���'\0')*/
/*����ʵ�ʶ�����ַ�����(��������β���'\0')*/

int ReadLineFromFile(FILE *fp,
char *str,int max_size);
/*��fpָ����ļ�����һ���ַ�������str��*/
/*������max_size���ַ�(��������β���'\0')*/
/*����ʵ�ʶ�����ַ�����(��������β���'\0')*/

#endif // MYIOLIB_H_INCLUDED
