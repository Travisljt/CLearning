#ifndef MAZE_PROBLEM_H
#define MAZE_PROBLEM_H
#include <stdio.h>
#include<stdbool.h>

#define MAXSIZE 6
//路口结构体定义
struct InterSection {
	int i;//行号
	int j;//列号
	int right;//可走的方位号
} InterSection[MAXSIZE];
void MyPath(char maze[][MAXSIZE], int moved[][MAXSIZE]);

/*顺序表结构体,用于辅助递归函数*/

typedef struct
{
	int list[50][2];
	int size;
}SeqList;
void ListInitiate(SeqList* L);
bool ListInsert(SeqList* L, int x, int y);
bool ListDelete(SeqList* L);
int ListOutput(SeqList* L);

bool RecursMaze(char maze[][MAXSIZE], int moved[][MAXSIZE], SeqList* L, int i, int j);

#endif // !MAZE_PROLBLEM_H
