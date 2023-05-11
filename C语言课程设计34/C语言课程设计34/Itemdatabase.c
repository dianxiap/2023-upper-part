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
/*��̬�洢�����ӿ��С*/

int max_capacity = 0; /*��Ʒ���ݿ���������*/
int num_items = 0;
struct Item* item_database = NULL;

ItemIterator ItemDB_GetFirstItemIterator(void)
{
    ItemIterator iter;
    iter.i = 0;
    return iter;
}

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
/*������һ����Ʒ�ĵ�����*/
{
    ItemIterator iter_next;
    iter_next.i = iter.i + 1;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*�����Ʒ������iter�Ƿ���Ч*/
{
    return iter.i >= 0 && iter.i < num_items;
}

ItemIterator ItemDB_FindItem(int item_number)
/*�����ݿ����������Ϊitem_number����Ʒ*/
/*�ҵ�������Ʒ������*/
/*���򷵻�һ����Ч�ĵ�����*/
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
    /*����ָ�����ݿ��е�����iter��Ӧ����Ʒ��ָ��*/
{
    return item_database + iter.i;
}

int ItemDB_AddItem(const struct Item* p_item)
{ /*��������Ƿ���Ҫ��������*/
    if (num_items == max_capacity)
    {
        /*����������*/
        int new_max_capacity = max_capacity + CHUNK_SIZE;
        /*�������ݿ�����*/
        struct Item* tmp= (struct Item*)realloc(item_database, new_max_capacity * sizeof(struct Item));

        assert(tmp);
        item_database = tmp;

        /*������������Ƿ�ɹ�*/
        if (item_database == NULL) return 0;

#ifdef ENABLE_LOG
        printf("���ݿ���������%d -> %d\n", max_capacity, new_max_capacity);
#endif // ENABLE_LOG
        /*������������Ϊ��ǰ����*/
        max_capacity = new_max_capacity;
    }
    /*��p_itemָ�����Ʒ�������ݿ���*/
  /*����Ʒ�������ݿ��β*/
  /*�ɹ�����1�����򷵻�0*/
    item_database[num_items] = *p_item;
    ++num_items; /*��Ʒ����+1*/
    return 1;
}

void ItemDB_DeleteItem(ItemIterator iter)
{/*�����ݿ�������ֵΪitem_index��Ԫ��ɾ��*/
    int j = iter.i;
    while (j < num_items - 1)
    {
        item_database[j] = item_database[++j];
    }
    /*��Ʒ����-1*/
    --num_items;

    /*������ݿ��Ƿ���Ҫ��С����*/
    if (num_items == max_capacity - CHUNK_SIZE)
    {

#ifdef ENABLE_LOG
        printf("���ݿ�������С��%d -> %d\n", max_capacity, num_items);
#endif // ENABLE_LOG

        if (num_items == 0)
        {
            /*�ͷ����ݿ�洢�ռ�*/
            free(item_database);
            item_database = NULL;
            max_capacity = 0;
        }
        else
        {
            /*��С���ݿ�����*/
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
{/*������Ʒ����*/
    return num_items;
}
