#pragma once

#define MAXVARSIZE 20
#define MAXROWSIZE 20
#define MAXCOLUMNSIZE 20

struct var{
    int value[MAXROWSIZE][MAXCOLUMNSIZE];
	int row;
	int column;
	bool flag;
};

typedef struct var Variable;

