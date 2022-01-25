#include "../dict.h"

/*The longiest word has 45 letters*/
#define LONGWORD 45

/*Define the list*/
struct listnode{
   char word[LONGWORD];
   struct listnode* next;
};
typedef struct listnode list;
typedef list* position;

/*Define the dictionary*/
struct dict{
   int tablesize;
   position* Thelist;
};

/*Bernstein hash function*/
int hash_func(const char* str, int tablesize);

/*Some test*/
void test(void);

