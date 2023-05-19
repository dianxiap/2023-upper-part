#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyIOLib.h"
#include "ItemDatabase.h"

void UI_AddItem(void)
/*添加物品*/
{
    ItemIterator iter;
    struct Item temp_item; /*临时物品*/

    /*输入新物品编号*/
    printf("请输入新物品编号：");
    scanf("%d", &temp_item.number);

    /*检查新物品编号是否已经存在*/
    /*如果已经存在则显示错误信息并返回*/
    iter = ItemDB_FindItem(temp_item.number);
    if (ItemDB_IsItemIteratorValid(iter))
    {
        printf("物品已经存在！\n");
        return;
    }

    /*输入新物品名称*/
    printf("请输入新物品名称：");
    while (getchar() != '\n');
    ReadLine(temp_item.name, ITEM_NAME_MAX_LEN);

    /*输入新物品数量*/
    printf("请输入新物品数量：");
    scanf("%d", &temp_item.quantity);

    /*把新物品加入数据库中*/
    if (!ItemDB_AddItem(&temp_item))
    {
        printf("物品添加失败！\n");
    }
}

void UI_DeleteItem(void)
/*删除物品*/
{
    int number;
    ItemIterator iter;

    /*检查数据库是否为空*/
    /*如果为空则显示错误信息并返回*/
    if (ItemDB_IsEmpty())
    {
        printf("数据库为空！\n");
        return;
    }

    /*输入要删除物品的编号*/
    printf("请输入要删除物品的编号：");
    scanf("%d", &number);

    /*检查物品编号是否已经存在*/
    /*如果不存在则显示错误信息并返回*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("物品不存在！\n");
        return;
    }

    /*把物品从数据库中删除*/
    ItemDB_DeleteItem(iter);
}

void UI_SearchItem(void)
/*搜索物品*/
{
    int number;
    ItemIterator iter;

    /*输入物品编号*/
    printf("请输入物品编号：");
    scanf("%d", &number);

    /*检查物品编号是否已经存在*/
    /*如果不存在则显示不存在*/
    /*否则显示物品的名称和数量*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("物品不存在。\n");
    }
    else
    {
        struct Item* p_item;
        p_item = ItemDB_GetItemPointer(iter);
        printf("物品名称：%s\n物品数量：%d\n",
            p_item->name,
            p_item->quantity);
    }
}

void UI_UpdateItem(void)
/*更新物品*/
{
    int number;
    ItemIterator iter;
    char ch;
    struct Item* p_item;

    /*输入物品编号*/
    printf("请输入物品编号：");
    scanf("%d", &number);

    /*检查物品编号是否已经存在*/
    /*如果不存在则显示错误信息并返回*/
    iter = ItemDB_FindItem(number);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("物品不存在！\n");
        return;
    }

    /*获取指向物品的指针*/
    p_item = ItemDB_GetItemPointer(iter);

    /*询问用户是否需要修改名称*/
    /*是则输入新的名称*/
    printf("是否需要修改名称？"
        "(输入y代表是，其他代表否)：");
    while (getchar() != '\n');
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        printf("请输入新的名称：");
        while (getchar() != '\n');
        ReadLine(p_item->name,
            ITEM_NAME_MAX_LEN);
    }
    else if (ch != '\n')
    {
        while (getchar() != '\n');
    }

    /*询问用户是否需要修改数量*/
    /*是则输入新的数量*/
    printf("是否需要修改数量？"
        "(输入y代表是，其他代表否)：");
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        printf("请输入新的数量：");
        scanf("%d", &p_item->quantity);
    }
}

void UI_ClearDatabase(void)
/*清除数据库*/
{
    char ch;

    /*询问用户是否真的要清除数据库*/
    /*是则清除数据库*/
    printf("按y键确认清除数据库，按其他键取消：");
    while (getchar() != '\n');
    ch = getchar();
    if (ch == 'y' || ch == 'Y')
    {
        ItemDB_Clear();
    }
}

void UI_PrintDatabase(void)
/*显示数据库*/
{
    ItemIterator iter;
    struct Item* p_item=NULL;

    /*显示表头*/
    printf("编号      名称                数量\n");

    /*遍历数据库中的每个物品*/
    int n = ItemDB_GetNumItems();
    for (iter = ItemDB_GetFirstItemIterator();
        n--&&ItemDB_IsItemIteratorValid(iter);
        iter = ItemDB_GetNextItemIterator(iter))
    {
        /*获取指向当前物品的指针*/
        p_item = ItemDB_GetItemPointer(iter);

        /*显示当前物品信息*/
        printf("%-10d%-20s%d\n",
            p_item->number,
            p_item->name,
            p_item->quantity);
    }
}

void UI_SaveDatabaseToFile(void)
/*保存文件*/
{
    char file_name[1024];
    int result;

    /*输入文件名*/
    printf("请输入要保存的文件名：");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*将数据库保存到文件*/
    result = ItemDB_SaveToFile(file_name);

    /*检查保存是否成功,并显示相应的信息*/
    if (result)
        printf("保存成功。\n");
    else
        printf("保存失败！\n");
}

void UI_LoadDatabaseFromFile(void)
/*載入文件*/
{
    char file_name[1024];
    int result;

    /*输入文件名*/
    printf("请输入要载入的文件名：");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*将文件载入数据库*/
    result = ItemDB_LoadFromFile(file_name);

    /*检查载入是否成功,并显示相应的信息*/
    if (result)
        printf("载入成功。\n");
    else
        printf("载入失败！\n");
}

void UI_SortDatabase(void)
/*选择排序类型*/
{
    int sort_method, sort_dir;

    printf("1-按名称排序\n");
    printf("2-按编号排序\n");
    printf("3-按数量排序\n");
    printf("请选择排序的方法：");
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

    printf("1-升序排序\n");
    printf("2-降序排序\n");
    printf("请选择排序方向：");
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

/*临时测试函数*/
void CreateTestDatabase(void)
/*创建测试数据库*/
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
        int choice; /*用户所选菜单项编号*/

        /*显示菜单*/
        printf("1-添加物品\n");
        printf("2-删除物品\n");
        printf("3-搜索物品\n");
        printf("4-更新物品\n");
        printf("5-显示数据库\n");
        printf("6-将数据库保存到文件\n");
        printf("7-从文件载入到数据库\n");
        printf("8-将数据库中的数据进行排序\n");
        printf("9-清除数据库\n");
        printf("0-退出\n");

        /*用户选择菜单一项*/
        printf("请输入菜单项编号: ");
        scanf("%d", &choice);

        /*根据用户选择调用相应的功能*/
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
