#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "headdefine.h"
#include "select_project.h"

//��ʼ��˳���
void initCou(Cou* pc);

//����γ���Ϣ
void input_cou(Stu* spc, Cou* cpc, Sel* lpc);

//��ѯ�γ���Ϣ
void search_cou(Stu* spc, Cou* cpc, Sel* lpc);
//����ѧ�Ų���
void search_cou_id(Stu* spc, Cou* cpc, Sel* lpc);
//������������
void search_cou_name(Stu* spc, Cou* cpc, Sel* lpc);

//��ʾ�γ���Ϣ
void show_cou(Stu* spc, Cou* cpc, Sel* lpc);

//�޸Ŀγ�
void edit_cou(Stu* spc, Cou* cpc, Sel* lpc);
//���¿γ����ݿ�
void renew_cou(Cou* pc);
//ɾ���γ�
void delete_cou(Stu* spc, Cou* cpc, Sel* lpc);

//�γ̲���
void cou_operate(Stu* spc, Cou* cpc, Sel* lpc);

//���ؿγ����ݿ�
void LordCou(Cou* pc);