#define _CRT_SECURE_NO_WARNINGS 1
#ifndef MYSORT_H_INCLUDED
#define MYSORT_H_INCLUDED

#include <stdlib.h>

void QuickSort(void *base, size_t num_elements, size_t element_size,
 int (*compare_func)(const void*, const void*));
/*��baseָ������鰴�մ�С�����˳���������*/

unsigned char *FindSplitElement(
    unsigned char *low, unsigned char *high,
    size_t element_size,
    int (*compare_func)(const void *, const void *));
/* ��������ѡ��ָ�Ԫ�ز�����ָ���Ԫ�ص�ָ�롣
   lowָ������ĵ�һ��Ԫ�أ�highָ����������һ��Ԫ�ء�
   ����ÿ��Ԫ�صĳߴ�Ϊelement_size���ֽڡ�
   Ԫ�صĴ�С��ϵ��compare_funcָ��ıȽϺ����жϡ�
   �ú����ķ���ֵ���壺����������ڣ��������ڣ���������С�ڡ� */

#endif // MYSORT_H_INCLUDED
