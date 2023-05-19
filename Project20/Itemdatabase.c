#include"Itemdatabase.h"
#include "Itemdatabase_internal.h"
#include<stdlib.h>
#include<string.h>

#if 1
#define ENABLE_LOG
#endif

int num_items = 0;

struct Item_Node *item_database_head = NULL;/*��Ʒ���ݿ�����ͷָ����ⲿ����*/
struct Item_Node *item_database_tail = NULL;/*��Ʒ���ݿ�����βָ����ⲿ����*/

ItemIterator ItemDB_GetFirstItemIterator(void)
{
    ItemIterator iter;
    iter.p = item_database_head;
    return iter;
}

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
/*������һ����Ʒ�ĵ�����*/
{
    ItemIterator iter_next;
    struct Item_Node *pn;
    pn = (struct Item_Node*)iter.p;
    iter_next.p = pn -> next;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*�����Ʒ������iter�Ƿ���Ч*/
{
    return iter.p != NULL;
}

ItemIterator ItemDB_FindItem(int item_number)
/*�����ݿ����������Ϊitem_number����Ʒ*/
/*�ҵ�������Ʒ������*/
/*���򷵻�һ����Ч�ĵ�����*/
{
    ItemIterator iter;
    struct Item_Node *pn;
    for(pn = item_database_head;  pn != NULL; pn = pn->next)
    {
        if(pn->data.number == item_number)
            break;
    }
    iter.p = pn;
    return iter;
}

int ItemDB_IsEmpty(void)
{
    return !num_items;
}

struct Item* ItemDB_GetItemPointer(ItemIterator iter)
/*����ָ�����ݿ��е�����iter��Ӧ����Ʒ��ָ��*/
{
    return (struct Item*)iter.p;
}

int ItemDB_AddItem(const struct Item *p_item)
{
    /*��p_itemָ�����Ʒ�������ݿ���*/
    /*����Ʒ�������ݿ��β*/
    /*�ɹ�����1�����򷵻�0*/

    struct Item_Node *new_item = (struct Item_Node*)malloc(sizeof(struct Item_Node));
    memcpy(&new_item->data,p_item,sizeof(struct Item));
    new_item->next = NULL;

    if(item_database_head != NULL)
    {
        new_item->prev = item_database_tail;
        item_database_tail->next = new_item;
    }
    else
    {
        new_item->prev = NULL;
        item_database_head = new_item;
    }

    ++num_items;/*��Ʒ����+1*/
    item_database_tail = new_item;
    return 1;
}

void ItemDB_DeleteItem(ItemIterator iter)
{/*�����ݿ�������ֵΪitem_index��Ԫ��ɾ��*/
    struct Item_Node *pn = (struct Item_Node*)iter.p;

    if(pn->next == NULL && pn->prev == NULL)
        item_database_tail = item_database_head = NULL;
    else if(pn->next == NULL)
    {
        pn->prev->next = NULL;
        item_database_tail = pn->prev;
    }
    else if(pn->prev == NULL)
    {
        pn->next->prev = NULL;
        item_database_head = pn->next;
    }
    else
    {
        pn->next->prev = pn->prev;
        pn->prev->next = pn->next;
    }
    free(pn);
    /*��Ʒ����-1*/
    -- num_items;

}

void ItemDB_Clear(void)
{
    struct Item_Node *pn, *pn_next;
    for(pn = item_database_head; pn != NULL;)
    {
        pn_next = pn->next;
        free(pn);
        pn = pn_next;
    }
    num_items = 0;
    item_database_head = NULL;
    item_database_tail = NULL;
}

int ItemDB_GetNumItems()
{/*������Ʒ����*/
    return num_items;
}
