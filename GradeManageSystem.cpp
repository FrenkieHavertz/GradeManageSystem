#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>//system()
using namespace std;


//ѧ���ṹ
typedef struct TagStudent{
    char name[100];//����
    int grade;//�ɼ�
    int num;//ѧ��
}student;

//������
typedef struct TagNode{
    student stu;
    struct TagNode *next;
}Node;


//ͷ���
Node *Head = NULL;

int ReturnFlag = 0;


//������Ϣ
void CreatStudent(){
    system("cls");
    Node *NewNode = (Node*)malloc(sizeof(Node));//�����ڴ�
    NewNode->next = NULL;
    Node *p = Head;//���ڱ�����������
    
    //Ѱ��β���
    while(Head != NULL && p->next != NULL){
        p = p->next;
    }

    //���ͷ���Ϊ�գ����½��Ϊͷ��㣬�����½�����ӵ����
    if(Head == NULL){
        Head = NewNode;
    }else{
        p->next = NewNode;
    }

    printf("ѧ��������");
    scanf("%s",NewNode->stu.name);
    printf("\n\n");
    printf("ѧ���ɼ���");
    scanf("%d",&NewNode->stu.grade);
    printf("\n\n");
    printf("ѧ��ѧ�ţ�");
    scanf("%d",&NewNode->stu.num);
    printf("\n\n");

    printf("��Ϣ¼��ɹ�\n");
    system("pause");
    system("cls");
}

//��ӡ����ѧ����Ϣ
void PrintStudent(){
    system("cls");

    Node *p = Head;

    //���ϵͳ�л�û�����ݣ�����Ҫ����������
    if(!p){
        printf("����δ�������Ϣ���밴1������Ϣ����д˲�����\n");
        return ;
    }

    printf("\t����\t�ɼ�\tѧ��\n");
    printf("\t--------------------\n");

    //����ÿ�����
    while(p != NULL){
        printf("\t%s\t%d\t%d\n",p->stu.name,p->stu.grade,p->stu.num);
        p = p->next;
    }
    
    printf("��Ϣ��ӡ�ɹ�\n");
    system("pause");
    system("cls");
}

//�޸�ĳѧ����Ϣ
void ChangeStudent(){
    system("cls");

    int num;//��Ҫ�޸ĵ�ѧ����ѧ��
    int flag = 0;//�����ѧ���Ƿ�����������еı�־
    Node *p = Head;

    //����ѧ��
    printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ�\n");
    scanf("%d",&num);

    //����ÿ����㣬�����Ƿ��иý��
    while(p != NULL){
        if(p->stu.num == num){
            flag = 1;//˵����������������ѧ�ŵ�ѧ��
            printf("��ѡ����Ҫ�޸ĵ���Ŀ\n");
            printf("1������\n2���ɼ�\n3��ѧ��\n");
            int n;//ѡ���޸���Ŀ
            scanf("%d",&n);
            
            switch (n)
            {
            case 1://�޸�����
                char ch[100];
                printf("�����޸�Ϊ��\n");
                scanf("%s",ch);
                strcpy(p->stu.name,ch);
                break;
            case 2://�޸ĳɼ�
                int grade;
                printf("�ɼ��޸�Ϊ��\n");
                scanf("%d",&grade);
                p->stu.grade = grade;
                break;
            case 3://�޸�ѧ��
                int stunum;
                printf("ѧ���޸�Ϊ��\n");
                scanf("%d",&stunum);
                p->stu.grade = stunum;
                break;
            default://��������
                printf("��������ȷ����Ŀ���\n");
                system("pause");
                system("cls");
                break;
            }
        }
        p = p->next;
    }


    PrintStudent();
    //���������û�������ѧ���������ѧ��������������
    if(!flag){
        printf("û������ѧ��������������\n");
        system("pause");
        system("cls");
    }

    system("cls");
}

//ɾ��ĳѧ����Ϣ
void DeleteStudent(){
    system("cls");

    int num;//ѧ��
    int flag = 0;//�ж��Ƿ��ҵ���ѧ��
    printf("������Ҫɾ����ѧ����ѧ��\n");
    scanf("%d",&num);

    Node *p = Head;//��ɾ�����
    Node *pre = Head;//��ɾ������ǰһ���

    //ɾ�����
    while(p != NULL){
        if(p->stu.num == num){
            flag = 1;//�ҵ���ѧ��

            if(p == Head){//����ɾ�����Ϊͷ���
                Head = p->next;
            }else if(p->next == NULL){//����ɾ�����Ϊβ���
                pre->next = NULL;
            }else{//����ɾ�����Ϊ�м���
                pre->next = p->next;
                p->next = NULL;
            }

            free(p);
        }

        pre = p;
        p = p->next;
    }

    PrintStudent();        
    //δ�ҵ���ѧ��
    if(!flag){
        printf("û������ѧ��������������\n");
        system("pause");
        system("cls");
    }

    system("cls");
}

