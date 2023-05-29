#define _CRT_SECURE_NO_WARNINGS 1
#include "select_project.h"

void home(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n-------------------------欢迎进入选课系统！----------------------");
    int h;
    printf("\n\n                        请选择你要进行的操作：");
    printf("\n\n                             1.学生操作");
    printf("\n                             2.课程操作");
    printf("\n                             3.开始选课");
    printf("\n                             4.选课统计");
    printf("\n                             5.退出系统");
    printf("\n                                                      ");
    printf("\n                        请输入：");
    scanf("%d", &h);
    system("cls");

    switch (h) {
    case 1:
        stu_operate(spc,cpc,lpc);
        break;
    case 2:
        cou_operate(spc,cpc,lpc);
        break;
    case 3:
        choose(spc, cpc, lpc);
        break;
    case 4:
        statistic(lpc, spc, cpc);
        break;
    default:
        system("cls");
        printf("BYE!");
        break;
    }
}

/*开始选课*/
void init_Sel(Sel* pc)
{
    sel* str = malloc(sizeof(sel) * SIZE_SEL);
    if (str == NULL)
    {
        perror("malloc fail");
        return;
    }
    pc->sel = str;
    pc->capacity = SIZE_SEL;
    pc->size = -1;

  
}

void choose(Stu* spc,Cou* cpc,Sel* lpc) {
    char stu_id[10] = { 0 }, cou_id[10] = { 0 };
    printf("\n-------------------------欢迎进入选课系统！----------------------");
    //输入选课学生信息
    printf("\n\n                 请输入选课人学号：");
    fflush(stdin);
    scanf("%s", stu_id);
    int h, flag = 0;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, stu_id) == 0) {
            flag = 0;
            break;
        }
        else {
            flag = 1;
        }
    }
    if (flag || spc->size == -1) {
        printf("\n                 不存在此学号\n");
        system("pause");
        system("cls");
        home(spc,cpc,lpc);
    }
    //录入姓名信息
    lpc->size++;
    lpc->sel[lpc->size].s = h;

    //输入课程信息
    printf("\n\n                 请输入选修课程号：");
    fflush(stdin);
    scanf("%s", cou_id);
    flag = 0;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, cou_id) == 0) {
            flag = 0;
            break;
        }
        else {
            flag = 1;
        }
    }
    if (flag || cpc->size == -1) {
        printf("\n                 不存在此课程号\n");
        lpc->size--;
        system("pause");
        system("cls");
        home(spc,cpc,lpc);
    }
    //录入课程信息
    lpc->sel[lpc->size].c = h;
    cpc->cou[h].people++;
    printf("\n                 录入成功!\n");
    system("pause");
    system("cls");
    home(spc,cpc,lpc);
}
/*删除选课记录*/
void delete_sel(Cou* cpc,Sel* lpc,int q) {//删除第q+1条记录
    /*注意！本函数没有将x减1，请在函数外手动减1（考虑外层函数循环的需要）*/
    int h;
    cpc->cou[lpc->sel[q].c].people--;
    for (h = q; q < lpc->size; h++) {
        q++;
        lpc->sel[h].c = lpc->sel[q].c;
        lpc->sel[h].s = lpc->sel[q].s;
    }

}
//选课信息统计记录
void statistic(Sel* lpc,Stu* spc,Cou* cpc) {
    printf("\n-------------------------欢迎进入选课系统！----------------------");
    printf("\n\n                     共有学生信息：%d 条", spc->size + 1);
    printf("\n                     共有课程信息：%d 条", cpc->size + 1);
    if (lpc->size == -1) {
        printf("\n                       选课记录：0 条");
        printf("\n\n                     ");
        system("pause");
        system("cls");
        home(spc,cpc,lpc);
    }
    else {
        printf("\n\n                        选课记录 %d 条：", lpc->size + 1);
        int m;
        for (m = 0; m <= lpc->size; m++) {
            printf("\n                     ================");
            printf("\n                     第%d条", m + 1);
            printf("\n                     学生学号：%s", spc->st[lpc->sel[m].s].stu_ID);
            printf("\n                     学生姓名：%s", spc->st[lpc->sel[m].s].stu_name);
            printf("\n                     课程号：%s", cpc->cou[lpc->sel[m].c].course_ID);
            printf("\n                     课程名：%s", cpc->cou[lpc->sel[m].c].course_name);
        }
        printf("\n\n            ");
        system("pause");
        system("cls");
        home(spc,cpc,lpc);
    }

}

