#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _FILEOPTION_H_
#define _FILEOPTION_H_
#include "link.h"

/// ���ļ�
int readFile(const char* fileName, link** course);

/// д�ļ�
int writeFile(const char* fileName, link* course);

#endif