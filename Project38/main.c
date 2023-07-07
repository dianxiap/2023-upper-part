#include<stdio.h>
#include "database.h"
#include "base.h"
#include "internal.h"
#include "read.h"
#include "sort.h"

void UI_addstudent(){
    struct student S;
    int i;
    int j=0;
    printf("输入学生编号\n");
    scanf("%d",&i);
    if(Find_student(i)){
        printf("该编号已经存在\n");
        return ;
    }
    S.num=i;
    printf("请输入该同学名称\n");
    while(getchar()!='\n'){
        S.name[j]=getchar();
        j++;    /*读入信息*/
    }
    S.name[j]='\0';
    Add_student(S);
}
void UI_addcourse(){
    struct course C;
    int i;
    int j=0;
    printf("输入课程编号\n");
    scanf("%d",&i);
    if(Find_course(i)){
        printf("该编号已经存在\n");
        return ;
    }
    C.number=i;
    printf("请输入该课程名称\n");
    while(getchar()!='\n'){
        C.name[j]=getchar();
        j++;    /*读入信息*/
    }
    C.name[j]='\0';
    Add_course(C);
}
void UI_deletestudent(){
if(Empty_student()){
    printf("没有学生，无法执行删除操作\n");
    return ;
}
printf("请输入待删除的学生编号: ");
int i;
scanf("%d",&i);
Iterator iter = Find_student(i);
if(!Find_student(i))
    printf("该学生不存在\n");
    Delete_student(iter);
    printf("删除成功\n");
}
void UI_deletecourse(){
if(Empty_course()){
    printf("没有课程，无法执行删除操作\n");
    return ;
}
printf("请输入待删除的课程编号: ");
int i;
scanf("%d",&i);
Iterator iter = Find_course(i);
if(!Find_course(i))
    printf("该课程不存在\n");
    Delete_course(iter);
    printf("删除成功\n");
}
void UI_findstudent(){
if(Empty_student()){
    printf("没有该学生\n");
    return ;
}
printf("请输入待寻找的学生编号: ");
int i;
scanf("%d",&i);
Iterator iter = Find_student(i);
if(!Find_student(i))
    printf("该学生不存在\n");
    else
        Printf_student(i);/*填坑*/
}
void UI_findcourse(){
if(Empty_course()){
    printf("没有该课程\n");
    return ;
}
printf("请输入待寻找的课程编号: ");
int i;
scanf("%d",&i);
Iterator iter = Find_course(i);
if(!Find_course(i))
    printf("该课程不存在\n");
    else
        Printf_course(i);/*填坑*/
}
void test()/*创建测试数据库*/
{
    int i, j, k;
    struct student Student;
    struct course Course;

    for (i = 0; i < 20; i++)
    {
        Student.num = i + 1;
        Course.number = i + 1;
        for (k = 0; k < 10; k++)
            Student.name[k] = 'A' + srand(123) % 26;
        Student.name[k] = '\0';
        for (j = 0; j < 10; j++)
            Course.name[j] = 'A' + rand(456) % 26;
        Course.name[j] = '\0';
    }
}
int main(){
    /*测试函数*/
    test();
    while(1){
        char c;
        printf("1--添加学生\n");
        printf("2--添加课程\n");
        printf("3--删除学生\n");
        printf("4--删除课程\n");
        printf("5--查找学生\n");
        printf("6--查找课程\n");
        printf("7--选课/退课[Y/N]\n");
        printf("8--载入\n");
        printf("9--保存\n");
        printf("0--退出系统");
        printf("选择将进行的操作\n");
        c=getchar();
        switch(c!='0'){
    case'1':UI_addstudent;break;
    case'2':UI_addcourse();break;
    case'3':UI_deletestudent();break;
    case'4':UI_deletecourse();break;
    case'5':UI_findstudent();break;
    case'6':UI_findcourse();break;
    case'7':choice(int student_number,int course_number);break;
    case'8':LoadFromFile(const char *file_name);break;
    case'9':SaveToFile(const char *file_name);
        }
    }
    return 0;
    }
