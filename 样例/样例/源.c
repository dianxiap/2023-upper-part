#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"
#include "project.h"
#include "student.h"

int main() {
    //进入欢迎界面
    Stu spc;
    Cou cpc;
    Sel lpc;

    initCou(&cpc);
    init_Sel(&lpc);
    init_stu(&spc);
    home(&spc,&cpc,&lpc);
    return 0;
}


 