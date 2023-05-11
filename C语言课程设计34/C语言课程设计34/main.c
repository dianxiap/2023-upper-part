#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "MyIOLib.h"
#include "Itemdatabase.h"
//#include "Itemdatabase.c"

void UI_SearchItem()/*������Ʒ*/
{/*������Ʒ���*/
    printf("��������Ҫ��ѯ����Ʒ���: ");
    int num; scanf("%d", &num);
    ItemIterator iter;
    iter = ItemDB_FindItem(num);
    if (!ItemDB_IsItemIteratorValid(iter))
        puts("����Ʒ������");/*�����Ʒ����Ƿ��Ѿ�����,�����������ʾ������*/
    else
    {
        struct Item* p_item = ItemDB_GetItemPointer(iter);
        printf("��Ʒ����: %s\n��Ʒ����: %d\n",
            p_item->name, p_item->quantity); /*������ʾ��Ʒ�����ƺ�����*/
    }
}

void UI_UpdateItem(void)/*����*/
{
    printf("��������Ʒ���: ");
    ItemIterator iter;
    int num; scanf("%d", &num); /*������Ʒ���*/
    iter = ItemDB_FindItem(num); /*�����Ʒ����Ƿ��Ѿ�����*/
    if (!ItemDB_IsItemIteratorValid(iter))  /*�������������ʾ������Ϣ������*/
    {
        puts("����Ʒ�����ڣ�"); return;
    }
    struct Item* p_item;
    p_item = ItemDB_GetItemPointer(iter);
    printf("�Ƿ��޸���Ʒ���� [Y/N] :"); /*ѯ���û��Ƿ���Ҫ�޸�����*/
    char choice[10]; scanf("%s", choice);
    if (choice[0] == 'Y') /*���������µ�����*/
    {
        getchar();
        printf("�������µ���Ʒ����: ");
        ReadLine(p_item->name, ITEM_NAME_MAX_LEN + 1);
        puts("����Ʒ�������޸�");
    }
    printf("�Ƿ��޸���Ʒ���� [Y/N] :");/*ѯ���û��Ƿ���Ҫ�޸�����*/
    scanf("%s", choice);
    if (choice[0] == 'Y') /*���������µ�����*/
    {
        printf("�������µ���Ʒ����: ");
        scanf("%d", &p_item->quantity);
        puts("����Ʒ�������޸�");
    }
}
void UI_ClearDatabase(void)/*������ݿ�*/
{
    /*ѯ���û��Ƿ����Ҫ������ݿ�*/
    printf("Are you serious? [Yes/No] ");
    /*����������ݿ�*/
    char choice[100]; scanf("%s", choice);
    if (!strcmp("Yes", choice))
    {
        ItemDB_Clear();
        printf("���ݿ������\n");
    }
    else puts("���ݿ����ʧ��\n");
}
void UI_DeleteItem(void)/*ɾ����Ʒ*/
{
    /*������ݿ��Ƿ�Ϊ��*/
    if (ItemDB_IsEmpty()) /*���Ϊ������ʾ������Ϣ������*/
    {
        printf("���ݿ�Ϊ�գ��޷�ɾ����Ʒ��"); return;
    }

    printf("�������ɾ����Ʒ���: ");
    int num; scanf("%d", &num); /*����Ҫɾ����Ʒ���*/
    /*�������������ʾ������Ϣ������*/
    ItemIterator iter = ItemDB_FindItem(num);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("����Ʒ�����ڻ��ѱ�ɾ��\n"); return;
    }
    ItemDB_DeleteItem(iter);
    printf("*ɾ���ɹ�*\n"); /*����Ʒ�����ݿ���ɾ��*/
}
void UI_AddItem(void)/*�����Ʒ*/
{
    ItemIterator i;
    struct Item temp_item; /*��ʱ��Ʒ*/


    /*��������Ʒ���*/
    printf("����������Ʒ���: ");
    int number;
    scanf("%d", &number);
    i = ItemDB_FindItem(number);
    if (ItemDB_IsItemIteratorValid(i))/*�������Ʒ����Ƿ��Ѿ�����*/
    {
        printf("��Ʒ�Ѿ����ڣ�\n");
        return;
    }/*����Ѿ���������ʾ������Ϣ������*/
    temp_item.number = number;
    /*������Ʒ����*/
    printf("����������Ʒ����: ");
    while (getchar() != '\n');
    ReadLine(temp_item.name, ITEM_NAME_MAX_LEN);
    /*������Ʒ����*/
    printf("����������Ʒ����: ");
    scanf("%d", &temp_item.quantity);
    /*������Ʒ�������ݿ���*/
    if (!ItemDB_AddItem(&temp_item))
    {
        printf("��Ʒ���ʧ�ܣ�\n");
    }
}
void UI_PrintDatabase(void)/*��ʾ���ݿ�*/
{
    if (ItemDB_IsEmpty())
    {
        puts(" ���ݿ�Ϊ�գ�"); return;
    }
    /*��ʾ��ͷ*/
    printf("���	  ����               ����\n");
    /*�������ݿ��е�ÿ����Ʒ*/
    ItemIterator iter;
    struct Item* p_item;
    //int n = ItemDB_GetNumItems();  ??
    for (iter = ItemDB_GetFirstItemIterator(); ItemDB_IsItemIteratorValid(iter); iter = ItemDB_GetNextItemIterator(iter))
    {   /*��ȡָ��ǰ��Ʒ��ָ��*/
        p_item = ItemDB_GetItemPointer(iter);
        /*��ʾ��ǰ��Ʒ��Ϣ*/
        printf("%-10d%-20s%d\n",
            p_item->number,
            p_item->name,
            p_item->quantity);
    }
}

