#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "ItemDatabase_internal.h"

#if 1 /*1�ĳ�0�������������ı仯�����*/
#define ENABLE_LOG
#endif

struct Item_Node *item_database_head=NULL;
    /*���ݿ�����ͷָ����ⲿ������ָ�������һ�����*/

struct Item_Node *item_database_tail=NULL;
    /*���ݿ�βָ�룬ָ���������һ�����*/


int num_items=0; /*��Ʒ����*/

ItemIterator ItemDB_GetFirstItemIterator(void)
/*���ص�һ����Ʒ�ĵ�����*/
{
    ItemIterator iter;
    iter.p=item_database_head;
    return iter;
}

ItemIterator
ItemDB_GetNextItemIterator(
    ItemIterator iter)
/*������һ����Ʒ�ĵ�����*/
{
    ItemIterator iter_next;
    struct Item_Node *pn;
    pn=(struct Item_Node *)iter.p;
    iter_next.p=pn->next;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*�����Ʒ������iter�Ƿ���Ч*/
/*��Ч����1�����򷵻�0*/
{
    return iter.p!=NULL;
}

ItemIterator ItemDB_FindItem(int item_number)
/*�����ݿ����������Ϊitem_number����Ʒ*/
/*�ҵ��򷵻���Ʒ�ĵ�����*/
/*���򷵻�һ����Ч�ĵ�����*/
{
    ItemIterator iter;
    struct Item_Node *pn=NULL;
    for (pn=item_database_head->next;
    pn!=NULL;pn=pn->next)
    {
        if (pn->data.number==item_number)
            break;
    }
    iter.p=pn;
    return iter;
}

int ItemDB_IsEmpty(void)
/*������ݿ��Ƿ�Ϊ�գ����򷵻�1�����򷵻�0*/
{
    return num_items==0;
}

int ItemDB_AddItem(
    const struct Item *p_item)
/*��p_itemָ�����Ʒ�������ݿ���*/
/*�ɹ�����1�����򷵻�0*/
{
    /*����һ���ڵ���¿ռ�*/
    struct Item_Node *new_p;
    new_p=(struct Item_Node *)malloc(sizeof (struct Item_Node));

    memcpy(&new_p->data, p_item, sizeof(struct Item));
    new_p->next = NULL;

    if (item_database_head != NULL)
    {
        new_p->prev = item_database_tail;
        item_database_tail->next = new_p;
    }
    else
    {
        new_p->prev = NULL;
        item_database_head = new_p;
    }

    ++num_items;/*��Ʒ����+1*/
    item_database_tail = new_p;
    return 1;

}

void ItemDB_DeleteItem(ItemIterator iter)
/*�����ݿ��е�����iter��Ӧ����Ʒɾ��*/
{
    struct Item_Node *pn=(struct Item_Node *)iter.p;

    if (pn->next == NULL && pn->prev == NULL)
        item_database_head = item_database_tail = NULL;
    else if (pn->next == NULL)
    {
        pn->prev->next = NULL;
        item_database_tail = pn->prev;
    }
    else if (pn->prev == NULL)
    {
        pn->next->prev = NULL;
        item_database_head = pn->next;
    }
    else
    {
        pn->next->prev = pn->prev;
        pn->prev->next = pn->next;
    }


    free(pn); //�ͷ�new_pָ��Ľڵ���ռ�õ��ڴ�ռ�
    num_items--;
}

struct Item *ItemDB_GetItemPointer(
    ItemIterator iter)
/*����ָ�����ݿ��е�����iter��Ӧ����Ʒ��ָ��*/
{
    struct Item_Node *new_p=(struct Item_Node *)iter.p;
    return &(new_p->data);
}

void ItemDB_Clear(void)
/*������ݿ�*/
{
    struct Item_Node *pn;
    num_items=0;
    pn=item_database_head;

    while (pn!=NULL)
    {
        struct Item_Node *pn_next=pn->next;
        free(pn);
        pn=pn_next;
    }
    item_database_head=NULL;
    item_database_tail=NULL;

}

int ItemDB_GetNumItems(void)
/*������Ʒ����*/
{
    return num_items;
}
