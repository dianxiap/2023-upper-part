#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _FILEOPTION_STUDENT_H_
#define _FILEOPTION_STUDENT_H_
#include "link_student.h"

/// ���ļ�
int readFile_student(const char* fileName, linkStudent** stu);

/// д�ļ�
int writeFile_student(const char* fileName, linkStudent* stu);

#endif