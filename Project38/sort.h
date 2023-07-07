#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include<stdlib.h>
void QuickSort(void *base, size_t num_elements, size_t element_size,
 int (*compare_func)(const void*, const void*));
 unsigned char *FindSplitElement(
    unsigned char *low, unsigned char *high,
    size_t element_size,
    int (*compare_func)(const void *, const void *));

#endif // SORT_H_INCLUDED
