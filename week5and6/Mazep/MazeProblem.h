#ifndef MAZE_PROBLEM_H
#define MAZE_PROBLEM_H
#include <stdio.h>
#include<stdbool.h>

#define MAXSIZE 6
//·�ڽṹ�嶨��
struct InterSection {
	int i;//�к�
	int j;//�к�
	int right;//���ߵķ�λ��
} InterSection[MAXSIZE];
void MyPath(char maze[][MAXSIZE], int moved[][MAXSIZE]);

/*˳���ṹ��,���ڸ����ݹ麯��*/

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
