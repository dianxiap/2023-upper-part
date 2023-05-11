#pragma once
#ifndef ITEMDATABASE_H_INCLUDED
#define ITEMDATABASE_H_INCLUDED

#define SORT_BY_NUMBER    0 /*���������*/
#define SORT_BY_NAME      1 /*����������*/
#define SORT_BY_QUANTITY  2 /*����������*/
#define SORT_ASCENDING  0 /*����������*/
#define SORT_DESCENDING 1 /*����������*/

#define ITEM_NAME_MAX_LEN 64/*��Ʒ���Ƶ���󳤶�*/


struct Item
{
    int number;/*���*/
    char name[ITEM_NAME_MAX_LEN + 1];/*����*/
    int quantity; /*����*/
};

typedef struct
{
    int i;/*��Ʒ�������е�����*/
}ItemIterator;/*��Ʒ������*/

ItemIterator ItemDB_GetFirstItemIterator(void);
/*���ص�һ����Ʒ�ĵ�����*/

ItemIterator ItemDB_GetNextItemIterator(ItemIterator iter);
/*������һ����Ʒ�ĵ�����*/

int ItemDB_IsItemIteratorValid(ItemIterator iter);
/*�����Ʒ������iter�Ƿ���Ч����Ч�򷵻�1�����򷵻�0*/

ItemIterator ItemDB_FindItem(int item_number);
/*�����ݿ����������Ϊitem_number����Ʒ*/
/*�ҵ�������Ʒ������*/
/*���򷵻�һ����Ч�ĵ�����*/
int ItemDB_IsEmpty(void);

struct Item* ItemDB_GetItemPointer(ItemIterator iter);
/*����ָ�����ݿ��е�����iter��Ӧ����Ʒ��ָ��*/

int ItemDB_AddItem(const struct Item* p_item);
/*��p_itemָ�����Ʒ�������ݿ���*/
    /*����Ʒ�������ݿ��β*/
    /*�ɹ�����1�����򷵻�0*/

void ItemDB_DeleteItem(ItemIterator iter);
/*�����ݿ��е�����iter��Ӧ����Ʒɾ��*/
    /*��Ʒ����-1*/

void ItemDB_Clear(void);/*������ݿ�*/

int ItemDB_GetNumItems();

int ItemDB_SaveToFile(const char* file_name);
/*�����ݿⱣ�浽��Ϊfile_name���ļ���*/
/*�ɹ��򷵻�1�����򷵻�0*/

int ItemDB_LoadFromFile(const char* file_name);
/*����Ϊfile_name���ļ��������ݿ�*/
/*�ɹ��򷵻�1�����򷵻�0*/

void ItemDB_Sort(int sort_method, int sort_dir);
/* �����ݿ��е���Ʒ��������
   sort_method�����򷽷�������ȡ����ֵ֮һ��
     SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
   sort_dir�������򣬿���ȡ����ֵ֮һ��
     SORT_ASCENDING, SORT_DESCENDING */

#endif // ITEMDATABASE_H_INCLUDED
