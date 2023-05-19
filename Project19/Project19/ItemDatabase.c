#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "ItemDatabase_internal.h"

#if 1 /*1改成0，则数据容量的变化不输出*/
#define ENABLE_LOG
#endif

struct Item_Node *item_database_head=NULL;
    /*数据库链表头指针的外部声明，指向链表第一个结点*/

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

ItemIterator
ItemDB_GetNextItemIterator(
    ItemIterator iter)
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
/*检查数据库是否为空，是则返回1，否则返回0*/
{
    return num_items==0;
}

int ItemDB_AddItem(
    const struct Item *p_item)
/*将p_item指向的物品加入数据库中*/
/*成功返回1，否则返回0*/
{
    /*定义一个节点的新空间*/
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

    ++num_items;/*物品总数+1*/
    item_database_tail = new_p;
    return 1;

}

void ItemDB_DeleteItem(ItemIterator iter)
/*将数据库中迭代器iter对应的物品删除*/
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


    free(pn); //释放new_p指向的节点所占用的内存空间
    num_items--;
}

struct Item *ItemDB_GetItemPointer(
    ItemIterator iter)
/*返回指向数据库中迭代器iter对应的物品的指针*/
{
    struct Item_Node *new_p=(struct Item_Node *)iter.p;
    return &(new_p->data);
}

void ItemDB_Clear(void)
/*清空数据库*/
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
/*返回物品总数*/
{
    return num_items;
}
