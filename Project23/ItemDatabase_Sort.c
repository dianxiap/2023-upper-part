#define _CRT_SECURE_NO_WARNINGS 1
#include "ItemDatabase.h"
#include "ItemDatabase_internal.h"
#include "MySort.h"
#include <stdlib.h>
#include <string.h>

int CompareByNumber_Ascending(const void *p, const void *q)
/*�������������ıȽϺ���*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;
    if (p_item->number<q_item->number) return -1;
    else if (p_item->number==q_item->number) return 0;
    else return 1;
}

int CompareByNumber_Descending(const void *p, const void *q)
/*����Ž�������ıȽϺ���*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;
    if (p_item->number>q_item->number) return -1;
    else if (p_item->number==q_item->number) return 0;
    else return 1;
}

int CompareByQuantity_Ascending(const void *p, const void *q)
/*��������������ıȽϺ���*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    if (p_item->quantity<q_item->quantity) return -1;
    else if (p_item->quantity==q_item->quantity) return 0;
    else return 1;
}

int CompareByQuantity_Descending(const void *p, const void *q)
/*��������������ıȽϺ���*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    if (p_item->quantity>q_item->quantity) return -1;
    else if (p_item->quantity==q_item->quantity) return 0;
    else return 1;
}

int CompareByName_Ascending(const void *p, const void *q)
/*��������������ıȽϺ���*/
/*�Ƚ��ַ�����strcmp()����,��Ҫ��ͷ�ļ�#include<string.h>*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    return strcmp(p_item->name, q_item->name);
    /*����ֵΪ������0������*/
}

int CompareByName_Descending(const void *p, const void *q)
/*�����ƽ�������ıȽϺ���*/
{
    const struct Item *p_item=(const struct Item *)p;
    const struct Item *q_item=(const struct Item *)q;

    return -strcmp(p_item->name, q_item->name);
	/*����ֵΪ������0������*/
}

void ItemDB_Sort(int sort_method, int sort_dir)
/* �����ݿ��е���Ʒ��������
   sort_method�����򷽷�������ȡ����ֵ֮һ��
     SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
   sort_dir�������򣬿���ȡ����ֵ֮һ��
     SORT_ASCENDING, SORT_DESCENDING */
{
    int (*comp_func)(const void*, const void*)=NULL;
    switch (sort_method)
    {
    case SORT_BY_NUMBER:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByNumber_Ascending;
        else
            comp_func = CompareByNumber_Descending;
        break;
    case SORT_BY_NAME:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByName_Ascending;
        else
            comp_func = CompareByName_Descending;
        break;
    case SORT_BY_QUANTITY:
        if (sort_dir == SORT_ASCENDING)
            comp_func = CompareByQuantity_Ascending;
        else
            comp_func = CompareByQuantity_Descending;
        break;
    }

    int num_items=ItemDB_GetNumItems();
    /*��̬������������*/
    struct Item *temp_items=(struct Item *)malloc(num_items*sizeof(struct Item));

    /*����һ����ʱ���*/
    struct Item_Node* temp = item_database_head;
    
    int i=0;
   
    /*���������ݿ�����������*/
    while(temp!=NULL)
    {
        temp_items[i]=temp->data;
        i++;
        temp=temp->next;
    }
    if(comp_func!=NULL)
        QuickSort(temp_items,num_items,sizeof(struct Item), comp_func);

    /*������������ݵ�����*/
    temp=item_database_head;
    i = 0;
    while(temp!=NULL)
    {
        temp->data=temp_items[i];
        i++;
        temp=temp->next;
    }

    free(temp_items);



}
