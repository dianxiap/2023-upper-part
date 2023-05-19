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
/*�����ݿⱣ�浽��Ϊfile_name���ļ���*/
/*�ɹ�����1�����򷵻�0*/
{
    FILE *fp;
    ItemIterator iter;
    struct Item *p;

    /*���ļ�*/
    fp=fopen(file_name,"w");
    if(fp==NULL) return 0;

    /*д�ļ�ͷ*/
    fprintf(fp,"%s\n",file_header);

    /*д�ļ��汾��*/
    fprintf(fp,"%s10\n",file_version);

    /*����������Ʒ*/
    for (iter=ItemDB_GetFirstItemIterator();
        ItemDB_IsItemIteratorValid(iter);
        iter=ItemDB_GetNextItemIterator(iter))
    {
        /*��ȡָ����Ʒ��ָ��*/
        p=ItemDB_GetItemPointer(iter);

        fputc('\n',fp);

        /*�����Ʒ��ʼ��ǩ*/
        fprintf(fp,"%s\n",item_start_tag_str);

        /*�����Ʒ����*/
        fprintf(fp,"%s%d\n",item_number_str,p->number);
        fprintf(fp,"%s%s\n",item_name_str,p->name);
        fprintf(fp,"%s%d\n",item_quantity_str,p->quantity);

        /*�����Ʒ������ǩ*/
        fprintf(fp,"%s\n",item_end_tag_str);
    }

    /*�ر��ļ�*/
    if (fclose(fp)==0)
        return 1;
    else
        return 0;
}

int ItemDB_LoadFromFile(const char *file_name)
/*����Ϊfile_name���ļ����������ݿ�*/
/*�ɹ�����1�����򷵻�0*/
{
    FILE *fp;
    char buffer[1024];
    size_t file_version_len=strlen(file_version);
    size_t item_name_str_len=strlen(item_name_str);
    size_t item_number_str_len=strlen(item_number_str);
    size_t item_quantity_str_len=strlen(item_quantity_str);
    int in_item_flag=0;/*�Ƿ�����Ʒ�ڲ���־*/
    struct Item temp_item;

    /*���ļ�*/
    fp=fopen(file_name,"r");
    if(fp==NULL) return 0;

    /*����һ�в�����Ƿ����ļ�ͷƥ��*/
    ReadLineFromFile(fp,buffer,
        sizeof(buffer)-1);
    if (strcmp(buffer,file_header)!=0)
    {
        fclose(fp);
        return 0;
    }

    /*����һ�в�����Ƿ����ļ�ƥ��*/
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

    /*������ݿ�*/
    ItemDB_Clear();

    /*�����ļ�����ֱ���ļ���βΪֹ*/
    while (!feof(fp))
    {
        /*����һ��*/
        ReadLineFromFile(fp,buffer,sizeof(buffer)-1);

        if (in_item_flag)
        {
            /*����Ʒ��*/
            /*��鵱ǰ���Ƿ�����Ʒ������ǩ*/
            if (strcmp(buffer,item_end_tag_str)==0)
            {
                in_item_flag=0;
                ItemDB_AddItem(&temp_item);
                continue;
            }

            /*��鵱ǰ���Ƿ�Ϊ��Ʒ���*/
            if (strncmp(buffer,item_number_str,
                item_number_str_len)==0)
            {
                sscanf(buffer+item_number_str_len,
                       "%d",&temp_item.number);
                continue;
            }

            /*��鵱ǰ���Ƿ�����Ʒ����*/
            if (strncmp(buffer,item_name_str,item_name_str_len)==0)
            {
                strncpy(temp_item.name,
                       buffer+item_name_str_len,
                       ITEM_NAME_MAX_LEN);
                temp_item.name[ITEM_NAME_MAX_LEN]='\0';
                continue;
            }

            /*��鵱ǰ���Ƿ�Ϊ��Ʒ����*/
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
            /*����Ʒ��*/
            /*��鵱ǰ���Ƿ�����Ʒ��ʼ��ǩ*/
            if (strcmp(buffer,item_start_tag_str)==0)
            {
                in_item_flag=1;
                continue;
            }
        }
    }

    /*�ر��ļ�*/
    if (fclose(fp))
        return 0;
    else
        return 1;
}
