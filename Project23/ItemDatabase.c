#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "ItemDatabase_internal.h"

#if 1
#define ENABLE_LOG
#endif

struct Item_Node *item_database_head=NULL;
/*���ݿ�ͷָ�룬ָ�������һ�����*/

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

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
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
    struct Item_Node *pn;
    for (pn=item_database_head; pn!=NULL ; pn=pn->next)
    {
        if (pn->data.number==item_number)
        {
            break;
        }
    }
    iter.p=pn;
    return iter;
}

int ItemDB_IsEmpty(void)
/*������ݿ��Ƿ�Ϊ�գ����򷵻�1�����򷵻�0*/
{
    if(num_items==0)
		return 1;
	else
        return 0;
}

int ItemDB_AddItem(const struct Item *p_item)
/*��p_itemָ�����Ʒ�������ݿ���*/
/*�ɹ�����1�����򷵻�0*/
{
    /*����һ���µĽ��*/
    struct Item_Node *ptr;
    ptr=(struct Item_Node *)malloc(sizeof(struct Item_Node));

    /*ptr����Ʒ������*/
    ptr->data=*p_item;

    /*�ж��½ڵ��Ƿ�Ϊ��*/
    if(item_database_head == NULL)
        item_database_head=item_database_tail=ptr;
    else
    {
        /*���½����뵽������*/
        ptr->prev=item_database_tail;
        item_database_tail->next=ptr;
        item_database_tail=ptr;
    }
   item_database_tail->next=NULL;
   num_items++;
   return 1;
}

void ItemDB_DeleteItem(ItemIterator iter)
{
    /*����2���µĽ��*/
    struct Item_Node *ptr1,*ptr2;

    /*ǿ������ת��*/
    ptr2=(struct Item_Node *)iter.p;

    /*���������Ƿ���Ч*/
    if(!ItemDB_IsItemIteratorValid(iter))
    {
        printf("��Ʒ�����ڣ�");
        return;
    }
    else if(ptr2==item_database_head)/*��Ҫɾ������Ʒ�������ͷ��ʱ*/
    {
        item_database_head=item_database_head->next;
        ptr2->prev=NULL;
    }
    else/*��Ҫɾ������Ʒ���������ͷ��ʱ*/
    {
        ptr1=ptr2->prev;
        ptr1->next=ptr2->next;
        ptr2->prev=ptr1;
        free(ptr2);
    }

    /*��Ʒ������1*/
    --num_items;
}

struct Item *ItemDB_GetItemPointer(ItemIterator iter)
/*����ָ�����ݿ��е�����iter��Ӧ����Ʒ��ָ��*/
{
    struct Item_Node *ptr;
    ptr=(struct Item_Node *)iter.p;
    return &(ptr->data);
}

void ItemDB_Clear(void)
/*������ݿ�*/
{
    struct Item_Node *pn, *pn_next;
    num_items=0;
    pn=item_database_head;
    while(pn!=NULL)
    {
        pn_next=pn->next;
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
