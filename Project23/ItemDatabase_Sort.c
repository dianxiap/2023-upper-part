#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include "ItemDatabase_internal.h"
#include "MySort.h"
#include <stdlib.h>
#include <string.h>

int CompareByNumber_Ascending(const void *p, const void *q)
/*按编号升序排序的比较函数*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;
    if (p_item->number<q_item->number) return -1;
    else if (p_item->number==q_item->number) return 0;
    else return 1;
}

int CompareByNumber_Descending(const void *p, const void *q)
/*按编号降序排序的比较函数*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;
    if (p_item->number>q_item->number) return -1;
    else if (p_item->number==q_item->number) return 0;
    else return 1;
}

int CompareByQuantity_Ascending(const void *p, const void *q)
/*按数量升序排序的比较函数*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    if (p_item->quantity<q_item->quantity) return -1;
    else if (p_item->quantity==q_item->quantity) return 0;
    else return 1;
}

int CompareByQuantity_Descending(const void *p, const void *q)
/*按数量降序排序的比较函数*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    if (p_item->quantity>q_item->quantity) return -1;
    else if (p_item->quantity==q_item->quantity) return 0;
    else return 1;
}

int CompareByName_Ascending(const void *p, const void *q)
/*按名称升序排序的比较函数*/
/*比较字符串用strcmp()函数,需要加头文件#include<string.h>*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    return strcmp(p_item->name, q_item->name);
    /*返回值为负数、0或正数*/
}

int CompareByName_Descending(const void *p, const void *q)
/*按名称降序排序的比较函数*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

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
    int (*comp_func)(const void*, const void*)=NULL;
    switch (sort_method)
    {
    case SORT_BY_NUMBER:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByNumber_Ascending;
        else
            comp_func = CompareByNumber_Descending;
        break;
    case SORT_BY_NAME:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByName_Ascending;
        else
            comp_func = CompareByName_Descending;
        break;
    case SORT_BY_QUANTITY:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByQuantity_Ascending;
        else
            comp_func = CompareByQuantity_Descending;
        break;
    }

    int num_items=ItemDB_GetNumItems();
    /*动态分配如下数组*/
    struct Item *temp_items=(struct Item *)malloc(num_items*sizeof(struct Item));

    /*创建一个临时结点*/
    struct Item_Node* temp = item_database_head;
    
    int i=0;
   
    /*将链表数据拷贝到数组里*/
    while(temp!=NULL)
    {
        temp_items[i]=temp->data;
        i++;
        temp=temp->next;
    }
    if(comp_func!=NULL)
        QuickSort(temp_items,num_items,sizeof(struct Item), comp_func);

    /*拷贝数组的数据到链表*/
    temp=item_database_head;
    i = 0;
    while(temp!=NULL)
    {
        temp->data=temp_items[i];
        i++;
        temp=temp->next;
    }

    free(temp_items);



}
