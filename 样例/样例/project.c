#define _CRT_SECURE_NO_WARNINGS 1
#include "project.h"
//--------------------------------------课程信息插入--------------------------------------
void initCou(Cou* pc)
{
    assert(pc);
    cou* tem = (cou*)malloc(sizeof(cou) * SIZE_COU);
    if (tem == NULL)
    {
        perror("malloc fail");
        return;
    }
    pc->cou =tem;
    pc->capacity = SIZE_COU;
    pc->size = -1;
    pc->cou->people = 0;

    //LordCou(pc);
}
void cou_operate(Stu* spc,Cou* cpc,Sel* lpc) {
    printf("\n-------------------------欢迎进入选课系统！----------------------");
    printf("\n\n                 请选择你要对课程记录进行的操作：");
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
        case 1:
            input_cou(spc,cpc,lpc);
                break;
        case 2:
            search_cou(spc, cpc, lpc);
                    break;
        case 3:
            show_cou(spc,cpc,lpc);
        case 4:
            home(spc,cpc,lpc);
            break;

    }
 
}
void input_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    char flag;
    FILE* fp;
    //--判断文件是否为空
    fp = fopen("course.txt", "a+");
    flag = fgetc(fp);
    if (flag == EOF) {
        fprintf(fp, "代码\t名称\t性质\t总学时\t学分\t开课学期\t选修人数\n");
    }
    fclose(fp);
    //--
    fp = fopen("course.txt", "a+");
    if (fp == NULL) {
        printf("打开文件失败！");
        system("cls");
        cou_operate(spc,cpc,lpc);
    }
    printf("代码\t名称\t性质\t总学时\t学分\t开课学期\n");
    while (1) {
        cpc->size++;
        scanf("%s %s %s %s %s %s", &cpc->cou[cpc->size].course_ID, &cpc->cou[cpc->size].course_name, 
            &cpc->cou[cpc->size].property, &cpc->cou[cpc->size].period, &cpc->cou[cpc->size].credit, &cpc->cou[cpc->size].time);
        cpc->cou[cpc->size].people = 0;
        //--数据查重
        int h;
        for (h = 0; h < cpc->size; h++) {
            if (cpc->size == 0) break;//第一条数据不需要查重
            if (strcmp(cpc->cou[h].course_ID,cpc->cou[cpc->size].course_ID) == 0) {
                printf("该课程号已存在，请重新输入！\n");
                scanf("\n%s %s %s %s %s %s", &cpc->cou[cpc->size].course_ID, &cpc->cou[cpc->size].course_name,
                    &cpc->cou[cpc->size].property, &cpc->cou[cpc->size].period, &cpc->cou[cpc->size].credit, &cpc->cou[cpc->size].time);
                h = -1;
            }
        }
        //--
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[cpc->size].course_ID,cpc->cou[cpc->size].course_name,
            cpc->cou[cpc->size].property,cpc->cou[cpc->size].period, cpc->cou[cpc->size].credit, cpc->cou[cpc->size].time, cpc->cou[cpc->size].people);
        printf("\n录入成功，继续录入输入y，返回上一级请按任意键：");
        fflush(stdin);
        scanf("%c", &flag);
        fclose(fp);
        if (flag != 'y' && 'Y') break;
        fp = fopen("course.txt", "a");
    }
    renew_cou(cpc);
    system("cls");
    cou_operate(spc,cpc,lpc);
}
/*查询课程信息*/
void search_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    printf("\n请选择查询方式：");
    printf("\n  1.课程号查询");
    printf("\n  2.课程名查询");
    printf("\n请选择：");
    int h;
    scanf(" %d", &h);
    switch (h) {
    case 1:
        search_cou_id(spc,cpc,lpc);
        break;
    case 2:
        search_cou_name(spc,cpc,lpc);
        break;

    }
}

