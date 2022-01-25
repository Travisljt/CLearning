#include "../dict.h"
#include <string.h>
#define MAX_SIZE 46


//定义哈希表
//结构体：分离链表法（separate chain）节点，横向
struct node
{
    char words[MAX_SIZE];
    struct node *next;
};
typedef struct node* LinkList;
//结构体：哈希表
struct dict
{
    int TableSize;      //maxwords * 2
    LinkList *TheLists; //纵向
};

int hash(unsigned int sz, const char *s);
