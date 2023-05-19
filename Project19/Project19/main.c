#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyIOLib.h"
#include "ItemDatabase.h"

void UI_AddItem(void)
/*�����Ʒ*/
{
    ItemIterator iter;
    struct Item temp_item; /*��ʱ��Ʒ*/

    /*��������Ʒ���*/
    printf("����������Ʒ��ţ�");
    scanf("%d", &temp_item.number);

    /*�������Ʒ����Ƿ��Ѿ�����*/
    /*����Ѿ���������ʾ������Ϣ������*/
    iter = ItemDB_FindItem(temp_item.number);
    if (ItemDB_IsItemIteratorValid(iter))
    {
        printf("��Ʒ�Ѿ����ڣ�\n");
        return;
    }

    /*��������Ʒ����*/
    printf("����������Ʒ���ƣ�");
    while (getchar() != '\n');
    ReadLine(temp_item.name, ITEM_NAME_MAX_LEN);

    /*��������Ʒ����*/
    printf("����������Ʒ������");
    scanf("%d", &temp_item.quantity);

    /*������Ʒ�������ݿ���*/
    if (!ItemDB_AddItem(&temp_item))
    {
        printf("��Ʒ���ʧ�ܣ�\n");
    }
}

void UI_DeleteItem(void)
/*ɾ����Ʒ*/
{
    int number;
    ItemIterator iter;

    /*������ݿ��Ƿ�Ϊ��*/
    /*���Ϊ������ʾ������Ϣ������*/
    if (ItemDB_IsEmpty())
    {
        printf("���ݿ�Ϊ�գ�\n");
        return;
    }

    /*����Ҫɾ����Ʒ�ı��*/
    printf("������Ҫɾ����Ʒ�ı�ţ�");
    scanf("%d", &number);

    /*�����Ʒ����Ƿ��Ѿ�����*/
    /*�������������ʾ������Ϣ������*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("��Ʒ�����ڣ�\n");
        return;
    }

    /*����Ʒ�����ݿ���ɾ��*/
    ItemDB_DeleteItem(iter);
}

void UI_SearchItem(void)
/*������Ʒ*/
{
    int number;
    ItemIterator iter;

    /*������Ʒ���*/
    printf("��������Ʒ��ţ�");
    scanf("%d", &number);

    /*�����Ʒ����Ƿ��Ѿ�����*/
    /*�������������ʾ������*/
    /*������ʾ��Ʒ�����ƺ�����*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("��Ʒ�����ڡ�\n");
    }
    else
    {
        struct Item* p_item;
        p_item = ItemDB_GetItemPointer(iter);
        printf("��Ʒ���ƣ�%s\n��Ʒ������%d\n",
            p_item->name,
            p_item->quantity);
    }
}

void UI_UpdateItem(void)
/*������Ʒ*/
{
    int number;
    ItemIterator iter;
    char ch;
    struct Item* p_item;

    /*������Ʒ���*/
    printf("��������Ʒ��ţ�");
    scanf("%d", &number);

    /*�����Ʒ����Ƿ��Ѿ�����*/
    /*�������������ʾ������Ϣ������*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("��Ʒ�����ڣ�\n");
        return;
    }

    /*��ȡָ����Ʒ��ָ��*/
    p_item = ItemDB_GetItemPointer(iter);

    /*ѯ���û��Ƿ���Ҫ�޸�����*/
    /*���������µ�����*/
    printf("�Ƿ���Ҫ�޸����ƣ�"
        "(����y�����ǣ����������)��");
    while (getchar() != '\n');
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        printf("�������µ����ƣ�");
        while (getchar() != '\n');
        ReadLine(p_item->name,
            ITEM_NAME_MAX_LEN);
    }
    else if (ch != '\n')
    {
        while (getchar() != '\n');
    }

    /*ѯ���û��Ƿ���Ҫ�޸�����*/
    /*���������µ�����*/
    printf("�Ƿ���Ҫ�޸�������"
        "(����y�����ǣ����������)��");
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        printf("�������µ�������");
        scanf("%d", &p_item->quantity);
    }
}

void UI_ClearDatabase(void)
/*������ݿ�*/
{
    char ch;

    /*ѯ���û��Ƿ����Ҫ������ݿ�*/
    /*����������ݿ�*/
    printf("��y��ȷ��������ݿ⣬��������ȡ����");
    while (getchar() != '\n');
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        ItemDB_Clear();
    }
}

