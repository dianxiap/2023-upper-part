#pragma once
#ifndef MYSORT_H_INCLUDED
#define MYSORT_H_INCLUDED

#include <stdlib.h>

void QuickSort(void* base, size_t num_elements, size_t element_size,
    int (*compare_func)(const void*, const void*));
/*对base指向的数组按照从小到大的顺序进行排序*/

unsigned char* FindSplitElement(
    unsigned char* low, unsigned char* high,
    size_t element_size,
    int (*compare_func)(const void*, const void*));
/* 从数组中选择分割元素并返回指向该元素的指针。
   low指向数组的第一个元素，high指向数组的最后一个元素。
   数组每个元素的尺寸为element_size个字节。
   元素的大小关系由compare_func指向的比较函数判断。
   该函数的返回值含义：正数代表大于，零代表等于，负数代表小于。 */

#endif // MYSORT_H_INCLUDED
