#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define SIZE 10
#define MAXNUMTOKEN 500
#define MAXTOKENSIZE 50
#define strsame(A,B) (strcmp(A,B)==0)
#define ERROR(PHRASE) { fprintf(stderr,"Fatal Error %s occurred in %s, line %d\n",PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define ALPHABET 26
#define LIST 30

struct node{
  char c[10];
  struct node* next;
};
typedef struct node node;

struct stack{
  int num;
  node* top;
};
typedef struct stack stack;

typedef struct store
{
    int arr[MAXTOKENSIZE][MAXTOKENSIZE];//     $I = 1 ;    !!! 1 = arr[0][0]=1;
    int row;//row = 1;!!
    int col;//col = 1;!!
}store;


struct prog{
    char wds[MAXNUMTOKEN][MAXTOKENSIZE];
    int cw;
    store list[LIST];//list[0] - - "A"
 
};
typedef struct prog prog;

void on_error(const char* s);
void* ncalloc(int n, size_t size);
void Start_Program(prog* p);
void Instrclist(prog* p, stack* s);
void Instrc(prog* p,stack* s);
void Print(prog* p);
void Varname(prog* p);
void String(prog* p);
void Set(prog* p, stack* s);
void Polishlist(prog* p,stack* s);
void Polish(prog* p, stack* s);
void Pushdown(prog* p, stack* s);
void Integer(prog* p);
void Binaryop(prog* p, stack* s);
void Unaryop(prog* p, stack* s);
void Create(prog* p,stack* s);
void Read(prog* p,stack* s);
void Filename(prog* p,stack* s);
void Loop(prog* p,stack* s);




prog* isprogram(char* argv[]);
bool Isinstrc(prog* p);
void stack_push(char* p,stack* s);
void stack_pop(char* tem, stack* s);
//void stack_initialize
//void stack_free
bool stack_free(stack* s);
bool boolNum(char* str);
void arr(prog* p, char* str1, char* str2);
bool Check_row_and_col(prog* p, int a, int b);
void U_NOT(prog* p,stack* s);
void U_EIGHTCOUNT(prog* p,stack* s);
int U_EIGHTAROUND(prog* p, int i, int j, int a);
void B_AND(prog* p,stack* s);
void B_OR(prog* p,stack* s);
void B_GREATER(prog* p,stack* s);
void B_LESS(prog* p,stack* s);
void B_ADD(prog* p,stack* s); 
void B_TIMES(prog* p,stack* s);
void B_EQUALS(prog* p,stack* s);

