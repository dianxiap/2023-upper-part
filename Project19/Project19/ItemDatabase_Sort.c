#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include "ItemDatabase_Internal.h"
#include "MySort.h"
#include <string.h>


int CompareByNumber_Ascending(const void* p, const void* q)
/*按编号升序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    if (p_item->number < q_item->number)
        return 1;
    else if (p_item->number == q_item->number)
        return 0;
    else
        return -1;
}

int CompareByNumber_Descending(const void* p, const void* q)
/*按编号降序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    if (p_item->number > q_item->number)
        return -1;
    else if (p_item->number == q_item->number)
        return 0;
    else
        return 1;
}

int CompareByQuantity_Ascending(const void* p, const void* q)
/*按数量升序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    if (p_item->quantity < q_item->quantity)
        return -1;
    else if (p_item->quantity == q_item->quantity)
        return 0;
    else
        return 1;
}

int CompareByQuantity_Descending(const void* p, const void* q)
/*按数量降序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    if (p_item->quantity < q_item->quantity)
        return 1;
    else if (p_item->quantity == q_item->quantity)
        return 0;
    else
        return -1;
}

int CompareByName_Ascending(const void* p, const void* q)
/*按名称升序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    return strcmp(p_item->name, q_item->name);
    /*返回值为负数、0或正数*/
}

int CompareByName_Descending(const void* p, const void* q)
/*按名称降序排序的比较函数*/
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;

    return -strcmp(p_item->name, q_item->name);
    /*返回值为负数、0或正数*/
}


void ItemDB_Sort(int sort_method, int sort_dir)
/* 对数据库中的物品进行排序。
   sort_method是排序方法，可以取下列值之一：
     SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
   sort_dir是排序方向，可以取下列值之一：
     SORT_ASCENDING, SORT_DESCENDING */
{
    int num_items = ItemDB_GetNumItems();
    ItemIterator iter;

    int *a=(int*)malloc(num_items*sizeof(int));
    int i = 0;


    /*将链条中的物品信息储存到数组中*/
    for (iter = ItemDB_GetFirstItemIterator();
        ItemDB_IsItemIteratorValid;
        iter = ItemDB_GetNextItemIterator(iter))
    {
        a[i] = iter.p;
        i++;
    }

    /*排序*/
    int (*cmp_func)(const void*, const void*)=NULL;
    switch (sort_method)
    {
    case SORT_BY_NUMBER:
        if (sort_dir == SORT_ASCENDING)
            cmp_func = CompareByNumber_Ascending;
        else
            cmp_func = CompareByNumber_Descending;
        break;
    case SORT_BY_NAME:
        if (sort_dir == SORT_ASCENDING)
            cmp_func = CompareByName_Ascending;
        else
            cmp_func = CompareByName_Descending;
        break;
    case SORT_BY_QUANTITY:
        if (sort_dir == SORT_ASCENDING)
            cmp_func = CompareByQuantity_Ascending;
        else
            cmp_func = CompareByQuantity_Descending;
        break;
    }
    QuickSort(a, num_items, sizeof(struct Item), cmp_func);

    /*将数组再存入链表*/
    /*把原链表清空*/

    /*遍历数组，存入链表*/
}





