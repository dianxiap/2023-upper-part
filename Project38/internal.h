#ifndef INTERNAL_H_INCLUDED
#define INTERNAL_H_INCLUDED
/*学生节点*/
struct student_node{
struct student Student;
struct student_node *prev;
struct student_node *next;
};
/*课程节点*/
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
