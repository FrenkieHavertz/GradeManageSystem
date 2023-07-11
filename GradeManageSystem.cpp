#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>//system()
using namespace std;


//学生结构
typedef struct TagStudent{
    char name[100];//姓名
    int grade;//成绩
    int num;//学号
}student;

//链表结点
typedef struct TagNode{
    student stu;
    struct TagNode *next;
}Node;


//头结点
Node *Head = NULL;

int ReturnFlag = 0;


//输入信息
void CreatStudent(){
    system("cls");
    Node *NewNode = (Node*)malloc(sizeof(Node));//分配内存
    NewNode->next = NULL;
    Node *p = Head;//用于遍历整个链表
    
    //寻找尾结点
    while(Head != NULL && p->next != NULL){
        p = p->next;
    }

    //如果头结点为空，则新结点为头结点，否则新结点链接到最后
    if(Head == NULL){
        Head = NewNode;
    }else{
        p->next = NewNode;
    }

    printf("学生姓名：");
    scanf("%s",NewNode->stu.name);
    printf("\n\n");
    printf("学生成绩：");
    scanf("%d",&NewNode->stu.grade);
    printf("\n\n");
    printf("学生学号：");
    scanf("%d",&NewNode->stu.num);
    printf("\n\n");

    printf("信息录入成功\n");
    system("pause");
    system("cls");
}

//打印所有学生信息
void PrintStudent(){
    system("cls");

    Node *p = Head;

    //如果系统中还没有数据，则需要先输入数据
    if(!p){
        printf("您还未输入过信息，请按1输入信息后进行此操作。\n");
        return ;
    }

    printf("\t姓名\t成绩\t学号\n");
    printf("\t--------------------\n");

    //遍历每个结点
    while(p != NULL){
        printf("\t%s\t%d\t%d\n",p->stu.name,p->stu.grade,p->stu.num);
        p = p->next;
    }
    
    printf("信息打印成功\n");
    system("pause");
    system("cls");
}

//修改某学生信息
void ChangeStudent(){
    system("cls");

    int num;//需要修改的学生的学号
    int flag = 0;//输入的学号是否存在于数据中的标志
    Node *p = Head;

    //输入学号
    printf("请输入需要修改的学生学号：\n");
    scanf("%d",&num);

    //遍历每个结点，查找是否有该结点
    while(p != NULL){
        if(p->stu.num == num){
            flag = 1;//说明链表中有所输入学号的学生
            printf("请选择需要修改的项目\n");
            printf("1、姓名\n2、成绩\n3、学号\n");
            int n;//选择修改项目
            scanf("%d",&n);
            
            switch (n)
            {
            case 1://修改姓名
                char ch[100];
                printf("姓名修改为：\n");
                scanf("%s",ch);
                strcpy(p->stu.name,ch);
                break;
            case 2://修改成绩
                int grade;
                printf("成绩修改为：\n");
                scanf("%d",&grade);
                p->stu.grade = grade;
                break;
            case 3://修改学号
                int stunum;
                printf("学号修改为：\n");
                scanf("%d",&stunum);
                p->stu.grade = stunum;
                break;
            default://错误输入
                printf("请输入正确的项目序号\n");
                system("pause");
                system("cls");
                break;
            }
        }
        p = p->next;
    }


    PrintStudent();
    //如果链表中没有输入的学号所代表的学生，则重新输入
    if(!flag){
        printf("没有这名学生，请重新输入\n");
        system("pause");
        system("cls");
    }

    system("cls");
}

