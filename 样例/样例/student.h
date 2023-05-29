#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"

//初始化顺序表
void init_stu(Stu *pc);
//插入学生信息
void input_stu(Stu* spc, Cou* cpc, Sel* lpc);

//查找学生信息
void search_stu(Stu* spc, Cou* cpc, Sel* lpc);
//根据下标查找学生信息
void search_stu_id(Stu* spc, Cou* cpc, Sel* lpc);
//根据姓名查找学生信息
void search_stu_name(Stu* spc, Cou* cpc, Sel* lpc);

//显示学生信息
void show_stu(Stu* spc, Cou* cpc, Sel* lpc);
//编辑学生信息
void edit_stu(Stu* spc, Cou* cpc, Sel* lpc);
//更新学生信息
void renew_stu(Stu* spc);
//删除学生信息
void delete_stu(Stu* spc, Cou* cpc, Sel* lpc);
//加载学生信息
void LordStu(Stu *pc);
//管理学生信息
void stu_operate(Stu* spc, Cou* cpc, Sel* lpc);