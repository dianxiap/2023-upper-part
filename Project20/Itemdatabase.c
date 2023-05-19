#include"Itemdatabase.h"
#include "Itemdatabase_internal.h"
#include<stdlib.h>
#include<string.h>

#if 1
#define ENABLE_LOG
#endif

int num_items = 0;

struct Item_Node *item_database_head = NULL;/*物品数据库链表头指针的外部声明*/
struct Item_Node *item_database_tail = NULL;/*物品数据库链表尾指针的外部声明*/

ItemIterator ItemDB_GetFirstItemIterator(void)
{
    ItemIterator iter;
    iter.p = item_database_head;
    return iter;
}

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter)
/*返回下一个物品的迭代器*/
{
    ItemIterator iter_next;
    struct Item_Node *pn;
    pn = (struct Item_Node*)iter.p;
    iter_next.p = pn -> next;
    return iter_next;
}

int ItemDB_IsItemIteratorValid(ItemIterator iter)
/*检查物品迭代器iter是否有效*/
{
    return iter.p != NULL;
}

ItemIterator ItemDB_FindItem(int item_number)
/*在数据库中搜索编号为item_number的物品*/
/*找到返回物品迭代器*/
/*否则返回一个无效的迭代器*/
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
/*返回指向数据库中迭代器iter对应的物品的指针*/
{
    return (struct Item*)iter.p;
}

int ItemDB_AddItem(const struct Item *p_item)
{
    /*将p_item指向的物品加入数据库中*/
    /*将物品存入数据库结尾*/
    /*成功返回1，否则返回0*/

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

    ++num_items;/*物品总数+1*/
    item_database_tail = new_item;
    return 1;
}

void ItemDB_DeleteItem(ItemIterator iter)
{/*将数据库中索引值为item_index的元素删除*/
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
    /*物品总数-1*/
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
{/*返回物品总数*/
    return num_items;
}