void UI_PrintDatabase(void)
/*��ʾ���ݿ�*/
{
    ItemIterator iter;
    struct Item* p_item=NULL;

    /*��ʾ��ͷ*/
    printf("���      ����                ����\n");

    /*�������ݿ��е�ÿ����Ʒ*/
    int n = ItemDB_GetNumItems();
    for (iter = ItemDB_GetFirstItemIterator();
        n--&&ItemDB_IsItemIteratorValid(iter);
        iter = ItemDB_GetNextItemIterator(iter))
    {
        /*��ȡָ��ǰ��Ʒ��ָ��*/
        p_item = ItemDB_GetItemPointer(iter);

        /*��ʾ��ǰ��Ʒ��Ϣ*/
        printf("%-10d%-20s%d\n",
            p_item->number,
            p_item->name,
            p_item->quantity);
    }
}

void UI_SaveDatabaseToFile(void)
/*�����ļ�*/
{
    char file_name[1024];
    int result;

    /*�����ļ���*/
    printf("������Ҫ������ļ�����");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*�����ݿⱣ�浽�ļ�*/
    result = ItemDB_SaveToFile(file_name);

    /*��鱣���Ƿ�ɹ�,����ʾ��Ӧ����Ϣ*/
    if (result)
        printf("����ɹ���\n");
    else
        printf("����ʧ�ܣ�\n");
}

void UI_LoadDatabaseFromFile(void)
/*�d���ļ�*/
{
    char file_name[1024];
    int result;

    /*�����ļ���*/
    printf("������Ҫ������ļ�����");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*���ļ��������ݿ�*/
    result = ItemDB_LoadFromFile(file_name);

    /*��������Ƿ�ɹ�,����ʾ��Ӧ����Ϣ*/
    if (result)
        printf("����ɹ���\n");
    else
        printf("����ʧ�ܣ�\n");
}

void UI_SortDatabase(void)
/*ѡ����������*/
{
    int sort_method, sort_dir;

    printf("1-����������\n");
    printf("2-���������\n");
    printf("3-����������\n");
    printf("��ѡ������ķ�����");
    scanf("%d", &sort_method);
    switch (sort_method)
    {
    case 1:sort_method = SORT_BY_NAME;
        break;
    case 2:sort_method = SORT_BY_NUMBER;
        break;
    case 3:sort_method = SORT_BY_QUANTITY;
        break;
    }

    printf("1-��������\n");
    printf("2-��������\n");
    printf("��ѡ��������");
    scanf("%d", &sort_dir);
    switch (sort_dir)
    {
    case 1:sort_dir = SORT_ASCENDING;
        break;
    case 2:sort_dir = SORT_DESCENDING;
        break;
    }

    ItemDB_Sort(sort_method, sort_dir);

}

/*��ʱ���Ժ���*/
void CreateTestDatabase(void)
/*�����������ݿ�*/
{
    int i, k;
    struct Item temp_item;

    srand(123);

    for (i = 0; i < 20; ++i)
    {
        temp_item.number = i + 1;
        temp_item.quantity = rand() % 1000;
        for (k = 0; k < 8; ++k)
            temp_item.name[k] = 'A' + rand() % 26;
        temp_item.name[k] = '\0';
        ItemDB_AddItem(&temp_item);
    }
}


int main()
{
    CreateTestDatabase();

    while (1)
    {
        int choice; /*�û���ѡ�˵�����*/

        /*��ʾ�˵�*/
        printf("1-�����Ʒ\n");
        printf("2-ɾ����Ʒ\n");
        printf("3-������Ʒ\n");
        printf("4-������Ʒ\n");
        printf("5-��ʾ���ݿ�\n");
        printf("6-�����ݿⱣ�浽�ļ�\n");
        printf("7-���ļ����뵽���ݿ�\n");
        printf("8-�����ݿ��е����ݽ�������\n");
        printf("9-������ݿ�\n");
        printf("0-�˳�\n");

        /*�û�ѡ��˵�һ��*/
        printf("������˵�����: ");
        scanf("%d", &choice);

        /*�����û�ѡ�������Ӧ�Ĺ���*/
        if (choice == 0) break;
        switch (choice)
        {
        case 1: UI_AddItem(); break;
        case 2: UI_DeleteItem(); break;
        case 3: UI_SearchItem(); break;
        case 4: UI_UpdateItem(); break;
        case 5: UI_PrintDatabase(); break;
        case 6: UI_SaveDatabaseToFile(); break;
        case 7: UI_LoadDatabaseFromFile(); break;
        case 8: UI_SortDatabase(); break;
        case 9: UI_ClearDatabase(); break;

        }
    }

    return 0;
}
