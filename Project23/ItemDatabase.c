#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "ItemDatabase_internal.h"

#if 1
#define ENABLE_LOG
#endif

struct Item_Node *item_database_head=NULL;
/*数据库头指针，指向链表第一个结点*/

struct Item_Node *item_database_tail=NULL;
/*数据库尾指针，指向链表最后一个结点*/

int num_items=0; /*物品总数*/

ItemIterator ItemDB_GetFirstItemIterator(void)
/*返回第一个物品的迭代器*/
{
    ItemIterator iter;
    iter.p=item_database_head;
    return iter;
}

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
/*返回下一个物品的迭代器*/
{
    ItemIterator iter_next;
    struct Item_Node *pn;
    pn=(struct Item_Node *)iter.p;
    iter_next.p=pn->next;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*检查物品迭代器iter是否有效*/
/*有效返回1，否则返回0*/
{
    return iter.p!=NULL;
}

ItemIterator ItemDB_FindItem(int item_number)
/*在数据库中搜索编号为item_number的物品*/
/*找到则返回物品的迭代器*/
/*否则返回一个无效的迭代器*/
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
/*检查数据库是否为空，是则返回1，否则返回0*/
{
    if(num_items==0)
		return 1;
	else
        return 0;
}

int ItemDB_AddItem(const struct Item *p_item)
/*将p_item指向的物品加入数据库中*/
/*成功返回1，否则返回0*/
{
    /*创建一个新的结点*/
    struct Item_Node *ptr;
    ptr=(struct Item_Node *)malloc(sizeof(struct Item_Node));

    /*ptr存物品的数据*/
    ptr->data=*p_item;

    /*判断新节点是否为空*/
    if(item_database_head == NULL)
        item_database_head=item_database_tail=ptr;
    else
    {
        /*把新结点加入到链表中*/
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
    /*创建2个新的结点*/
    struct Item_Node *ptr1,*ptr2;

    /*强制类型转换*/
    ptr2=(struct Item_Node *)iter.p;

    /*检查迭代器是否有效*/
    if(!ItemDB_IsItemIteratorValid(iter))
    {
        printf("物品不存在！");
        return;
    }
    else if(ptr2==item_database_head)/*当要删除的物品在链表的头部时*/
    {
        item_database_head=item_database_head->next;
        ptr2->prev=NULL;
    }
    else/*当要删除的物品不在链表的头部时*/
    {
        ptr1=ptr2->prev;
        ptr1->next=ptr2->next;
        ptr2->prev=ptr1;
        free(ptr2);
    }

    /*物品总数减1*/
    --num_items;
}

struct Item *ItemDB_GetItemPointer(ItemIterator iter)
/*返回指向数据库中迭代器iter对应的物品的指针*/
{
    struct Item_Node *ptr;
    ptr=(struct Item_Node *)iter.p;
    return &(ptr->data);
}

void ItemDB_Clear(void)
/*清空数据库*/
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
/*返回物品总数*/
{
    return num_items;
}
