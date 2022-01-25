#pragma once

#include "../Stack/stack.h"
#include "../Include/var.h"

#define FORMATSTR "%d"
#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#define MAXLENS 5
#define VARSIZE 26
#define strsame(A, B) (strcmp(A, B) == 0)
#define ERROR(PHRASE)                                               \
    {                                                               \
        fprintf(stderr,                                             \
                "Fatal Error %s occurred in %s, line %d\n", PHRASE, \
                __FILE__, __LINE__);                                \
        exit(EXIT_FAILURE);                                         \
    }

struct prog
{
    char wds[MAXNUMTOKENS][MAXTOKENSIZE];
    int cw; // Current Word
};

typedef struct prog Program;

static Variable vars[VARSIZE];

void parseFile(char *path, Program *p);
void Prog(Program *p);
void Insterclist(Program *p);
void Instrc(Program *p);
bool isPrint(Program *p);
bool isSet(Program *p);
bool isCreate(Program *p);
bool isLoop(Program *p);
void Loop(Program *p);
bool isVarname(Program *p);
char getVarname(Program *p);
void printVar(Variable var);
bool isString(Program *p);
void getString(Program *p, char *string);
void printSring(Program *p);
void Polishlist(Program *p, stack *s, int index);
void Polish(Program *p, stack *s);
bool UnaryOp(Program *p, stack *s);
bool BinaryOp(Program *p, stack *s);
bool Pushdown(Program *p, stack *s);
bool isInteger(Program *p);
int getInteger(Program *p);
void BinOperator(stack *s, char op);
void UnOperator(stack *s, char op);
