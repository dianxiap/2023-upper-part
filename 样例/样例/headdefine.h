#pragma once
//--学生信息部分：
#define SIZE_STU 10

/*学生信息结构体*/
typedef struct student_info {
    char stu_ID[9];
    char stu_name[5];
    char sex[9];
    char age[9];
    char collage[9];
    char grade[9];
    char contact[9];
}stu;

//存储学生信息的顺序表
typedef struct student
{
    stu* st;
    int size;
    int capacity;
}Stu;

#define SIZE_COU 10
/*课程信息结构体*/
typedef struct course_info {
    char course_ID[9];
    char course_name[9];
    char property[9];
    char period[9];
    char credit[9];
    char time[9];
    int people;
}cou;

typedef struct course
{
    cou* cou;
    int size;
    int capacity;
}Cou;
#define SIZE_SEL 10
/*选课记录结构体*/
typedef struct select {
    int s;//存放学生信息的数组下标
    int c;//存放课程信息的数组下标
}sel;

typedef struct Select
{
    int size;
    int capacity;
    sel* sel;
}Sel;