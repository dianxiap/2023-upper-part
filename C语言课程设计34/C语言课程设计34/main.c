#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "MyIOLib.h"
#include "Itemdatabase.h"
//#include "Itemdatabase.c"

void UI_SearchItem()/*搜索物品*/
{/*输入物品编号*/
    printf("请输入需要查询的物品编号: ");
    int num; scanf("%d", &num);
    ItemIterator iter;
    iter = ItemDB_FindItem(num);
    if (!ItemDB_IsItemIteratorValid(iter))
        puts("该物品不存在");/*检查物品编号是否已经存在,如果不存在显示不存在*/
    else
    {
        struct Item* p_item = ItemDB_GetItemPointer(iter);
        printf("物品名称: %s\n物品数量: %d\n",
            p_item->name, p_item->quantity); /*否则显示物品的名称和数量*/
    }
}

void UI_UpdateItem(void)/*更新*/
{
    printf("请输入物品编号: ");
    ItemIterator iter;
    int num; scanf("%d", &num); /*输入物品编号*/
    iter = ItemDB_FindItem(num); /*检查物品编号是否已经存在*/
    if (!ItemDB_IsItemIteratorValid(iter))  /*如果不存在则显示错误信息并返回*/
    {
        puts("该物品不存在！"); return;
    }
    struct Item* p_item;
    p_item = ItemDB_GetItemPointer(iter);
    printf("是否修改物品名称 [Y/N] :"); /*询问用户是否需要修改名称*/
    char choice[10]; scanf("%s", choice);
    if (choice[0] == 'Y') /*是则输入新的名称*/
    {
        getchar();
        printf("请输入新的物品名称: ");
        ReadLine(p_item->name, ITEM_NAME_MAX_LEN + 1);
        puts("该物品名称已修改");
    }
    printf("是否修改物品数量 [Y/N] :");/*询问用户是否需要修改数量*/
    scanf("%s", choice);
    if (choice[0] == 'Y') /*是则输入新的数量*/
    {
        printf("请输入新的物品数量: ");
        scanf("%d", &p_item->quantity);
        puts("该物品数量已修改");
    }
}
void UI_ClearDatabase(void)/*清除数据库*/
{
    /*询问用户是否真的要清除数据库*/
    printf("Are you serious? [Yes/No] ");
    /*是则清除数据库*/
    char choice[100]; scanf("%s", choice);
    if (!strcmp("Yes", choice))
    {
        ItemDB_Clear();
        printf("数据库已清空\n");
    }
    else puts("数据库清除失败\n");
}
void UI_DeleteItem(void)/*删除物品*/
{
    /*检查数据库是否为空*/
    if (ItemDB_IsEmpty()) /*如果为空则显示错误信息并返回*/
    {
        printf("数据库为空，无法删除物品！"); return;
    }

    printf("请输入待删除物品编号: ");
    int num; scanf("%d", &num); /*输入要删除物品编号*/
    /*如果不存在则显示错误信息并返回*/
    ItemIterator iter = ItemDB_FindItem(num);
    if (!ItemDB_IsItemIteratorValid(iter))
    {
        printf("该物品不存在或已被删除\n"); return;
    }
    ItemDB_DeleteItem(iter);
    printf("*删除成功*\n"); /*把物品从数据库中删除*/
}
void UI_AddItem(void)/*添加物品*/
{
    ItemIterator i;
    struct Item temp_item; /*临时物品*/


    /*输入新物品编号*/
    printf("请输入新物品编号: ");
    int number;
    scanf("%d", &number);
    i = ItemDB_FindItem(number);
    if (ItemDB_IsItemIteratorValid(i))/*检查新物品编号是否已经存在*/
    {
        printf("物品已经存在！\n");
        return;
    }/*如果已经存在则显示错误信息并返回*/
    temp_item.number = number;
    /*输入物品名称*/
    printf("请输入新物品名称: ");
    while (getchar() != '\n');
    ReadLine(temp_item.name, ITEM_NAME_MAX_LEN);
    /*输入物品数量*/
    printf("请输入新物品数量: ");
    scanf("%d", &temp_item.quantity);
    /*把新物品加入数据库中*/
    if (!ItemDB_AddItem(&temp_item))
    {
        printf("物品添加失败！\n");
    }
}
void UI_PrintDatabase(void)/*显示数据库*/
{
    if (ItemDB_IsEmpty())
    {
        puts(" 数据库为空！"); return;
    }
    /*显示表头*/
    printf("编号	  名称               数量\n");
    /*遍历数据库中的每个物品*/
    ItemIterator iter;
    struct Item* p_item;
    //int n = ItemDB_GetNumItems();  ??
    for (iter = ItemDB_GetFirstItemIterator(); ItemDB_IsItemIteratorValid(iter); iter = ItemDB_GetNextItemIterator(iter))
    {   /*获取指向当前物品的指针*/
        p_item = ItemDB_GetItemPointer(iter);
        /*显示当前物品信息*/
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

    /*输入文件名*/
    printf("请输入要保存的文件名:");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*将数据库保存到文件*/
    result = ItemDB_SaveToFile(file_name);

    /*检查保存是否成功，并显示相应信息*/
    if (result)
        puts("保存成功！");
    else
        puts("保存失败！");
}

void UI_LoadDatabaseFromFile(void)
{
    char file_name[1024];
    int result;

    /*输入文件名*/
    printf("请输入要载入的文件名:");
    while (getchar() != '\n');
    ReadLine(file_name, sizeof(file_name) - 1);

    /*从文件载入数据库*/
    result = ItemDB_LoadFromFile(file_name);

    /*检查载入是否成功，并显示相应信息*/
    if (result)
        puts("载入成功！");
    else
        puts("载入失败！");
}

void UI_SortDatabase(void)
{
    int sort_method, sort_dir;

    printf("1-按物品编号排序\n");
    printf("2-按物品名称排序\n");
    printf("3-按物品数量排序\n");
    printf("请选择排序方法: ");
    scanf("%d", &sort_method);

    printf("1-升序排序\n");
    printf("2-降序排序\n");
    printf("请选择排序方向: ");
    scanf("%d", &sort_dir);

    ItemDB_Sort(sort_method - 1, sort_dir - 1);
    puts("排序完成.");

}

/*临时测试函数*/
void CreateTestDatabase(void)/*创建测试数据库*/
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
        char choice;/*用户所选菜单项编号*/
        /*显示菜单*/
        printf(" | 1-添加物品           |\n");
        printf(" | 2-删除物品           |\n");
        printf(" | 3-搜索物品           |\n");
        printf(" | 4-更新物品           |\n");
        printf(" | 5-数据库排序         |\n");
        printf(" | 6-显示数据库         |\n");
        printf(" | 7-将数据库保存到文件 |\n");
        printf(" | 8-从文件载入数据库   |\n");
        printf(" | 9-清除数据库         |\n");
        printf(" | q-退出               |\n");
        /*用户选择菜单一项*/
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
        case 'q': puts("感谢您体验本程序\n"); break;
        default: puts("更多功能暂未开启,敬请期待 :)\n"); break;
        }
        if (choice == 'q') break;
        while ((choice = getchar()) != '\n');
        /*根据用户选择调用相应功能*/
    }
    return 0;
}
