#include "../dict.h"

#define STRLEN 50

struct table {
    char string[STRLEN];
    struct table *next;
};

typedef struct table table;

struct dict {
    int dict_size;
    struct table **dict_table;
} Dict;



