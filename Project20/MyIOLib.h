#define _CRT_SECURE_NO_WARNINGS 1
#ifndef MY_H_INCLUDED
#define MY_H_INCLUDED

int ReadLine(char *str, int max_size);
/*����һ���ַ�����str��*/
/*������max_size���ַ�*/

int ReadLineFromFile(FILE *fp, char *str, int max_size);
/*��fpָ����ļ�����һ���ַ�����str��*/
/*������max_size���ַ�*/

#endif // MY_H_INCLUDED
