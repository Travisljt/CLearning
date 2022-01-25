#include "../dict.h"

#include "specific.h"
#define KHASHES 11
#define BIGSTR 1000



unsigned long *_hashes(const char *s)
{
    // You’ll need to free this later
    unsigned long *hashes = ncalloc(KHASHES, sizeof(unsigned long));
    // Use Bernstein from Lecture Notes (or other suitable hash)
    unsigned long bh = _hash(s);
    int ln = strlen(s);
    /* If two different strings have the same bh, then
    we need a separate way to distiguish them when using
    bh to generate a sequence */
    srand(bh * (ln * s[0] + s[ln - 1]));
    unsigned long h2 = bh;
    int i;
    for (i = 0; i < KHASHES; i++)
    {
        h2 = 33 * h2 ^ rand();
        hashes[i] = h2;
    }
    // Still need to apply modulus to these to fit table size
    return hashes;
}

unsigned long _hash(const char *s)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *s++) != 0)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

dict *dict_init(unsigned int maxwords)
{
    dict *d = (dict*)malloc(sizeof(struct dict));
    if (d != NULL)
    {
        d->dict_size = maxwords * 20;
        d->dict_flags = (bool*)malloc((d->dict_size + 1) * sizeof(bool));
    }

    int i;
    for (i = 0; i < d->dict_size; i++)
    {
        d->dict_flags[i] = 0;
    }

    return d;
}

bool dict_add(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }

    unsigned long *position = _hashes(s);
    int i;
    //int position_size = (int)sizeof(position) / sizeof(position[0]);
 
    
        for (i = 0; i < KHASHES; i++)
        {
            x->dict_flags[position[i] % x->dict_size] = 1;
        }
    
    free(position);
    return true;
}

bool dict_spelling(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }

    unsigned long *position = _hashes(s);
    int i;
    int position_size = (int)sizeof(position) / sizeof(position[0]);
    for (i = 0; i < position_size; i++)
    {
        if (x->dict_flags[position[i] % x->dict_size] == 0)
        {
            free(position);
            return false;
        }
    }

    free(position);
    return true;
}

void dict_free(dict *x)
{

        free(x->dict_flags);
        free(x);
    
}

