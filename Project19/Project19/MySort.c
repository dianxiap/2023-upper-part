#define _CRT_SECURE_NO_WARNINGS 1
#include "MySort.h"
#include <string.h>
#include <stdlib.h>

unsigned char* FindSplitElement(
    unsigned char* low, unsigned char* high,
    size_t element_size,
    int (*compare_func)(const void*, const void*))
    /* ��������ѡ��ָ�Ԫ�ز�����ָ���Ԫ�ص�ָ�롣
       lowָ������ĵ�һ��Ԫ�أ�highָ����������һ��Ԫ�ء�
       ����ÿ��Ԫ�صĳߴ�Ϊelement_size���ֽڡ�
       Ԫ�صĴ�С��ϵ��compare_funcָ��ıȽϺ����жϡ�
       �ú����ķ���ֵ���壺����������ڣ��������ڣ���������С�ڡ� */
{
    int i;
    unsigned char* part_element = (unsigned char*)malloc(element_size);

    for (i = 0; i < element_size; i++)
        part_element[i] = low[i];

    memcpy(low, high, element_size);

    for (;;)
    {
        while (low < high && compare_func(part_element, high) <= 0)//�Ƚ�����ֵ
            high -= element_size;

        if (low >= high)
            break;

        for (i = 0; i < element_size; ++i)
            low[i] = high[i];
        low += element_size;

        while (low < high && compare_func(low, part_element) <= 0)
            low += element_size;

        if (low >= high)
            break;

        for (i = 0; i < element_size; ++i)
            high[i] = low[i];
        high -= element_size;
    }

    for (i = 0; i < element_size; ++i)
        high[i] = part_element[i];

    free(part_element);
    return high;
}


void QuickSort(void* base,
    size_t num_elements, size_t element_size,
    int (*compare_func)(const void*, const void*))
    /* ��baseָ������鰴�մ�С�����˳���������
       ������num_elements��Ԫ�أ�
       ÿ��Ԫ�صĳߴ�Ϊelement_size���ֽڡ�
       Ԫ�صĴ�С��ϵ��compare_funcָ��ıȽϺ����жϡ�
       �ú����ķ���ֵ���壺����������ڣ��������ڣ���������С�ڡ� */
{
    size_t num_elements_before;
    unsigned char* middle;
    unsigned char* base_ub = (unsigned char*)base;
    if (num_elements <= 1) return;
    middle = FindSplitElement(base,
        base_ub + (num_elements - 1) * element_size,
        element_size, compare_func);
    num_elements_before = (middle - base_ub) / element_size;
    QuickSort(base, num_elements_before,
        element_size, compare_func);
    QuickSort(middle + element_size,
        num_elements - num_elements_before - 1,
        element_size, compare_func);

}
