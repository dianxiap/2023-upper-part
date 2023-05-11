#define _CRT_SECURE_NO_WARNINGS 1
#include"Itemdatabase.h"
#include "Itemdatabase_internal.h"
#include<stdlib.h>
#include <assert.h>
#include <stdio.h>
#if 1
#define ENABLE_LOG
#endif

#define CHUNK_SIZE 5
/*动态存储分配子块大小*/

int max_capacity = 0; /*物品数据库的最大容量*/
int num_items = 0;
struct Item* item_database = NULL;

ItemIterator ItemDB_GetFirstItemIterator(void)
{
    ItemIterator iter;
    iter.i = 0;
    return iter;
}

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
/*返回下一个物品的迭代器*/
{
    ItemIterator iter_next;
    iter_next.i = iter.i + 1;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*检查物品迭代器iter是否有效*/
{
    return iter.i >= 0 && iter.i < num_items;
}

ItemIterator ItemDB_FindItem(int item_number)
/*在数据库中搜索编号为item_number的物品*/
/*找到返回物品迭代器*/
/*否则返回一个无效的迭代器*/
{
    ItemIterator iter;
    int i;
    for (i = 0; i < num_items; i++)
    {
        if (item_database[i].number == item_number)
        {
            iter.i = i;
            return iter;
        }
    }
    iter.i = -1;
    return iter;
}

int ItemDB_IsEmpty(void)
{
    return !num_items;
}

struct Item* ItemDB_GetItemPointer(ItemIterator iter)
    /*返回指向数据库中迭代器iter对应的物品的指针*/
{
    return item_database + iter.i;
}

int ItemDB_AddItem(const struct Item* p_item)
{ /*检查数据是否需要扩大容量*/
    if (num_items == max_capacity)
    {
        /*计算新容量*/
        int new_max_capacity = max_capacity + CHUNK_SIZE;
        /*扩大数据库容量*/
        struct Item* tmp= (struct Item*)realloc(item_database, new_max_capacity * sizeof(struct Item));

        assert(tmp);
        item_database = tmp;

        /*检查容量扩大是否成功*/
        if (item_database == NULL) return 0;

#ifdef ENABLE_LOG
        printf("数据库容量扩大：%d -> %d\n", max_capacity, new_max_capacity);
#endif // ENABLE_LOG
        /*把新容量设置为当前容量*/
        max_capacity = new_max_capacity;
    }
    /*将p_item指向的物品加入数据库中*/
  /*将物品存入数据库结尾*/
  /*成功返回1，否则返回0*/
    item_database[num_items] = *p_item;
    ++num_items; /*物品总数+1*/
    return 1;
}

void ItemDB_DeleteItem(ItemIterator iter)
{/*将数据库中索引值为item_index的元素删除*/
    int j = iter.i;
    while (j < num_items - 1)
    {
        item_database[j] = item_database[++j];
    }
    /*物品总数-1*/
    --num_items;

    /*检查数据库是否需要缩小容量*/
    if (num_items == max_capacity - CHUNK_SIZE)
    {

#ifdef ENABLE_LOG
        printf("数据库容量缩小：%d -> %d\n", max_capacity, num_items);
#endif // ENABLE_LOG

        if (num_items == 0)
        {
            /*释放数据库存储空间*/
            free(item_database);
            item_database = NULL;
            max_capacity = 0;
        }
        else
        {
            /*缩小数据库容量*/
            struct Item*  tmp=(struct Item*)realloc(item_database, num_items * sizeof(struct Item));
            assert(tmp);
            item_database = tmp;
            max_capacity = num_items;
        }
    }
}

void ItemDB_Clear(void)
{
    num_items = 0;
    max_capacity = 0;
    if (item_database != NULL)
    {
        free(item_database);
        item_database = NULL;
    }
}

int ItemDB_GetNumItems()
{/*返回物品总数*/
    return num_items;
}
