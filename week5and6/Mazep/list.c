#include"MazeProblem.h"
//��ʼ��˳���
void ListInitiate(SeqList* L)
{
	L->size = 0;
}
//��������Ԫ��
bool ListInsert(SeqList* L, int x, int y)
{
	L->list[L->size][0] = x;
	L->list[L->size][1] = y;
	L->size++;
	return true;
}
//ɾ������Ԫ��
bool ListDelete(SeqList* L)
{
	L->list[L->size][0] = -1;
	L->list[L->size][1] = -1;
	L->size--;
	return true;
}
//�������Ԫ��
int ListOutput(SeqList* L)
{
	for (int x = 0; x < L->size; x++)
	{
		printf("(%d,%d) ", L->list[x][0], L->list[x][1]);

	}
	return true;
}
