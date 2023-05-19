#pragma once
#ifndef ITEMDATABASE_INTERNAL_H_INCLUDED
#define ITEMDATABASE_INTERNAL_H_INCLUDED

/*��Ʒ���*/
struct Item_Node
{
    struct Item data; /*��Ʒ����*/
    struct Item_Node* prev; /*ָ��ǰһ������ָ��*/
    struct Item_Node* next; /*ָ���һ������ָ��*/
};

extern struct Item_Node* item_database_head;
/*���ݿ�����ͷָ����ⲿ������ָ�������һ�����*/

extern struct Item_Node* item_database_tail;
/*���ݿ�βָ�룬ָ���������һ�����*/

extern int num_items; /*��Ʒ����*/

#endif // ITEMDATABASE_INTERNAL_H_INCLUDED
