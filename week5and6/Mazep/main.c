/*
Maze problem
*Use n*m ​​matrix to describe the maze
* (0,0) represents the exit, n and m respectively represent the number of rows and columns of the maze
* There are obstacles in the matrix, its value is ‘*’ otherwise it is ‘’
*/
/*
	Claim
*Find a path from the entrance <0,0> to the exit <5,5>
* Use recursion and backtracking to achieve two solutions separately
*/
#include "MazeProblem.h"
int main() {
	//迷宫数组
	char maze[MAXSIZE][MAXSIZE] = {
		{' ',' ',' ',' ','*',' '},
		{' ','*','*','*',' ',' '},
		{' ',' ','*',' ',' ','*'},
		{'*',' ',' ',' ','*',' '},
		{'*','*',' ','*','*',' '},
		{'*','*',' ',' ',' ',' '},
	};
	//记录是否已访问的数组
	int moved[MAXSIZE][MAXSIZE] = { 0 };
	//MyPath(maze, moved);

	SeqList	MyTest;
	ListInitiate(&MyTest);
	RecursMaze(maze, moved,&MyTest ,0, 0);
	ListOutput(&MyTest);


}
