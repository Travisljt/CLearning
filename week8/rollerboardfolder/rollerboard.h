#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define JUMP -1 //For temp to out of loop

//Direction
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN  3

#define MAX 6
#define MAXIUM 100
#define STORE 500
#define LARGE 10000000


char* temp_p;//Return for receiving fgets

/*Define the structure roller, 
the elements inside include the chessboard, 
the height and width of the chessboard, the flag symbol,   
the array element number pointing to the parent chessboard*/
struct roller
{
    char arr[MAX][MAX];
    int row;
    int col;
    int flag;
    int parent;
};
typedef struct roller roller;

//open a File function
FILE* file_open(char* filename);

//print an error and exit function
void  print_error(const char* str);

//initial malloc space function
void* my_malloc(int size);

//Algorithm fucntion, it is Similar to BFS
int move_num(char* s,roller* st);

//print each part of the rollerboard
void print_move(roller* st,int move);

//test function
void test(void);

//Check the first line of file
bool vaildline(char* str);

//check the rollerboard is vaild or not
bool vaildboard(int num1, int num2, char* str);

//copy rollerboard from file to the roller structure
void copytoarr(roller* r, FILE* fp);

//Initialize the rollerboard
roller* ini_roll(int num);

//Got the consequence rollerboard
void consequence(roller* r,roller* conseq);

//Give a direction and row, make it roll left or right
roller row_left_right(roller* r, int d, int row);

//Give a direction and coloum, make it roll up or down
roller col_up_down(roller*r,int d, int col);

//Check if it is same rollerboard or not
bool isSame(const roller* parent, const roller* child);

//Transfer the rollerboard
roller arrtoarr(roller* r);

//Print nosolution
void print_nosolution(roller* r, roller* h);
