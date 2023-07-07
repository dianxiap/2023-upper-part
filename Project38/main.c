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
    printf("����ѧ�����\n");
    scanf("%d",&i);
    if(Find_student(i)){
        printf("�ñ���Ѿ�����\n");
        return ;
    }
    S.num=i;
    printf("�������ͬѧ����\n");
    while(getchar()!='\n'){
        S.name[j]=getchar();
        j++;    /*������Ϣ*/
    }
    S.name[j]='\0';
    Add_student(S);
}
void UI_addcourse(){
    struct course C;
    int i;
    int j=0;
    printf("����γ̱��\n");
    scanf("%d",&i);
    if(Find_course(i)){
        printf("�ñ���Ѿ�����\n");
        return ;
    }
    C.number=i;
    printf("������ÿγ�����\n");
    while(getchar()!='\n'){
        C.name[j]=getchar();
        j++;    /*������Ϣ*/
    }
    C.name[j]='\0';
    Add_course(C);
}
void UI_deletestudent(){
if(Empty_student()){
    printf("û��ѧ�����޷�ִ��ɾ������\n");
    return ;
}
printf("�������ɾ����ѧ�����: ");
int i;
scanf("%d",&i);
Iterator iter = Find_student(i);
if(!Find_student(i))
    printf("��ѧ��������\n");
    Delete_student(iter);
    printf("ɾ���ɹ�\n");
}
void UI_deletecourse(){
if(Empty_course()){
    printf("û�пγ̣��޷�ִ��ɾ������\n");
    return ;
}
printf("�������ɾ���Ŀγ̱��: ");
int i;
scanf("%d",&i);
Iterator iter = Find_course(i);
if(!Find_course(i))
    printf("�ÿγ̲�����\n");
    Delete_course(iter);
    printf("ɾ���ɹ�\n");
}
void UI_findstudent(){
if(Empty_student()){
    printf("û�и�ѧ��\n");
    return ;
}
printf("�������Ѱ�ҵ�ѧ�����: ");
int i;
scanf("%d",&i);
Iterator iter = Find_student(i);
if(!Find_student(i))
    printf("��ѧ��������\n");
    else
        Printf_student(i);/*���*/
}
void UI_findcourse(){
if(Empty_course()){
    printf("û�иÿγ�\n");
    return ;
}
printf("�������Ѱ�ҵĿγ̱��: ");
int i;
scanf("%d",&i);
Iterator iter = Find_course(i);
if(!Find_course(i))
    printf("�ÿγ̲�����\n");
    else
        Printf_course(i);/*���*/
}
void test()/*�����������ݿ�*/
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
    /*���Ժ���*/
    test();
    while(1){
        char c;
        printf("1--���ѧ��\n");
        printf("2--��ӿγ�\n");
        printf("3--ɾ��ѧ��\n");
        printf("4--ɾ���γ�\n");
        printf("5--����ѧ��\n");
        printf("6--���ҿγ�\n");
        printf("7--ѡ��/�˿�[Y/N]\n");
        printf("8--����\n");
        printf("9--����\n");
        printf("0--�˳�ϵͳ");
        printf("ѡ�񽫽��еĲ���\n");
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
