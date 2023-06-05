#define _CRT_SECURE_NO_WARNINGS 1
#include "student.h"

void init_stu(Stu *pc)
{
    assert(pc);
    stu* ptr = (stu*)malloc(sizeof(stu) * SIZE_STU);
    if (ptr == NULL)
    {
        perror("initstu fail");
        return;
    }
    pc->st = ptr;
    pc->capacity = SIZE_STU;
    pc->size = -1;

    //LordStu(pc);
}
void stu_operate(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n-------------------------��ӭ����ѡ��ϵͳ��----------------------");
    printf("\n\n                 ��ѡ����Ҫ��ѧ����¼���еĲ�����");
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
    case 1://���ѧ����Ϣ 
        input_stu(spc, cpc, lpc);
        break;
    case 2://��ѯѧ����Ϣ 
        search_stu(spc, cpc, lpc);
        break;
    case 3://��ʾ����ѧ����Ϣ
        show_stu(spc, cpc, lpc);
        break;
    case 4:
        home(spc,cpc,lpc);
        break;
    }
}
void input_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    char flag;
    FILE* fp;
    //--�ж��ļ��Ƿ�Ϊ��
    fp = fopen("student.txt", "a+");
    flag = fgetc(fp);
    if (flag == EOF) {
        fprintf(fp, "ѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ\n");
    }
    fclose(fp);
    //--
    fp = fopen("student.txt", "a+");
    if (fp == NULL) {
        printf("���ļ�ʧ�ܣ�");
        system("cls");
        stu_operate(spc, cpc, lpc);
    }
    printf("ѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ\n");
    while (1) {
        spc->size++;
        scanf("%s %s %s %s %s %s %s", &spc->st[spc->size].stu_ID, &spc->st[spc->size].stu_name, &spc->st[spc->size].sex, 
            &spc->st[spc->size].age, &spc->st[spc->size].collage, &spc->st[spc->size].grade, &spc->st[spc->size].contact);
        //--���ݲ���
        int h;
        for (h = 0; h < spc->size; h++) {
            if (spc->size == 0) break;//��һ�����ݲ���Ҫ����
            if (strcmp(spc->st[h].stu_ID, spc->st[spc->size].stu_ID) == 0) {
                printf("��ѧ���Ѵ��ڣ����������룡\n");
                scanf("%s %s %s %s %s %s %s", &spc->st[spc->size].stu_ID, &spc->st[spc->size].stu_name, &spc->st[spc->size].sex,
                    &spc->st[spc->size].age, &spc->st[spc->size].collage, &spc->st[spc->size].grade, &spc->st[spc->size].contact);
                h = -1;
            }
        }
        //--
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",  spc->st[spc->size].stu_ID, spc->st[spc->size].stu_name, spc->st[spc->size].sex,
            spc->st[spc->size].age, spc->st[spc->size].collage, spc->st[spc->size].grade, spc->st[spc->size].contact);
        printf("\n¼��ɹ�������¼������y��������һ���밴�������");
        fflush(stdin);
        scanf("%c", &flag);
        fclose(fp);
        if (flag != 'y' && 'Y') break;
        fp = fopen("student.txt", "a");
       
    }
    renew_stu(spc);
    system("cls");
    stu_operate(spc, cpc, lpc);
}
/*��ѯѧ����Ϣ*/
void search_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    printf("\n��ѡ���ѯ��ʽ��");
    printf("\n  1.ѧ�Ų�ѯ");
    printf("\n  2.������ѯ");
    printf("\n��ѡ��");
    int h;
    scanf(" %d", &h);
    switch (h) {
    case 1:
        search_stu_id(spc, cpc, lpc);
        break;
    case 2:
        search_stu_name(spc, cpc, lpc);
        break;

    }
}
/*ѧ�Ų�ѯ*/
void search_stu_id(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char id[9] = { 0 };
    printf("\n����ѧ����ѧ��:");
    fflush(stdin);
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {
            system("cls");
            printf("���ҳɹ�!");
            printf("\n\n\tѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ");
            printf("\n\t-----------------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID,&spc->st[h].stu_name, spc->st[h].sex,
                spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
            system("pause");
            system("cls");
            stu_operate(spc, cpc, lpc);
        }
    }
    system("cls");
    printf("û�д�ѧ�ţ�\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}
/*������ѯ*/
void search_stu_name(Stu* spc, Cou* cpc, Sel* lpc) {
    system("cls");
    char name[9] = { 0 };
    printf("\n����ѧ��������:");
    fflush(stdin);
    scanf("%s", name);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_name, name) == 0) {
            system("cls");
            printf("���ҳɹ�!");
            printf("\n\n\tѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID, &spc->st[h].stu_name, spc->st[h].sex,
                spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
            system("pause");
            system("cls");
            stu_operate(spc, cpc, lpc);
        }
    }
    system("cls");
    printf("û�д�������");
    system("pause");
    system("cls");
    stu_operate(spc, cpc, lpc);
}
/*��ʾ����ѧ����Ϣ*/
void show_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    int h;
    if (spc->size == -1) {
        printf("\n��û��¼����Ϣ��\n");
        system("pause");
        system("cls");
        stu_operate(spc, cpc, lpc);
    }
    system("cls");
    printf("\n\n\tѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ");
    printf("\n\t---------------------------------------------------------");
    for (h = 0; h <= spc->size; h++) {
        printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[h].stu_ID, &spc->st[h].stu_name, spc->st[h].sex,
            spc->st[h].age, spc->st[h].collage, spc->st[h].grade, spc->st[h].contact);
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
        edit_stu(spc, cpc, lpc);
        break;
    case 2:
        delete_stu(spc, cpc, lpc);
        break;
    default:
        system("cls");
        stu_operate(spc, cpc, lpc);
        break;

    }
}
/*�༭ѧ����Ϣ*/
void edit_stu(Stu* spc, Cou* cpc, Sel* lpc) {
    printf("\n������Ҫ�༭��ѧ����ѧ�ţ�");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {//�ҵ���Ҫ�༭����
            system("cls");
            printf("\n\n\tѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ");
            printf("\n\t---------------------------------------------------------");
            printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", spc->st[spc->size].stu_ID, spc->st[spc->size].stu_name, spc->st[spc->size].sex,
                spc->st[spc->size].age, spc->st[spc->size].collage, spc->st[spc->size].grade, spc->st[spc->size].contact);
            printf("\n�����޸�ǰ�����ݣ������������޸�ֵ��\n\t");
            fflush(stdin);
            scanf("%s %s %s %s %s %s %s", &spc->st[h].stu_ID, &spc->st[h].stu_name, &spc->st[h].sex,
                &spc->st[h].age, &spc->st[h].collage, &spc->st[h].grade, &spc->st[h].contact);
            int k;
            for (k = 0; k <= spc->size; k++) {
                if (strcmp(spc->st[k].stu_ID, spc->st[h].stu_ID) == 0) {
                    if (k == h) {
                        continue;
                    }
                    else {//ѧ�Ų�Ψһ
                        printf("\n��ѧ���Ѵ��ڣ���������ѧ�ţ�");
                        fflush(stdin);
                        scanf("%s", &spc->st[h].stu_ID);
                        k = -1;
                    }
                }
            }
            /*���޸���Ϣд���ļ�*/
            //˼�룺��ԭ�ļ�����д��һ��
            renew_stu(spc);
            system("cls");
            printf("�޸ĳɹ���\n");
            system("pause");
            system("cls");
            stu_operate(spc,cpc,lpc);
        }
    }
    printf("\n��ѧ�Ų����ڣ�\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}
/*ɾ��ѧ����Ϣ*/
void delete_stu(Stu* spc, Cou* cpc, Sel* lpc)
{
    printf("\n������Ҫ�༭��ѧ����ѧ�ţ�");
    char id[10] = { 0 };
    getchar();
    scanf("%s", id);
    int h;
    for (h = 0; h <= spc->size; h++) {
        if (strcmp(spc->st[h].stu_ID, id) == 0) {//�ҵ���Ҫ�༭����
            system("cls");
            //�����/���Ƿ�ѡ����
            int a;
            for (a = 0; a <= lpc->size; a++) {
                if (h == lpc->sel[a].s) {//ѡ�����򽫶�Ӧ�γ̼�¼��1,�Լ�ѡ�������1
                    delete_sel(cpc,lpc,a);
                    a = -1;
                    lpc->size--;
                    continue;
                }
            }
            //���ֻ��һ����¼
            if (spc->size == 0) {
                spc->size = -1;
                renew_stu(spc);
                printf("�޸ĳɹ���\n");
                system("pause");
                system("cls");
                stu_operate(spc,cpc,lpc);
            }

            int k;
            for (k = h + 1; k <= spc->size; k++, h++) {//������ֱ����ǰ�ƶ�
                strcpy(spc->st[h].stu_ID, spc->st[k].stu_ID);
                strcpy(spc->st[h].stu_name, spc->st[k].stu_name);
                strcpy(spc->st[h].sex, spc->st[h].sex);
                strcpy(spc->st[h].grade, spc->st[h].grade);
                strcpy(spc->st[h].contact, spc->st[k].contact);
                strcpy(spc->st[h].collage, spc->st[k].collage);
                strcpy(spc->st[h].age, spc->st[k].age);
            }
            /*���޸���Ϣд���ļ�*/
            //˼�룺��ԭ�ļ�����д��һ��
            renew_stu(spc);
            spc->size--;
            system("cls");
            printf("�޸ĳɹ���\n");
            system("pause");
            system("cls");
            stu_operate(spc,cpc,lpc);
        }
    }
    printf("\n��ѧ�Ų����ڣ�\n");
    system("pause");
    system("cls");
    stu_operate(spc,cpc,lpc);
}

//void LordStu(Stu* pc)
//{
//    FILE* pf = fopen("student.txt", "rb");
//    if (pf == NULL)
//    {
//        perror("LordStu fail");
//    }
//    else
//    {
//        stu temp;
//        int i = 0;
//        while (fread(&temp, sizeof(stu), 1, pf))
//        {
//            //check_capacity(pc);
//            pc->st[i] = temp;
//            pc->size++;
//            i++;
//        }
//        fclose(pf);
//        pf = NULL;
//    }
//}

void renew_stu(Stu* pc) {
    FILE* fp;
    fp = fopen("student.txt", "w+");
    if (fp == NULL) {
        printf("\n���ļ�ʧ��,�޷��������ļ���\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "ѧ��\t����\t�Ա�\t����\tϵ��\t�༶\t��ϵ��ʽ\n");
    if (pc->size == -1) {
        fclose(fp);
        return;
    }
    int h;
    for (h = 0; h <= pc->size; h++) {
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", pc->st[h].stu_ID, pc->st[h].stu_name, pc->st[h].sex,
            pc->st[h].age, pc->st[h].collage, pc->st[h].grade, pc->st[h].contact);
    }
    fclose(fp);

}