/*课程号查询*/
void search_cou_id(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char id[9] = { 0 };
    printf("\n输入课程号:");
    fflush(stdin);
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {
            system("cls");
            printf("查找成功!");
            printf("\n\n\t代码\t名称\t性质\t总学时\t学分\t开课学期\t选修人数");
            printf("\n\t-----------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time, cpc->cou[h].people);
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    system("cls");
    printf("没有此课程号！\n");
    system("pause");
    system("cls");
    cou_operate(spc,cpc,lpc);
}
/*课程名查询*/
void search_cou_name(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char name[9] = { 0 };
    printf("\n输入课程名:");
    fflush(stdin);
    scanf("%s", name);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_name, name) == 0) {
            system("cls");
            printf("查找成功!");
            printf("\n\n\t代码\t名称\t性质\t总学时\t学分\t开课学期\t选修人数");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time,cpc->cou[h].people);
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    system("cls");
    printf("没有此课程名！");
    system("pause");
    system("cls");
    cou_operate(spc,cpc,lpc);
}
/*显示所有课程信息*/
void show_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    int h;
    if (cpc->size == -1) {
        printf("\n还没有录入信息！\n");
        system("pause");
        system("cls");
        cou_operate(spc, cpc,lpc);
    }
    system("cls");
    printf("\n\n\t代码\t名称\t性质\t总学时\t学分\t开课学期\t选修人数");
    printf("\n\t-------------------------------------------------------------");
    for (h = 0; h <=cpc->size; h++) {
        printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
            cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time, cpc->cou[cpc->size].people);
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
        edit_cou(spc, cpc, lpc);
        break;
    case 2:
        delete_cou(spc, cpc, lpc);
        break;
    default:
        system("cls");
        cou_operate(spc, cpc, lpc);
        break;

    }
}
/*编辑课程信息*/
void edit_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n输入需要编辑的课程号：");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {//找到需要编辑的行
            system("cls");
            printf("\n\n\t代码\t名称\t性质\t总学时\t学分\t开课学期");
            printf("\n\t-------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\n",cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time);
            printf("\n这是修改前的数据，请依次输入修改值：\n\t");
            fflush(stdin);
            scanf("%s %s %s %s %s %s", &cpc->cou[h].course_ID, &cpc->cou[h].course_name,
                &cpc->cou[h].property, &cpc->cou[h].period, &cpc->cou[h].credit, &cpc->cou[h].time);
            int k;
            for (k = 0; k <= cpc->size; k++) {
                if (strcmp(cpc->cou[k].course_ID, cpc->cou[h].course_ID) == 0) {
                    if (k == h) {
                        continue;
                    }
                    else {//课程号不唯一
                        printf("\n此课程号已存在，重新输入：");
                        fflush(stdin);
                        scanf("%s", &cpc->cou[h].course_ID);
                        k = -1;
                    }
                }
            }
            /*将修改信息写入文件*/
            //思想：将原文件重新写入一遍
            renew_cou(cpc);
            system("cls");
            printf("修改成功！\n");
            system("pause");
            system("cls");
            cou_operate(spc, cpc, lpc);
        }
    }
    printf("\n此课程号不存在！\n");
    system("pause");
    system("cls");
    cou_operate(spc, cpc, lpc);
}
/*删除课程信息*/
void delete_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n输入需要编辑的课程号：");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {//找到需要编辑的行
            system("cls");
            //如果只有一条记录
            if (cpc->size == 0) {
                cpc->size = -1;
                renew_cou(cpc);
                printf("修改成功！\n");
                system("pause");
                system("cls");
                cou_operate(spc, cpc, lpc);
            }
            //查看是否有人选课
            if (cpc->cou[h].people != 0) {//有人选课时
                int a;
                for (a = 0; a <= lpc->size; a++) {
                    if (lpc->sel[a].c == h) {
                        delete_sel(cpc,lpc,a);
                        a = -1;
                        lpc->size--;
                        continue;
                    }
                }
            }
            int k;
            for (k = h + 1; k <= cpc->size; k++, h++) {//将数组直接向前移动
                strcpy(cpc->cou[h].course_ID, cpc->cou[k].course_ID);
                strcpy(cpc->cou[h].course_name, cpc->cou[k].course_name);
                strcpy(cpc->cou[h].property, cpc->cou[k].property);
                strcpy(cpc->cou[h].period, cpc->cou[k].period);
                strcpy(cpc->cou[h].credit, cpc->cou[k].credit);
                strcpy(cpc->cou[h].time, cpc->cou[k].time);
            }
            /*将修改信息写入文件*/
            //思想：将原文件重新写入一遍
            renew_cou(cpc);
            cpc->size--;
            system("cls");
            printf("修改成功！\n");
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    printf("\n此课程号不存在！\n");
    system("pause");
    system("cls");
    cou_operate(spc, cpc, lpc);
}



//void LordCou(Cou* pc)
//{
//    FILE* pf = fopen("course.txt", "r+");
//    if (pf == NULL)
//    {
//        perror("LordStu fail");
//    }
//    else
//    {
//        cou temp;
//        int i = 0;
//      
//        while (fread(&temp, sizeof(cou), 1, pf))
//        {
//            //check_capacity(pc);
//            pc->cou[i] = temp;
//            pc->size++;
//            i++;
//        }
//        fclose(pf);
//        pf = NULL;
//    }
//}

void renew_cou(Cou* pc) {
    FILE* fp;
    fp = fopen("course.txt", "w+");
    if (fp == NULL) {
        printf("\n打开文件失败,无法保存至文件。\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "代码\t名称\t性质\t总学时\t学分\t开课学期\t选修人数\n");
    if (pc->size == -1) {
        fclose(fp);
        return;
    }
    int h;
    for (h = 0; h <= pc->size; h++) {
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n",
            pc->cou[h].course_ID, pc->cou[h].course_name,
            pc->cou[h].property, pc->cou[h].period, pc->cou[h].credit, pc->cou[h].time, pc->cou[h].people);
    }
    fclose(fp);

}

