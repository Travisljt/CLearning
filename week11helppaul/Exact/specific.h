
#pragma once
#include "../dict.h"
#define STRINGSIZE 40
struct node{
    char key[STRINGSIZE];
    int value;
    struct node *next;
};
typedef struct node node;


struct dict{
    int size;
    struct node **table;
};

