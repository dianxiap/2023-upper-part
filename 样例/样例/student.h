#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"

//��ʼ��˳���
void init_stu(Stu *pc);
//����ѧ����Ϣ
void input_stu(Stu* spc, Cou* cpc, Sel* lpc);

//����ѧ����Ϣ
void search_stu(Stu* spc, Cou* cpc, Sel* lpc);
//�����±����ѧ����Ϣ
void search_stu_id(Stu* spc, Cou* cpc, Sel* lpc);
//������������ѧ����Ϣ
void search_stu_name(Stu* spc, Cou* cpc, Sel* lpc);

//��ʾѧ����Ϣ
void show_stu(Stu* spc, Cou* cpc, Sel* lpc);
//�༭ѧ����Ϣ
void edit_stu(Stu* spc, Cou* cpc, Sel* lpc);
//����ѧ����Ϣ
void renew_stu(Stu* spc);
//ɾ��ѧ����Ϣ
void delete_stu(Stu* spc, Cou* cpc, Sel* lpc);
//����ѧ����Ϣ
void LordStu(Stu *pc);
//����ѧ����Ϣ
void stu_operate(Stu* spc, Cou* cpc, Sel* lpc);