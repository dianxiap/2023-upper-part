#define _CRT_SECURE_NO_WARNINGS 1
#include "student.h"

void init_stu(Stu *pc)
{
    assert(pc);
    stu* ptr = (stu*)malloc(sizeof(stu) * SIZE_STU);
    if (ptr == NULL)
    {
        perror("initstu fail");
        return;
    }
    pc->st = ptr;
    pc->capacity = SIZE_STU;
    pc->size = -1;

    //LordStu(pc);
}
void stu_operate(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n-------------------------欢迎进入选课系统！----------------------");
    printf("\n\n                 请选择你要对学生记录进行的操作：");
    printf("\n\n                             1.添加");
    printf("\n                             2.查询");
    printf("\n                             3.显示");
    printf("\n                             4.返回主页面");
    printf("\n                                                      ");
    printf("\n                        请输入：");
    int i;
    scanf("%d", &i);
    system("cls");
    switch (i) {
    case 1://添加学生信息 
        input_stu(spc, cpc, lpc);
        break;
    case 2://查询学生信息 
        search_stu(spc, cpc, lpc);
        break;
    case 3://显示所有学生信息
        show_stu(spc, cpc, lpc);
        break;
    case 4:
        home(spc,cpc,lpc);
        break;
    }
}
void input_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    char flag;
    FILE* fp;
    //--判断文件是否为空
    fp = fopen("student.txt", "a+");
    flag = fgetc(fp);
    if (flag == EOF) {
        fprintf(fp, "学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式\n");
    }
    fclose(fp);
    //--
    fp = fopen("student.txt", "a+");
    if (fp == NULL) {
        printf("打开文件失败！");
        system("cls");
        stu_operate(spc, cpc, lpc);
    }
    printf("学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式\n");
    while (1) {
        spc->size++;
        scanf("%s %s %s %s %s %s %s", &spc->st[spc->size].stu_ID, &spc->st[spc->size].stu_name, &spc->st[spc->size].sex, 
            &spc->st[spc->size].age, &spc->st[spc->size].collage, &spc->st[spc->size].grade, &spc->st[spc->size].contact);
        //--数据查重
        int h;
        for (h = 0; h < spc->size; h++) {
            if (spc->size == 0) break;//第一条数据不需要查重
            if (strcmp(spc->st[h].stu_ID, spc->st[spc->size].stu_ID) == 0) {
                printf("该学号已存在，请重新输入！\n");
                scanf("%s %s %s %s %s %s %s", &spc->st[spc->size].stu_ID, &spc->st[spc->size].stu_name, &spc->st[spc->size].sex,
                    &spc->st[spc->size].age, &spc->st[spc->size].collage, &spc->st[spc->size].grade, &spc->st[spc->size].contact);
                h = -1;
            }
        }
        //--
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",  spc->st[spc->size].stu_ID, spc->st[spc->size].stu_name, spc->st[spc->size].sex,
            spc->st[spc->size].age, spc->st[spc->size].collage, spc->st[spc->size].grade, spc->st[spc->size].contact);
        printf("\n录入成功，继续录入输入y，返回上一级请按任意键：");
        fflush(stdin);
        scanf("%c", &flag);
        fclose(fp);
        if (flag != 'y' && 'Y') break;
        fp = fopen("student.txt", "a");
       
    }
    renew_stu(spc);
    system("cls");
    stu_operate(spc, cpc, lpc);
}
/*查询学生信息*/
void search_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    printf("\n请选择查询方式：");
    printf("\n  1.学号查询");
    printf("\n  2.姓名查询");
    printf("\n请选择：");
    int h;
    scanf(" %d", &h);
    switch (h) {
    case 1:
        search_stu_id(spc, cpc, lpc);
        break;
    case 2:
        search_stu_name(spc, cpc, lpc);
        break;

    }
}
/*学号查询*/
void search_stu_id(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char id[9] = { 0 };
    printf("\n输入学生的学号:");
    fflush(stdin);
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {
            system("cls");
            printf("查找成功!");
            printf("\n\n\t学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式");
            printf("\n\t-----------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID,&spc->st[h].stu_name, spc->st[h].sex,
                spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
            system("pause");
            system("cls");
            stu_operate(spc, cpc, lpc);
        }
    }
    system("cls");
    printf("没有此学号！\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}
/*姓名查询*/
void search_stu_name(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char name[9] = { 0 };
    printf("\n输入学生的姓名:");
    fflush(stdin);
    scanf("%s", name);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_name, name) == 0) {
            system("cls");
            printf("查找成功!");
            printf("\n\n\t学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID, &spc->st[h].stu_name, spc->st[h].sex,
                spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
            system("pause");
            system("cls");
            stu_operate(spc, cpc, lpc);
        }
    }
    system("cls");
    printf("没有此姓名！");
    system("pause");
    system("cls");
    stu_operate(spc, cpc, lpc);
}
/*显示所有学生信息*/
void show_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    int h;
    if (spc->size == -1) {
        printf("\n还没有录入信息！\n");
        system("pause");
        system("cls");
        stu_operate(spc, cpc, lpc);
    }
    system("cls");
    printf("\n\n\t学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式");
    printf("\n\t---------------------------------------------------------");
    for (h = 0; h <= spc->size; h++) {
        printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID, &spc->st[h].stu_name, spc->st[h].sex,
            spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
    }
    //
    fflush(stdin);
    printf("\n\t1.修改");
    printf("\n\t2.删除");
    printf("\n\t3.返回");
    printf("\n\n  选择要进行的操作：");
    int flag;
    fflush(stdin);
    scanf("%d", &flag);
    switch (flag) {
    case 1:
        edit_stu(spc, cpc, lpc);
        break;
    case 2:
        delete_stu(spc, cpc, lpc);
        break;
    default:
        system("cls");
        stu_operate(spc, cpc, lpc);
        break;

    }
}
/*编辑学生信息*/
void edit_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n输入需要编辑的学生的学号：");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {//找到需要编辑的行
            system("cls");
            printf("\n\n\t学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[spc->size].stu_ID, spc->st[spc->size].stu_name, spc->st[spc->size].sex,
                spc->st[spc->size].age, spc->st[spc->size].collage, spc->st[spc->size].grade, spc->st[spc->size].contact);
            printf("\n这是修改前的数据，请依次输入修改值：\n\t");
            fflush(stdin);
            scanf("%s %s %s %s %s %s %s", &spc->st[h].stu_ID, &spc->st[h].stu_name, &spc->st[h].sex,
                &spc->st[h].age, &spc->st[h].collage, &spc->st[h].grade, &spc->st[h].contact);
            int k;
            for (k = 0; k <= spc->size; k++) {
                if (strcmp(spc->st[k].stu_ID, spc->st[h].stu_ID) == 0) {
                    if (k == h) {
                        continue;
                    }
                    else {//学号不唯一
                        printf("\n此学号已存在！重新输入学号：");
                        fflush(stdin);
                        scanf("%s", &spc->st[h].stu_ID);
                        k = -1;
                    }
                }
            }
            /*将修改信息写入文件*/
            //思想：将原文件重新写入一遍
            renew_stu(spc);
            system("cls");
            printf("修改成功！\n");
            system("pause");
            system("cls");
            stu_operate(spc,cpc,lpc);
        }
    }
    printf("\n此学号不存在！\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}
/*删除学生信息*/
void delete_stu(Stu* spc, Cou* cpc, Sel* lpc)
{
    printf("\n输入需要编辑的学生的学号：");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {//找到需要编辑的行
            system("cls");
            //检查他/她是否选课了
            int a;
            for (a = 0; a <= lpc->size; a++) {
                if (h == lpc->sel[a].s) {//选课了则将对应课程记录减1,以及选课数组减1
                    delete_sel(cpc,lpc,a);
                    a = -1;
                    lpc->size--;
                    continue;
                }
            }
            //如果只有一条记录
            if (spc->size == 0) {
                spc->size = -1;
                renew_stu(spc);
                printf("修改成功！\n");
                system("pause");
                system("cls");
                stu_operate(spc,cpc,lpc);
            }

            int k;
            for (k = h + 1; k <= spc->size; k++, h++) {//将数组直接向前移动
                strcpy(spc->st[h].stu_ID, spc->st[k].stu_ID);
                strcpy(spc->st[h].stu_name, spc->st[k].stu_name);
                strcpy(spc->st[h].sex, spc->st[h].sex);
                strcpy(spc->st[h].grade, spc->st[h].grade);
                strcpy(spc->st[h].contact, spc->st[k].contact);
                strcpy(spc->st[h].collage, spc->st[k].collage);
                strcpy(spc->st[h].age, spc->st[k].age);
            }
            /*将修改信息写入文件*/
            //思想：将原文件重新写入一遍
            renew_stu(spc);
            spc->size--;
            system("cls");
            printf("修改成功！\n");
            system("pause");
            system("cls");
            stu_operate(spc,cpc,lpc);
        }
    }
    printf("\n此学号不存在！\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}

//void LordStu(Stu* pc)
//{
//    FILE* pf = fopen("student.txt", "rb");
//    if (pf == NULL)
//    {
//        perror("LordStu fail");
//    }
//    else
//    {
//        stu temp;
//        int i = 0;
//        while (fread(&temp, sizeof(stu), 1, pf))
//        {
//            //check_capacity(pc);
//            pc->st[i] = temp;
//            pc->size++;
//            i++;
//        }
//        fclose(pf);
//        pf = NULL;
//    }
//}

void renew_stu(Stu* pc) {
    FILE* fp;
    fp = fopen("student.txt", "w+");
    if (fp == NULL) {
        printf("\n打开文件失败,无法保存至文件。\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "学号\t姓名\t性别\t年龄\t系别\t班级\t联系方式\n");
    if (pc->size == -1) {
        fclose(fp);
        return;
    }
    int h;
    for (h = 0; h <= pc->size; h++) {
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", pc->st[h].stu_ID, pc->st[h].stu_name, pc->st[h].sex,
            pc->st[h].age, pc->st[h].collage, pc->st[h].grade, pc->st[h].contact);
    }
    fclose(fp);

}

