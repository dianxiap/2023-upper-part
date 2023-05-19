#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "MyIOLib.h"
#include "ItemDatabase.h"
#include "ItemDatabase_internal.h"/*Internal*/

const char *file_header="ItemDatabase";
const char *file_version="version=";
const char *item_start_tag_str="<Item>";
const char *item_end_tag_str="</Item>";
const char *item_name_str="name=";
const char *item_number_str="number=";
const char *item_quantity_str="quantity=";

int ItemDB_SaveToFile(const char *file_name)
/*把数据库保存到名为file_name的文件中*/
/*成功返回1，否则返回0*/
{
    FILE *fp;
    ItemIterator iter;
    struct Item *p;

    /*打开文件*/
    fp=fopen(file_name,"w");
    if(fp==NULL) return 0;

    /*写文件头*/
    fprintf(fp,"%s\n",file_header);

    /*写文件版本号*/
    fprintf(fp,"%s10\n",file_version);

    /*遍历所有物品*/
    for (iter=ItemDB_GetFirstItemIterator();
        ItemDB_IsItemIteratorValid(iter);
        iter=ItemDB_GetNextItemIterator(iter))
    {
        /*获取指向物品的指针*/
        p=ItemDB_GetItemPointer(iter);

        fputc('\n',fp);

        /*输出物品起始标签*/
        fprintf(fp,"%s\n",item_start_tag_str);

        /*输出物品属性*/
        fprintf(fp,"%s%d\n",item_number_str,p->number);
        fprintf(fp,"%s%s\n",item_name_str,p->name);
        fprintf(fp,"%s%d\n",item_quantity_str,p->quantity);

        /*输出物品结束标签*/
        fprintf(fp,"%s\n",item_end_tag_str);
    }

    /*关闭文件*/
    if (fclose(fp)==0)
        return 1;
    else
        return 0;
}

int ItemDB_LoadFromFile(const char *file_name)
/*从名为file_name的文件中载入数据库*/
/*成功返回1，否则返回0*/
{
    FILE *fp;
    char buffer[1024];
    size_t file_version_len=strlen(file_version);
    size_t item_name_str_len=strlen(item_name_str);
    size_t item_number_str_len=strlen(item_number_str);
    size_t item_quantity_str_len=strlen(item_quantity_str);
    int in_item_flag=0;/*是否在物品内部标志*/
    struct Item temp_item;

    /*打开文件*/
    fp=fopen(file_name,"r");
    if(fp==NULL) return 0;

    /*读入一行并检查是否与文件头匹配*/
    ReadLineFromFile(fp,buffer,
        sizeof(buffer)-1);
    if (strcmp(buffer,file_header)!=0)
    {
        fclose(fp);
        return 0;
    }

    /*读入一行并检查是否与文件匹配*/
    ReadLineFromFile(fp,buffer,sizeof(buffer)-1);

    if (strncmp(buffer,file_version,file_version_len)!=0)
    {
        fclose(fp);
        return 0;
    }

    if (strcmp(buffer+file_version_len,"10")!=0)
    {
        fclose(fp);
        return 0;
    }

    /*清空数据库*/
    ItemDB_Clear();

    /*读入文件数据直到文件结尾为止*/
    while (!feof(fp))
    {
        /*读入一行*/
        ReadLineFromFile(fp,buffer,sizeof(buffer)-1);

        if (in_item_flag)
        {
            /*在物品内*/
            /*检查当前行是否是物品结束标签*/
            if (strcmp(buffer,item_end_tag_str)==0)
            {
                in_item_flag=0;
                ItemDB_AddItem(&temp_item);
                continue;
            }

            /*检查当前行是否为物品编号*/
            if (strncmp(buffer,item_number_str,
                item_number_str_len)==0)
            {
                sscanf(buffer+item_number_str_len,
                       "%d",&temp_item.number);
                continue;
            }

            /*检查当前行是否是物品名称*/
            if (strncmp(buffer,item_name_str,item_name_str_len)==0)
            {
                strncpy(temp_item.name,
                       buffer+item_name_str_len,
                       ITEM_NAME_MAX_LEN);
                temp_item.name[ITEM_NAME_MAX_LEN]='\0';
                continue;
            }

            /*检查当前行是否为物品数量*/
            if (strncmp(buffer,item_quantity_str,
                item_quantity_str_len)==0)
            {
                sscanf(buffer+item_quantity_str_len,
                       "%d",&temp_item.quantity);
                continue;
            }

        }
        else
        {
            /*在物品外*/
            /*检查当前行是否是物品开始标签*/
            if (strcmp(buffer,item_start_tag_str)==0)
            {
                in_item_flag=1;
                continue;
            }
        }
    }

    /*关闭文件*/
    if (fclose(fp))
        return 0;
    else
        return 1;
}
