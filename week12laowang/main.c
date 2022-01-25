#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifdef PARSER
#include "Parser/parser.h"
#else
#include "Interpreter/interpreter.h"
#endif

int main(int argc, char *argv[])
{
    Program *prog = calloc(1, sizeof(Program));
    if (argc >= 2)
    {
        parseFile(argv[1], prog);
        Prog(prog);
    }
    //printf("Parsed OK\n");
    return 0;
}
