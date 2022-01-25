#include "MazeProblem.h"
//µ›πÈ µœ÷
bool RecursMaze(char maze[][MAXSIZE], int moved[][MAXSIZE], SeqList* L,int i, int j) {
	if (i < 0 || j < 0 || i >= MAXSIZE || j >= MAXSIZE||moved[i][j]==1)return false;
	if ((i == MAXSIZE - 1) && (j == MAXSIZE - 1))return true;
	if (maze[i][j] == '*')return false;
	moved[i][j] = 1;
	ListInsert(L, i, j);
	if (RecursMaze(maze, moved,L, i-1, j))return true;
	if (RecursMaze(maze, moved,L, i, j+1))return true;
	if (RecursMaze(maze, moved,L, i+1, j))return true;
	if (RecursMaze(maze, moved,L, i, j-1))return true;
	ListDelete(L);
	return false;
}
