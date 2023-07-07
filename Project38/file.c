#include<stdio.h>
#include<string.h>
#include"read.h"
#include"database.h"
#include"internal.h"
const char *file_header = "database";
const char *student_start_tag_str = "</student>";
const char *course_start_tag_str = "</course>";
const char *student_end_tag_str = "</student>";
const char *student_name_str = "name_";
const char *student_number_str = "number = ";
const char *course_end_tag_str = "</course>";
const char *course_name_str = "name_";
const char *course_number_str = "number = ";
int SaveToFile(const char *file_name)
/*�����ݿⱣ�浽��Ϊfile_name���ļ���*/
/*�ɹ��򷵻�1�����򷵻�0*/
{
    FILE *fp;
    ItemIterator iter1,iter2;
    struct student *s;
    struct course *c;

    /*���ļ�*/
    fp=fopen(file_name,"w");
    if(fp==NULL) return 0;

    /*д�ļ�ͷ*/
    fprintf(fp,"%s\n",file_header);

    /*��������ѧ��*/
    for(iter=GetFirstStudentIterator();Valid(iter);
        iter=GetNextStudentIterator(iter))
        {
            /*��ȡָ��ѧ����ָ��*/
            s=GetStudentPointer(iter1);
            c=GetCoursePointer(iter2);

            fputc('\n',fp);

            /*���ѧ����ʼ��ǩ*/
            fprintf(fp,"%s\n",student_start_tag_str);

            fprintf(fp,"%s%d\n",studet_number_str,p->number);
            fprintf(fp,"%s%s\n",student_name_str,p->name);
            for(int i=0;i<num_course;i++)
                fprintf(fp,"%s\n",p->choice);
            fprintf(fp,"%s%d\n",course_number_str,c->number);
            fprintf(fp,"%s%s\n",course_name_str,c->name);

            /*�����β��ǩ*/
            fprintf(fp,"%s\n",student_end_tag_str);
            fprintf(fp,"%s\n",course_end_tag_str);
        }

    /*�ر��ļ�*/
    return !fclose(fp);
}
int LoadFromFile(const char *file_name){
    FILE *fp;
    char buffer[1024];
    size_t student_number_str_len = strlen(student_number_str);
    size_t student_name_str_len = strlen(student_name_str);
    int in_item_flag = 0; /*�Ƿ�����Ʒ�ڲ��ı�־*/
    struct student student_item;
    size_t course_number_str_len = strlen(course_number_str);
    size_t course_name_str_len = strlen(course_name_str);
    struct course course_item;

    /*���ļ�*/
    fp = fopen(file_name,"r");
    if(fp == NULL) return 0;

    /*����һ�в�����Ƿ����ļ�ͷƥ��*/
    ReadLineFromFile(fp, buffer, sizeof(buffer)-1);
    if(strcmp(buffer,file_header) != 0)
    {
        fclose(fp);
        return 0;
    }

    Clear();
    /*�����ļ�����ֱ���ļ���βΪֹ*/
    while(!feof(fp))
    {
        /*����һ��*/
        ReadLineFromFile(fp, buffer, sizeof(buffer)-1);

        if(in_item_flag)
        {
            /*�Ƿ�ͽ�����ǩ��ƥ��*/
            if(strcmp(buffer,student_end_tag_str) == 0)
                if(strcmp(buffer,course_end_tag_str) == 0)
            {
                in_item_flag = 0;
               int Add_student(const struct student *p_Student);
               int Add_course(const struct course *p_Course);
                continue;
            }

            /*��鵱ǰ���Ƿ�������*/
            if(strncmp(buffer,student_name_str,student_name_str_len) == 0)
            {
                strncpy(student_item.name,buffer+student_name_str_len,NAME_MAX_LEN);
                student_item.name[NAME_MAX_LEN] = '\0';
                continue;
            }
            if(strncmp(buffer,course_name_str,course_name_str_len) == 0)
            {
                strncpy(course_item.name,buffer+course_name_str_len,NAME_MAX_LEN);
                course_item.name[NAME_MAX_LEN] = '\0';
                continue;
            }
            /*��鵱ǰ���Ƿ�����Ʒ���*/
            if(strncmp(buffer,student_number_str,student_number_str_len) == 0)
            {
                sscanf(buffer+student_number_str_len,"%d",&student_item.number);
                continue;
            }
            if(strncmp(buffer,course_number_str,course_number_str_len) == 0)
            {
                sscanf(buffer+course_number_str_len,"%d",&course_item.number);
                continue;
            }
        }
        else
        {
            /*����Ʒ��*/
            /*��鵱ǰ���Ƿ�����Ʒ��ʼ��ǩ*/
            if (strcmp(buffer,student_start_tag_str) == 0)
                if (strcmp(buffer,course_start_tag_str) == 0)
            {
                in_item_flag = 1;
                continue;
            }
        }
    }

    /*�ر��ļ�*/
    return !fclose(fp);
}
