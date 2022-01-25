#include<stdlib.h>
#include<stdio.h>

struct student {
    int score;
    struct student *next;
};
typedef struct student NODE; //typedef为C语言的关键字&#xff0c;作用是为一种数据类型定义一个新名字。简化一些比较复杂的类型声明。

NODE *create(); //创建链表
void insert(NODE *head, NODE *pnew, int i); //插入
void delete(NODE *head, int i); //删除
void allClear(NODE *head); //清除链表的所有节点&#xff0c;包含头节点。
void display(NODE *head); //打印链表

int main() {
    NODE *head, *pnew;
    
    //创建链表
    head = create();
    
    //打印链表
    display(head);
    
    //插入一个新节点
    pnew = (NODE*)malloc(sizeof(NODE));
    pnew->score = 99;
    insert(head, pnew, 1);
    
    //打印链表
    display(head);
    
    //删除
    delete(head, 0);
    
    //打印链表
    display(head);
    
    //清除链表的所有节点&#xff0c;包含头节点。
    allClear(head);
    
    //打印链表
    display(head);
    
    return 0;
}

//创建链表
NODE *create() {
    NODE *head, *tail, *pnew;
    int score;
    head = (NODE*)malloc(sizeof(NODE)); //创建头节点。
    if (head == NULL) {
        printf("创建失败!");
        return NULL;
    }
    head->next = NULL;
    tail = head;
    printf("输入学生成绩: ");
    while (1) {
        scanf("%d", &score);
        if (score < 0) //成绩为负是退出循环
            break;
        pnew = (NODE*)malloc(sizeof(NODE)); //创建新节点
        if (pnew == NULL) {
            printf("创建失败!");
            return  NULL;
        }
        pnew->score = score;
        pnew->next = NULL;
        tail->next = pnew; //新节点插入到表尾
        tail = pnew; //为指针指向当前的尾节点
    }
    printf("返回头节点");
    return head;
}

//插入 头结点不算&#xff0c;从有数据的开始算第一个
void insert(NODE *head, NODE *pnew, int i) {
    NODE *p = head;
    int j;
    for (j = 0; j < i && p != NULL; j++) {
        p = p->next;
        if (p == NULL) {
            printf("\n与插入的节点不存在!");
            return;
        }
    }
    pnew->next = p->next;
    p->next = pnew;
}

//删除 头结点不算&#xff0c;从有数据的开始算第一个
void delete(NODE *head, int i) {
    NODE *p = head, *pnew;
    int j;
    for (j = 0; j < i && p != NULL; j++) {
        p = p->next;
        if (p == NULL) {
            printf("\n删除的节点不存在!");
            return;
        }
    }
    pnew = p->next;
    p->next = pnew->next;
    free(pnew);
}

//清除链表的所有节点&#xff0c;包含头节点。
void allClear(NODE *head) {
    NODE *p, *q;
    p = head;
    while (p->next != NULL) {
        q = p->next;
        p->next = q->next;
        free(q);
    }
    free(head); //最后删除头节点
}

//打印链表
void display(NODE *head) {
    printf("\n学生成绩分别是:");
    NODE *p;
    for (p = head->next; p != NULL; p = p->next) {
        printf("%d ", p->score);
    }
}