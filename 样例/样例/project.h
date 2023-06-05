#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"

//初始化顺序表
void initCou(Cou* pc);

//插入课程信息
void input_cou(Stu* spc, Cou* cpc, Sel* lpc);

//查询课程信息
void search_cou(Stu* spc, Cou* cpc, Sel* lpc);
//按照学号查找
void search_cou_id(Stu* spc, Cou* cpc, Sel* lpc);
//按照姓名查找
void search_cou_name(Stu* spc, Cou* cpc, Sel* lpc);

//显示课程信息
void show_cou(Stu* spc, Cou* cpc, Sel* lpc);

//修改课程
void edit_cou(Stu* spc, Cou* cpc, Sel* lpc);
//更新课程数据库
void renew_cou(Cou* pc);
//删除课程
void delete_cou(Stu* spc, Cou* cpc, Sel* lpc);

//课程操作
void cou_operate(Stu* spc, Cou* cpc, Sel* lpc);

//加载课程数据库
void LordCou(Cou* pc);