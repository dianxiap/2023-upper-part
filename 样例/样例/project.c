#define _CRT_SECURE_NO_WARNINGS 1
#include "project.h"
//--------------------------------------�γ���Ϣ����--------------------------------------
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
    printf("\n-------------------------��ӭ����ѡ��ϵͳ��----------------------");
    printf("\n\n                 ��ѡ����Ҫ�Կγ̼�¼���еĲ�����");
    printf("\n\n                             1.���");
    printf("\n                             2.��ѯ");
    printf("\n                             3.��ʾ");
    printf("\n                             4.������ҳ��");
    printf("\n                                                      ");
    printf("\n                        �����룺");
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
    //--�ж��ļ��Ƿ�Ϊ��
    fp = fopen("course.txt", "a+");
    flag = fgetc(fp);
    if (flag == EOF) {
        fprintf(fp, "����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\tѡ������\n");
    }
    fclose(fp);
    //--
    fp = fopen("course.txt", "a+");
    if (fp == NULL) {
        printf("���ļ�ʧ�ܣ�");
        system("cls");
        cou_operate(spc,cpc,lpc);
    }
    printf("����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\n");
    while (1) {
        cpc->size++;
        scanf("%s %s %s %s %s %s", &cpc->cou[cpc->size].course_ID, &cpc->cou[cpc->size].course_name, 
            &cpc->cou[cpc->size].property, &cpc->cou[cpc->size].period, &cpc->cou[cpc->size].credit, &cpc->cou[cpc->size].time);
        cpc->cou[cpc->size].people = 0;
        //--���ݲ���
        int h;
        for (h = 0; h < cpc->size; h++) {
            if (cpc->size == 0) break;//��һ�����ݲ���Ҫ����
            if (strcmp(cpc->cou[h].course_ID,cpc->cou[cpc->size].course_ID) == 0) {
                printf("�ÿγ̺��Ѵ��ڣ����������룡\n");
                scanf("\n%s %s %s %s %s %s", &cpc->cou[cpc->size].course_ID, &cpc->cou[cpc->size].course_name,
                    &cpc->cou[cpc->size].property, &cpc->cou[cpc->size].period, &cpc->cou[cpc->size].credit, &cpc->cou[cpc->size].time);
                h = -1;
            }
        }
        //--
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[cpc->size].course_ID,cpc->cou[cpc->size].course_name,
            cpc->cou[cpc->size].property,cpc->cou[cpc->size].period, cpc->cou[cpc->size].credit, cpc->cou[cpc->size].time, cpc->cou[cpc->size].people);
        printf("\n¼��ɹ�������¼������y��������һ���밴�������");
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
/*��ѯ�γ���Ϣ*/
void search_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    printf("\n��ѡ���ѯ��ʽ��");
    printf("\n  1.�γ̺Ų�ѯ");
    printf("\n  2.�γ�����ѯ");
    printf("\n��ѡ��");
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

