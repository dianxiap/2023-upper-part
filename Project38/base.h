#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
#define NAME_MAX_LEN 10
/*�γ����ݿ���ѧ�����ݿ�*/
typedef struct student{/*ѧ����Ϣ*/
int num;
char name[NAME_MAX_LEN + 1];
struct student* prev;
struct student* next;
};
typedef struct course{/*�γ���Ϣ*/
char name[NAME_MAX_LEN + 1];
int number;
struct student* prev;
struct student* next;
};

#endif // BASE_H_INCLUDED
