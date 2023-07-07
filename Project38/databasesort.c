#include<string.h>
#include"sort.h"
#include"database.h"
#include"internal.h"
int StudentNumber_Ascending(const void *p, const void *q)
{
    const struct student *p_item = (const struct student *)p;
    const struct student *q_item = (const struct student *)q;
    if (p_item->number < q_item->number) return -1;
    else if (p_item->number == q_item->number) return 0;
    else return 1;
}
int StudentNumber_Descending(const void *p, const void *q)
{
    const struct student *p_item = (const struct student *)p;
    const struct student *q_item = (const struct student *)q;
    if (p_item->number < q_item->number) return 1;
    else if (p_item->number == q_item->number) return 0;
    else return -1;
}
int CourseNumber_Ascending(const void *p, const void *q)
{
    const struct course *p_item = (const struct course *)p;
    const struct course *q_item = (const struct course *)q;
    if (p_item->number < q_item->number) return -1;
    else if (p_item->number == q_item->number) return 0;
    else return 1;
}
int CourseNumber_Descending(const void *p, const void *q)
{
    const struct course *p_item = (const struct course *)p;
    const struct course *q_item = (const struct course *)q;
    if (p_item->number < q_item->number) return 1;
    else if (p_item->number == q_item->number) return 0;
    else return -1;
}
void Student_Sort(int sort_target, int sort_dir){
    int (*fun_sort)(const void*, const void*);
    if(sort_dir == SORT_ASCENDING)
    {
        if(sort_target == SORT_STUDENT)
            fun_sort = StudentNumber_Ascending;
        else
            fun_sort = StudentNumber_Descending;
    }
    struct student student_database[1024*10];
    int iter = 0;
    struct student_node *pn = student_database_head;
    while(pn != NULL)
    {
        //printf("YY");
        student_database[iter] = pn->Student;
        iter ++;
        pn = pn->next;
    }
    QuickSort(student_database,num_student,sizeof(struct student),fun_sort);
    pn = student_database_head;
    iter = 0;
    while(pn != NULL)
    {
        //printf("II");
        pn->Student = student_database[iter];
        iter ++;
        pn = pn->next;
    }
}
void Course_Sort(int sort_target, int sort_dir){
    int (*fun_sort)(const void*, const void*);
    if(sort_dir == SORT_ASCENDING)
    {
        if(sort_target == SORT_STUDENT)
            fun_sort = CourseNumber_Ascending;
        else
            fun_sort = CourseNumber_Descending;
    }
    struct course course_database[1024*10];
    int iter = 0;
    struct course_node *pn = course_database_head;
    while(pn != NULL)
    {
        //printf("YY");
        course_database[iter] = pn->Course;
        iter ++;
        pn = pn->next;
    }
    QuickSort(course_database,num_items,sizeof(struct course),fun_sort);
    pn = course_database_head;
    iter = 0;
    while(pn != NULL)
    {
        //printf("II");
        pn->Course = course_database[iter];
        iter ++;
        pn = pn->next;
    }
}
