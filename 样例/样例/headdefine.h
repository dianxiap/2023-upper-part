#pragma once
//--ѧ����Ϣ���֣�
#define SIZE_STU 10

/*ѧ����Ϣ�ṹ��*/
typedef struct student_info {
    char stu_ID[9];
    char stu_name[5];
    char sex[9];
    char age[9];
    char collage[9];
    char grade[9];
    char contact[9];
}stu;

//�洢ѧ����Ϣ��˳���
typedef struct student
{
    stu* st;
    int size;
    int capacity;
}Stu;

#define SIZE_COU 10
/*�γ���Ϣ�ṹ��*/
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
/*ѡ�μ�¼�ṹ��*/
typedef struct select {
    int s;//���ѧ����Ϣ�������±�
    int c;//��ſγ���Ϣ�������±�
}sel;

typedef struct Select
{
    int size;
    int capacity;
    sel* sel;
}Sel;