void UI_SaveDatabaseToFile(void)
{
    char file_name[1024];
    int result;

    /*�����ļ���*/
    printf("������Ҫ������ļ���:");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*�����ݿⱣ�浽�ļ�*/
    result = ItemDB_SaveToFile(file_name);

    /*��鱣���Ƿ�ɹ�������ʾ��Ӧ��Ϣ*/
    if (result)
        puts("����ɹ���");
    else
        puts("����ʧ�ܣ�");
}

void UI_LoadDatabaseFromFile(void)
{
    char file_name[1024];
    int result;

    /*�����ļ���*/
    printf("������Ҫ������ļ���:");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*���ļ��������ݿ�*/
    result = ItemDB_LoadFromFile(file_name);

    /*��������Ƿ�ɹ�������ʾ��Ӧ��Ϣ*/
    if (result)
        puts("����ɹ���");
    else
        puts("����ʧ�ܣ�");
}

void UI_SortDatabase(void)
{
    int sort_method, sort_dir;

    printf("1-����Ʒ�������\n");
    printf("2-����Ʒ��������\n");
    printf("3-����Ʒ��������\n");
    printf("��ѡ�����򷽷�: ");
    scanf("%d", &sort_method);

    printf("1-��������\n");
    printf("2-��������\n");
    printf("��ѡ��������: ");
    scanf("%d", &sort_dir);

    ItemDB_Sort(sort_method - 1, sort_dir - 1);
    puts("�������.");

}

/*��ʱ���Ժ���*/
void CreateTestDatabase(void)/*�����������ݿ�*/
{
    int i, k;
    struct Item temp_item;

    srand(123);

    for (i = 0; i < 20; i++)
    {
        temp_item.number = i + 1;
        for (k = 0; k < 8; k++)
            temp_item.name[k] = 'A' + rand() % 26;
        temp_item.name[k] = '\0';
        temp_item.quantity = rand() % 1000;
        ItemDB_AddItem(&temp_item);
    }

}
int main()
{
    CreateTestDatabase();
    while (1)
    {
        char choice;/*�û���ѡ�˵�����*/
        /*��ʾ�˵�*/
        printf(" | 1-�����Ʒ           |\n");
        printf(" | 2-ɾ����Ʒ           |\n");
        printf(" | 3-������Ʒ           |\n");
        printf(" | 4-������Ʒ           |\n");
        printf(" | 5-���ݿ�����         |\n");
        printf(" | 6-��ʾ���ݿ�         |\n");
        printf(" | 7-�����ݿⱣ�浽�ļ� |\n");
        printf(" | 8-���ļ��������ݿ�   |\n");
        printf(" | 9-������ݿ�         |\n");
        printf(" | q-�˳�               |\n");
        /*�û�ѡ��˵�һ��*/
        printf("Please input the number of the menu: ");
        scanf("%c", &choice);
        switch (choice)
        {
        case '1': UI_AddItem(); break;
        case '2': UI_DeleteItem(); break;
        case '3': UI_SearchItem(); break;
        case '4': UI_UpdateItem(); break;
        case '5': UI_SortDatabase(); break;
        case '6': UI_PrintDatabase(); break;
        case '7': UI_SaveDatabaseToFile(); break;
        case '8': UI_LoadDatabaseFromFile(); break;
        case '9': UI_ClearDatabase(); break;
        case 'q': puts("��л�����鱾����\n"); break;
        default: puts("���๦����δ����,�����ڴ� :)\n"); break;
        }
        if (choice == 'q') break;
        while ((choice = getchar()) != '\n');
        /*�����û�ѡ�������Ӧ����*/
    }
    return 0;
}
