#define _CRT_SECURE_NO_WARNINGS 1
#ifndef ITEMDATABASE_INTERNAL_H_INCLUDED
#define ITEMDATABASE_INTERNAL_H_INCLUDED

/*��Ʒ���*/
struct Item_Node
{
    struct Item data;/*��Ʒ����*/
    struct Item_Node *prev;/*ָ��ǰһ������ָ��*/
    struct Item_Node *next;/*ָ���һ���ڵ��ָ��*/
};

extern struct Item_Node *item_database_head;
/*��Ʒ���ݿ�����ͷָ����ⲿ����*/

extern struct Item_Node *item_database_tail;
/*��Ʒ���ݿ�����βָ����ⲿ����*/

extern int num_items;/*��Ʒ����*/

#endif // ITEMDATABASE_INTERNAL_H_INCLUDED
