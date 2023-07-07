#include<stdlib.h>
#include<string.h>
#include"database.h"
#include "internal.h"
int num_student = 0;
int num_course = 0;
struct student_node *student_database_head = NULL;
struct student_node *student_database_tail = NULL;
struct course_node *course_database_head = NULL;
struct course_node *course_database_tail = NULL;
ItemIterator GetFirstStudentIterator(void)
{
    ItemIterator iter;
    iter.p = student_database_head;
    return iter;
}
ItemIterator GetFirstCourseIterator(void)
{
    ItemIterator iter;
    iter.p = course_database_head;
    return iter;
}
ItemIterator GetNextStudentIterator(ItemIterator iter){
    ItemIterator iter_next;
    struct student_node *pn;
    pn = (struct student_node*)iter.p;
    iter_next.p = pn -> next;
    return iter_next;
}
ItemIterator GetNextCourseIterator(ItemIterator iter){
    ItemIterator iter_next;
    struct course_node *pn;
    pn = (struct course_node*)iter.p;
    iter_next.p = pn -> next;
    return iter_next;
}
int Valid(ItemIterator iter)
/*检查物品迭代器iter是否有效*/
{
    return iter.p != NULL;
}
ItemIterator Find_student(int student_number){
    ItemIterator iter;
    struct student_node *pn;
    for(pn = student_database_head;  pn != NULL; pn = pn->next)
    {
        if(pn->Student.number == student_number)
            break;
    }
    iter.p = pn;
    return iter;
}
ItemIterator Find_course(int course_number){
    ItemIterator iter;
    struct course_node *pn;
    for(pn = course_database_head;  pn != NULL; pn = pn->next)
    {
        if(pn->Course.number == course_number)
            break;
    }
    iter.p = pn;
    return iter;
}
int Empty_student(void)
{
    return !num_student;
}
int Empty_course(void)
{
    return !num_course;
}
struct student* StudentGetItemPointer(ItemIterator iter){
    return (struct student*)iter.p;
}
struct course* CourseGetItemPointer(ItemIterator iter){
    return (struct course*)iter.p;
}
int Add_student(const struct student *p_Student)
{
    struct student_node *new_Student = (struct student_node*)malloc(sizeof(struct student_node));
    memcpy(&new_Student->Student,p_Student,sizeof(struct student));
    new_Student->next = NULL;

    if(student_database_head != NULL)
    {
        new_Student->prev = student_database_tail;
        student_database_tail->next = new_Student;
    }
    else
    {
        new_Student->prev = NULL;
        student_database_head = new_Student;
    }

    ++num_student;/*物品总数+1*/
    student_database_tail = new_Student;
    return 1;
}
int Add_course(const struct course *p_Course)
{
    struct course_node *new_Course = (struct course_node*)malloc(sizeof(struct course_node));
    memcpy(&new_Course->Course,p_Course,sizeof(struct course));
    new_Course->next = NULL;

    if(course_database_head != NULL)
    {
        new_Course->prev = course_database_tail;
        course_database_tail->next = new_Course;
    }
    else
    {
        new_Course->prev = NULL;
        course_database_head = new_Course;
    }

    ++num_course;/*物品总数+1*/
    course_database_tail = new_Course;
    return 1;
}
void Delete_student(ItemIterator iter){
    struct student_node *pn = (struct student_node*)iter.p;

    if(pn->next == NULL && pn->prev == NULL)
        student_database_tail = student_database_head = NULL;
    else if(pn->next == NULL)
    {
        pn->prev->next = NULL;
        student_database_tail = pn->prev;
    }
    else if(pn->prev == NULL)
    {
        pn->next->prev = NULL;
        student_database_head = pn->next;
    }
    else
    {
        pn->next->prev = pn->prev;
        pn->prev->next = pn->next;
    }
    free(pn);
    /*物品总数-1*/
    -- num_student;

}
void Delete_course(ItemIterator iter){
    struct course_node *pn = (struct course_node*)iter.p;

    if(pn->next == NULL && pn->prev == NULL)
        course_database_tail = course_database_head = NULL;
    else if(pn->next == NULL)
    {
        pn->prev->next = NULL;
        course_database_tail = pn->prev;
    }
    else if(pn->prev == NULL)
    {
        pn->next->prev = NULL;
        course_database_head = pn->next;
    }
    else
    {
        pn->next->prev = pn->prev;
        pn->prev->next = pn->next;
    }
    free(pn);
    /*物品总数-1*/
    -- num_course;

}
int GetNumStudent()
{
    return num_student;
}
int GetNumCourse()
{
    return num_course;
}
ItemIterator choice(int student_number,int course_number){
    ItemIterator iter;
    struct student_node *s;
    struct course_node *c;
    char a;
    printf("选课/退课/退出[Y/N/Q]");
    while(a=='Y'){
    for(s = student_database_head;  s != NULL; s = s->next)
    {
        if(s->Student.number != student_number)
                printf("该学生不存在");
            else
    for(c = course_database_head;  c != NULL; c = c->next)
    {
        if(c->Course.number != course_number)
           printf("该课程不存在");
           else{
           s->Student.choice[course_number-1]='1';
           printf("选课成功");
           }
    }
    }
    }
    while(a=='N'){
        for(s = student_database_head;  s != NULL; s = s->next)
    {
        if(s->Student.number != student_number)
                printf("该学生不存在");
            else
    for(c = course_database_head;  c != NULL; c = c->next)
    {
        if(c->Course.number != course_number)
           printf("该课程不存在");
           else{
           s->Student.choice[course_number-1]='0';
           printf("退课成功");
           }
    }
    }
    }
    while(a=='Q')
        break;
        iter.p=s;
     return iter;
}
void Clear(){
struct student_node *s, *s_next;
struct course_node *c, *c_next;
    for(s = student_database_head; s != NULL;)
        for(c = course_database_head; c != NULL;)
    {
        s_next = s->next;
        free(s);
        s = s_next;
        c_next = c->next;
        free(c);
        c = c_next;
    }
    num_student = 0;
    student_database_head = NULL;
    student_database_tail = NULL;
    num_course = 0;
    course_database_head = NULL;
    course_database_tail = NULL;
}
