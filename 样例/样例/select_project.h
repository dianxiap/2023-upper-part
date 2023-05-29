#pragma once
//Ñ¡¿Î¼ÇÂ¼
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "headdefine.h"
#include "project.h"
#include "student.h"

void home(Stu* spc, Cou* cpc, Sel* lpc);
void init_Sel(Sel* pc);
void statistic(Sel* lpc, Stu* spc, Cou* cpc);
void choose(Stu* spc, Cou* cpc, Sel* lpc);
void delete_sel(Cou* cpc, Sel* lpc, int q);
