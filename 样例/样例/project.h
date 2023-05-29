#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"

void initCou(Cou* pc);
void input_cou(Stu* spc, Cou* cpc, Sel* lpc);
void search_cou(Stu* spc, Cou* cpc, Sel* lpc);
void search_cou_id(Stu* spc, Cou* cpc, Sel* lpc);
void search_cou_name(Stu* spc, Cou* cpc, Sel* lpc);
void show_cou(Stu* spc, Cou* cpc, Sel* lpc);
void edit_cou(Stu* spc, Cou* cpc, Sel* lpc);
void renew_cou(Cou* pc);
void delete_cou(Stu* spc, Cou* cpc, Sel* lpc);
void renew_cou(Cou* pc);
void cou_operate(Stu* spc, Cou* cpc, Sel* lpc);

void LordCou(Cou* pc);