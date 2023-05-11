#define _CRT_SECURE_NO_WARNINGS 1
#include "MySort.h"
#include "Itemdatabase.h"
#include "Itemdatabase_internal.h"
#include <string.h>

int CompareByNumber_Ascending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (p_item->number < q_item->number) return -1;
    else if (p_item->number == q_item->number) return 0;
    else return 1;
}
int CompareByNumber_Descending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (p_item->number < q_item->number) return 1;
    else if (p_item->number == q_item->number) return 0;
    else return -1;
}

int CompareByName_Ascending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (strcmp(p_item->name, q_item->name) < 0) return -1;
    else if (!strcmp(p_item->name, q_item->name)) return 0;
    else return 1;
}
int CompareByName_Descending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (strcmp(p_item->name, q_item->name) < 0) return 1;
    else if (!strcmp(p_item->name, q_item->name)) return 0;
    else return -1;
}

int CompareByQuantity_Ascending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (p_item->quantity < q_item->quantity) return -1;
    else if (p_item->quantity == q_item->quantity) return 0;
    else return 1;
}
int CompareByQuantity_Descending(const void* p, const void* q)
{
    const struct Item* p_item = (const struct Item*)p;
    const struct Item* q_item = (const struct Item*)q;
    if (p_item->quantity < q_item->quantity) return 1;
    else if (p_item->quantity == q_item->quantity) return 0;
    else return -1;
}

void ItemDB_Sort(int sort_method, int sort_dir)
/* 对数据库中的物品进行排序。
   sort_method是排序方法，可以取下列值之一：
     SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
   sort_dir是排序方向，可以取下列值之一：
     SORT_ASCENDING, SORT_DESCENDING */
{
    int (*fun_sort)(const void*, const void*);
    if (sort_dir == SORT_ASCENDING)
    {
        if (sort_method == SORT_BY_NUMBER)
            fun_sort = CompareByNumber_Ascending;
        else if (sort_method == SORT_BY_NAME)
            fun_sort = CompareByName_Ascending;
        else
            fun_sort = CompareByQuantity_Ascending;
    }
    else
    {
        if (sort_method == SORT_BY_NUMBER)
            fun_sort = CompareByNumber_Descending;
        else if (sort_method == SORT_BY_NAME)
            fun_sort = CompareByName_Descending;
        else
            fun_sort = CompareByQuantity_Descending;
    }

    QuickSort(item_database, num_items, sizeof(struct Item), fun_sort);
}
