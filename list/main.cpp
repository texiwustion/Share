// 顺序表基本操作

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 3
#define LIST_INCREMENT 1 // 需要增加的元素个数（该常量在扩大数组长度时用到）

typedef struct
{
    int age;
    int height;
    double weight;
} Student; // 先定义一个结构数组

typedef struct
{
    Student *stu; // 每个数组元素的数据类型
    int length;   // 顺序表中元素个数（学生个数）
    int listsize; // 整个顺序表的长度
} Sqlist;

// 初始化一个线性表
int initList(Sqlist *L)
{
    //  1.申请一个空间
    L->stu = (Student *)malloc(LIST_INIT_SIZE * sizeof(Student));
    //  2.判断是否拿到了空间内存
    if (!L->stu)
        exit(-1);
    //  3.如果拿到了内存空间，则需要初始化顺序表
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;

    return 1;
}

// 销毁顺序表
int deleteList(Sqlist *L)
{
    // 1.判断顺序表是否存在
    if (L->stu == NULL) // 即不存在
        return 0;
    // 2.如果存在，则要释放对应的内存
    free(L->stu);
    // 3.释放内存之后，要恢复表的初始值
    L->length = 0;
    L->listsize = 0;

    return 1;
}

// 遍历顺序表
void findAllList(Sqlist *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("age=%5d  height=%5d  weight=%5lf\n\n", L->stu[i].age, L->stu[i].height, L->stu[i].weight);
    }
}

// 查找数组中的某个元素,如果查找到某个函数将返回1，否则返回0
int findOneList(Sqlist *L, Student *stu)
{
    int i = 0;
    while (i < L->length)
    {
        if (L->stu[i].age == stu->age && L->stu[i].height == stu->height && L->stu[i].weight == stu->weight)
            return 1;
        i++;
    }

    return 0;
}

// 打印成员信息，不需要有返回值
void displayValue(Student *stu)
{
    if (!stu)
        return;                                                                    // 如果为空，不需要打印，直接返回
    printf("age=%5d  height=%5d  weight=%lf\n", stu->age, stu->height, stu->weight); // 存疑，为什么stu.age会报错而stu->age不会报错
    // 因为stu是指针，如果想用.，应该是*（stu）.age
}

// 扩大数组的长度
int extantList(Sqlist *L)
{
    // 1.重新申请内存
    Student *p = (Student *)realloc(L->stu, (L->listsize + LIST_INCREMENT) * sizeof(Student));
    // realloc函数用法：两部分，第一部分写原来申请到的地址，第二部分计算需要的空间，最后把申请到的空间赋给一个新的地址

    // 2.如果p为空，没有申请到，直接退出；如果申请到了，则要更新顺序表的信息
    if (!p)
        exit(-1);
    L->stu = p;
    L->listsize += LIST_INCREMENT;
    return 1;
}

// 复制元素，借助此函数，将需要插入的元素复制到需要从尾部插入的函数的尾部，从而实现插入操作
void copyList(Student *s1, Student *s2)
{
    s1->age = s2->age;
    s1->height = s2->height;
    s1->weight = s2->weight;
}

// 在顺序表的尾部插入元素
void insertLastList(Sqlist *L, Student *stu)
{
    // 1.如果顺序表已满，需要重新申请空间
    if (L->length >= L->listsize)
        extantList(L);
    // 2.如果有足够的空间，则需要在尾部插入新元素
    copyList(&L->stu[L->listsize], stu); //error
    // 3.如果新元素插入，需要更新成员数量
    L->length++;
}

int main(void)
{
    // 1.初始化一个固定用例
    Sqlist *L1;
    // 2.测试相关函数
    initList(L1);//为线性表分配空间并进行初始化

    for (int i = 0; i < L1->listsize; i++)
    {
        printf("请输入年龄，身高和体重：\n");
        scanf("%d %d %lf", &L1->stu[i].age, &L1->stu[i].height, &L1->stu[i].weight);
        L1->length++;
    }

    findAllList(L1); // 遍历顺序表

    Student stu1 = {10, 160, 45};

    printf("从尾部插入stu1：\n");
    insertLastList(L1, &stu1); // 从顺序表的尾部插入一个函数
    findAllList(L1);           // 将整个表打印出来

    // 4.释放顺序表空间
    deleteList(L1);

    return 0;
}