//������Ϣ
void SaveFile(){
    system("cls");

    //���ļ�
    FILE *pfile;
    pfile = fopen(".\\Student.dat","w");

    //���ļ�ʧ��
    if(!pfile){
        printf("����ʧ��\n");
        return ;
    }

    Node *p = Head;

    if(p == NULL){
        system("cls");
        printf("û���ܱ��������\n");
        system("pause");
        return;
    }

    //������Ϣ
    while(p != NULL){
        fprintf(pfile,"\t%s\t%d\t%d",p->stu.name,p->stu.grade,p->stu.num);
        p = p->next;
    }

    //�ر��ļ�
    fclose(pfile);
    printf("����ɹ�\n");
    system("pause");
    system("cls");
}

void LoadFile(){
    system("cls");

    //���ļ�
    FILE *pfile;
    pfile = fopen(".\\Student.dat","r");

    //���ļ�ʧ��
    if(!pfile){
        printf("��ȡʧ��\n");
        return ;
    }

    //�����ڴ�
    Node *p = (Node*)malloc(sizeof(Node));
    Node *pre = Head;//
    p->next = NULL;
    Head = p;
    
    //���ж�ȡ����
    while(fscanf(pfile,"\t%s\t%d\t%d",p->stu.name,&p->stu.grade,&p->stu.num) != EOF){
        Node *NewNode = (Node*)malloc(sizeof(Node));
        NewNode ->next = NULL;
        p->next = NewNode;
        pre = p;
        p = NewNode;
    }

    //����������һ����㣬��Ҫɾ��
    pre->next = NULL;
    free(p);
    
    //�ر��ļ�
    fclose(pfile);
    printf("��ȡ�ɹ�\n");
    PrintStudent();
    system("cls");
}

/*
------------    - -        - -      -------------           
-               -  -     -   -      -       
-               -   -   -    -      -
-     - - --    -     -      -      -------------
-          -    -     -      -                  -
-          -    -     -      -                  - 
------------    -     -      -      -------------
*/


//�˵�����
void menu(){
    //��Ҫ�˳������������ʱ�Ŵ�ӡ���������
    if(ReturnFlag == 0){
        printf("\n\n\n\n");
        printf("\t\t------------    - -        - -      -------------\t\t\n");
        printf("\t\t-               -  -     -   -      -            \t\t\n");
        printf("\t\t-               -   -   -    -      -            \t\t\n");
        printf("\t\t-     - - --    -     -      -      -------------\t\t\n");
        printf("\t\t-          -    -     -      -                  -\t\t\n");
        printf("\t\t-          -    -     -      -                  -\t\t\n");
        printf("\t\t------------    -     -      -      -------------\t\t\n");
        system("pause");
        system("cls");
    }
    printf("\t\t\t��ӭʹ��ѧ������ϵͳ\t\t\t\n\n");
    printf("\t\t\t�����Ӧ������ʹ�ö�Ӧ�Ĺ���\t\t\t\n\n");
    printf("0.�˳�\n\n1.¼����Ϣ\n\n2.��ӡ��Ϣ\n\n3.�޸�ĳѧ����Ϣ\n\n");
    printf("4.ɾ��ĳѧ����Ϣ\n\n5.������Ϣ\n\n6.��ȡ��Ϣ\n\n");
}

//������
int main(){
    int n;//�û�����ѡ��
    while(1){
        Desk://�˳�������������label
        system("cls");
        menu();//����
        n = getch();
        switch (n)
        {
        case '0'://�˳�
            goto Desk;//�˳������������
            break;    
        case '1'://¼����Ϣ
            CreatStudent();
            break;
        case '2'://��ӡ��Ϣ
            PrintStudent();
            break;
        case '3'://�޸���Ϣ
            ChangeStudent();
            break;
        case '4'://ɾ��ĳѧ����Ϣ
            DeleteStudent();
            break;
        case '5'://������Ϣ
            SaveFile();
            break;
        case '6'://��ȡ��Ϣ
            LoadFile();
            break;
        default:
            printf("û�д˹���\n\n");
            system("pause");
            system("cls");
            break;
        }
        system("cls");
        printf("�Ƿ��˳�����������棿\n");
        ChooseAgain://�Ƿ������label
        printf("0.��\n1.��\n");
        int Temp;//����������ǡ�������
        scanf("%d",&Temp);
        if(Temp == 1){
            ReturnFlag = 1;
        }else if(Temp == 0){
            ReturnFlag = 0;
        }else{
            printf("������ѡ��\n");
            goto ChooseAgain;//�Ƿ����룬��������
        }
    }

    return 0;
}
