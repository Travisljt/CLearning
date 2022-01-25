#include "../general.h"

struct dict
{
    int dict_size;
    bool *dict_flags;
};
unsigned long* _hashes(const char *s);
unsigned long _hash(const char *s);
