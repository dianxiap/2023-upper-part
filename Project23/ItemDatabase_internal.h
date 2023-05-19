#define _CRT_SECURE_NO_WARNINGS 1
#ifndef ITEMDATABASE_INTERNAL_H_INCLUDED
#define ITEMDATABASE_INTERNAL_H_INCLUDED

/*物品结点*/
struct Item_Node
{
    struct Item data;/*物品数据*/
    struct Item_Node *prev;/*指向前一个结点的指针*/
    struct Item_Node *next;/*指向后一个节点的指针*/
};

extern struct Item_Node *item_database_head;
/*物品数据库链表头指针的外部声明*/

extern struct Item_Node *item_database_tail;
/*物品数据库链表尾指针的外部声明*/

extern int num_items;/*物品总数*/

#endif // ITEMDATABASE_INTERNAL_H_INCLUDED
