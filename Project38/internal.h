#ifndef INTERNAL_H_INCLUDED
#define INTERNAL_H_INCLUDED
/*ѧ���ڵ�*/
struct student_node{
struct student Student;
struct student_node *prev;
struct student_node *next;
};
/*�γ̽ڵ�*/
struct course_node{
struct course Course;
struct course_node *prev;
struct course_node *next;
};
extern struct student_node *student_database_head;
extern struct student_node *student_database_tail;
extern struct student_node *course_database_head;
extern struct student_node *course_database_tail;
#endif // INTERNAL_H_INCLUDED