/*�γ̺Ų�ѯ*/
void search_cou_id(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char id[9] = { 0 };
    printf("\n����γ̺�:");
    fflush(stdin);
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {
            system("cls");
            printf("���ҳɹ�!");
            printf("\n\n\t����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\tѡ������");
            printf("\n\t-----------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time, cpc->cou[h].people);
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    system("cls");
    printf("û�д˿γ̺ţ�\n");
    system("pause");
    system("cls");
    cou_operate(spc,cpc,lpc);
}
/*�γ�����ѯ*/
void search_cou_name(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char name[9] = { 0 };
    printf("\n����γ���:");
    fflush(stdin);
    scanf("%s", name);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_name, name) == 0) {
            system("cls");
            printf("���ҳɹ�!");
            printf("\n\n\t����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\tѡ������");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time,cpc->cou[h].people);
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    system("cls");
    printf("û�д˿γ�����");
    system("pause");
    system("cls");
    cou_operate(spc,cpc,lpc);
}
/*��ʾ���пγ���Ϣ*/
void show_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    int h;
    if (cpc->size == -1) {
        printf("\n��û��¼����Ϣ��\n");
        system("pause");
        system("cls");
        cou_operate(spc, cpc,lpc);
    }
    system("cls");
    printf("\n\n\t����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\tѡ������");
    printf("\n\t-------------------------------------------------------------");
    for (h = 0; h <=cpc->size; h++) {
        printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t\t%d\n", cpc->cou[h].course_ID, cpc->cou[h].course_name,
            cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time, cpc->cou[cpc->size].people);
    }
    //
    fflush(stdin);
    printf("\n\t1.�޸�");
    printf("\n\t2.ɾ��");
    printf("\n\t3.����");
    printf("\n\n  ѡ��Ҫ���еĲ�����");
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
/*�༭�γ���Ϣ*/
void edit_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n������Ҫ�༭�Ŀγ̺ţ�");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {//�ҵ���Ҫ�༭����
            system("cls");
            printf("\n\n\t����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��");
            printf("\n\t-------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\n",cpc->cou[h].course_ID, cpc->cou[h].course_name,
                cpc->cou[h].property, cpc->cou[h].period, cpc->cou[h].credit, cpc->cou[h].time);
            printf("\n�����޸�ǰ�����ݣ������������޸�ֵ��\n\t");
            fflush(stdin);
            scanf("%s %s %s %s %s %s", &cpc->cou[h].course_ID, &cpc->cou[h].course_name,
                &cpc->cou[h].property, &cpc->cou[h].period, &cpc->cou[h].credit, &cpc->cou[h].time);
            int k;
            for (k = 0; k <= cpc->size; k++) {
                if (strcmp(cpc->cou[k].course_ID, cpc->cou[h].course_ID) == 0) {
                    if (k == h) {
                        continue;
                    }
                    else {//�γ̺Ų�Ψһ
                        printf("\n�˿γ̺��Ѵ��ڣ��������룺");
                        fflush(stdin);
                        scanf("%s", &cpc->cou[h].course_ID);
                        k = -1;
                    }
                }
            }
            /*���޸���Ϣд���ļ�*/
            //˼�룺��ԭ�ļ�����д��һ��
            renew_cou(cpc);
            system("cls");
            printf("�޸ĳɹ���\n");
            system("pause");
            system("cls");
            cou_operate(spc, cpc, lpc);
        }
    }
    printf("\n�˿γ̺Ų����ڣ�\n");
    system("pause");
    system("cls");
    cou_operate(spc, cpc, lpc);
}
/*ɾ���γ���Ϣ*/
void delete_cou(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n������Ҫ�༭�Ŀγ̺ţ�");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= cpc->size; h++) {
        if (strcmp(cpc->cou[h].course_ID, id) == 0) {//�ҵ���Ҫ�༭����
            system("cls");
            //���ֻ��һ����¼
            if (cpc->size == 0) {
                cpc->size = -1;
                renew_cou(cpc);
                printf("�޸ĳɹ���\n");
                system("pause");
                system("cls");
                cou_operate(spc, cpc, lpc);
            }
            //�鿴�Ƿ�����ѡ��
            if (cpc->cou[h].people != 0) {//����ѡ��ʱ
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
            for (k = h + 1; k <= cpc->size; k++, h++) {//������ֱ����ǰ�ƶ�
                strcpy(cpc->cou[h].course_ID, cpc->cou[k].course_ID);
                strcpy(cpc->cou[h].course_name, cpc->cou[k].course_name);
                strcpy(cpc->cou[h].property, cpc->cou[k].property);
                strcpy(cpc->cou[h].period, cpc->cou[k].period);
                strcpy(cpc->cou[h].credit, cpc->cou[k].credit);
                strcpy(cpc->cou[h].time, cpc->cou[k].time);
            }
            /*���޸���Ϣд���ļ�*/
            //˼�룺��ԭ�ļ�����д��һ��
            renew_cou(cpc);
            cpc->size--;
            system("cls");
            printf("�޸ĳɹ���\n");
            system("pause");
            system("cls");
            cou_operate(spc,cpc,lpc);
        }
    }
    printf("\n�˿γ̺Ų����ڣ�\n");
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
        printf("\n���ļ�ʧ��,�޷��������ļ���\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "����\t����\t����\t��ѧʱ\tѧ��\t����ѧ��\tѡ������\n");
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

