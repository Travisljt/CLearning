#include "../dict.h"

/*Coefficient k*/
#define KHASHES 11

/*Define the dictionary*/
struct dict
{
    int size;
    unsigned long* bloom;
};

/*Hash function*/
unsigned long* _hashes(const char* s, dict* x);
unsigned long _hash(const char* str, int tablesize);

