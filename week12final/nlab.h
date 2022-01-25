#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define ARRMAX 20
#define LISTSIZE 1000
#define PROGSTART 2
#define VARIABLESIZE 10
#define WORDSIZE 20
#define ALPHASIZE 30
#define TEMSTORE 26

#define strsame(A,B) (strcmp(A,B)==0)

//ADTs Stack linked list
struct node{
  char c[VARIABLESIZE];
  struct node* next;
};
typedef struct node node;

struct stack{
  int num;
  node* top;
};
typedef struct stack stack;

//Data store in Program
struct varn
{
    int arr[ARRMAX][ARRMAX];
    char var[VARIABLESIZE];
    int sizerow;
    int sizecol;
};
typedef struct varn varn;

typedef char* List;

//Program struct
struct prog
{
    List* text;//String read from file
    varn* store;//Data store
    int cword;//current word
};

typedef struct prog Program;

//General function and test
void test(void);
void on_error(const char* s);
void* nfopen(char* fname, char* mode);
void* ncalloc(int n, size_t size);

//Stack functions
stack* stack_initialize(void);
void stack_push(stack* s, char* str);
bool stack_pop(stack* s, char* str);
bool stack_free(stack* s);

//Program initial
Program* prog_initialize(void);
//Program start
void isProgram(char* s);
void prog_free(Program* p);
void nextword(Program* p);

//For 1x1 scale change to the suitable array size
void int2arr(Program* p, char* str1, char* str2);

//Judge the varname if is 1x1 scale or not
bool isscale(Program* p, char* str);

//Judge the words if is the keyword or not
bool isInstrc(Program* p);
bool isCreate(Program* P);
bool isSET(Program* p);
bool isPRINT(Program* p);
bool isLoop(Program* p);
bool isVarname(Program* p);
bool isPolishlist(Program* p);
bool isPolish(Program* p);
bool isPushdown(Program* p);
bool isUnaryop(Program* p);
bool isBinaryop(Program* p);
bool isInteger(Program* p);
bool isString(Program* p);

//Judge the word from stack is number or not
bool isNum(char* str);
//Judge both array is same size or not
bool isSamesize(Program* p, int n, int m);

//main function
void instrclist(Program* p, stack* s);
void instrc(Program* p, stack* s);
void func_ONES(Program* p, stack* s);
void func_SET(Program* p, stack* s);
void polishlist(Program* p,stack* s);
void polish(Program* p, stack* s);
void pushdown(Program* p, stack* s);
void unary(Program* p, stack* s);
void binary(Program* p, stack* s);
void u_NOT(Program* p, stack* s);
void u_EIGHTCOUNT(Program* p, stack* s);
void b_AND(Program* p, stack* s);
void b_OR(Program* p, stack* s);
void b_GREATER(Program* p, stack* s);
void b_LESS(Program* p, stack* s);
void b_ADD(Program* p, stack* s);
void b_TIMES(Program* p, stack* s);
void b_EQUAL(Program* p,stack* s);
void func_PRINT(Program* p);
void func_LOOP(Program* p, stack* s);
void func_READ(Program* p, stack* s);
int func_eightneighbour(Program* p, int n, int row, int col);
void func_file(Program* p, stack* s);