//删除某学生信息
void DeleteStudent(){
    system("cls");

    int num;//学号
    int flag = 0;//判断是否找到该学生
    printf("请输入要删除的学生的学号\n");
    scanf("%d",&num);

    Node *p = Head;//待删除结点
    Node *pre = Head;//待删除结点的前一结点

    //删除结点
    while(p != NULL){
        if(p->stu.num == num){
            flag = 1;//找到该学生

            if(p == Head){//若待删除结点为头结点
                Head = p->next;
            }else if(p->next == NULL){//若待删除结点为尾结点
                pre->next = NULL;
            }else{//若待删除结点为中间结点
                pre->next = p->next;
                p->next = NULL;
            }

            free(p);
        }

        pre = p;
        p = p->next;
    }

    PrintStudent();        
    //未找到该学生
    if(!flag){
        printf("没有这名学生，请重新输入\n");
        system("pause");
        system("cls");
    }

    system("cls");
}

//保存信息
void SaveFile(){
    system("cls");

    //打开文件
    FILE *pfile;
    pfile = fopen(".\\Student.dat","w");

    //打开文件失败
    if(!pfile){
        printf("保存失败\n");
        return ;
    }

    Node *p = Head;

    if(p == NULL){
        system("cls");
        printf("没有能保存的数据\n");
        system("pause");
        return;
    }

    //输入信息
    while(p != NULL){
        fprintf(pfile,"\t%s\t%d\t%d",p->stu.name,p->stu.grade,p->stu.num);
        p = p->next;
    }

    //关闭文件
    fclose(pfile);
    printf("保存成功\n");
    system("pause");
    system("cls");
}

void LoadFile(){
    system("cls");

    //打开文件
    FILE *pfile;
    pfile = fopen(".\\Student.dat","r");

    //打开文件失败
    if(!pfile){
        printf("读取失败\n");
        return ;
    }

    //分配内存
    Node *p = (Node*)malloc(sizeof(Node));
    Node *pre = Head;//
    p->next = NULL;
    Head = p;
    
    //逐行读取数据
    while(fscanf(pfile,"\t%s\t%d\t%d",p->stu.name,&p->stu.grade,&p->stu.num) != EOF){
        Node *NewNode = (Node*)malloc(sizeof(Node));
        NewNode ->next = NULL;
        p->next = NewNode;
        pre = p;
        p = NewNode;
    }

    //最后多申请了一个结点，需要删除
    pre->next = NULL;
    free(p);
    
    //关闭文件
    fclose(pfile);
    printf("读取成功\n");
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


//菜单函数
void menu(){
    //需要退出到主标题界面时才打印主标题界面
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
    printf("\t\t\t欢迎使用学生管理系统\t\t\t\n\n");
    printf("\t\t\t输入对应数字以使用对应的功能\t\t\t\n\n");
    printf("0.退出\n\n1.录入信息\n\n2.打印信息\n\n3.修改某学生信息\n\n");
    printf("4.删除某学生信息\n\n5.保存信息\n\n6.读取信息\n\n");
}

//主函数
int main(){
    int n;//用户输入选择
    while(1){
        Desk://退出到主标题界面的label
        system("cls");
        menu();//桌面
        n = getch();
        switch (n)
        {
        case '0'://退出
            goto Desk;//退出到主标题界面
            break;    
        case '1'://录入信息
            CreatStudent();
            break;
        case '2'://打印信息
            PrintStudent();
            break;
        case '3'://修改信息
            ChangeStudent();
            break;
        case '4'://删除某学生信息
            DeleteStudent();
            break;
        case '5'://保存信息
            SaveFile();
            break;
        case '6'://读取信息
            LoadFile();
            break;
        default:
            printf("没有此功能\n\n");
            system("pause");
            system("cls");
            break;
        }
        system("cls");
        printf("是否退出至主标题界面？\n");
        ChooseAgain://非法输入的label
        printf("0.是\n1.否\n");
        int Temp;//保存输入的是、否数据
        scanf("%d",&Temp);
        if(Temp == 1){
            ReturnFlag = 1;
        }else if(Temp == 0){
            ReturnFlag = 0;
        }else{
            printf("请重新选择\n");
            goto ChooseAgain;//非法输入，重新输入
        }
    }

    return 0;
}
