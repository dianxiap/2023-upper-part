#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
#define NAME_MAX_LEN 10
/*课程数据库与学生数据库*/
typedef struct student{/*学生信息*/
int num;
char name[NAME_MAX_LEN + 1];
struct student* prev;
struct student* next;
};
typedef struct course{/*课程信息*/
char name[NAME_MAX_LEN + 1];
int number;
struct student* prev;
struct student* next;
};

#endif // BASE_H_INCLUDED
