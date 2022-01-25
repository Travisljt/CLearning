#include "specific.h"

dict* dict_init(unsigned int maxwords)
{
    dict* d = (dict*)ncalloc(1,sizeof(dict));
    d->size = 20*maxwords;
    
    /*Create a big hash table to store the 1 or 0*/
    d->bloom = (unsigned long*)ncalloc(d->size,sizeof(unsigned long));
    for(int i=0; i<d->size; i++)
    {
        /*bloom array initialize*/
        d->bloom[i]=0;
    }

    return d;
}


bool dict_add(dict* x,  const char* s)
{
    if(x==NULL||s==NULL)
    {
       return false;
    }
    
    /*Just insert 1 to the array*/
    unsigned long* cmp = _hashes(s,x);
    for(int i=0; i<KHASHES; i++)
    {
        unsigned long index = cmp[i]%x->size;
        x->bloom[index] = 1;
    }
    free(cmp);
    
    return true;
  
}

bool dict_spelling(dict* x, const char* s)
{
    if(x==NULL||s==NULL)
    {
       return false;
    }
    
    /*Set the flag*/
    bool check = true;
    unsigned long* cmp = _hashes(s,x);

    for(int i=0; i<KHASHES; i++)
    {
        unsigned long index = cmp[i]%x->size;

        /*Check to see if different numbers 
        are returned in the traversal group*/
        if(x->bloom[index]==0)
        {
            check = false;
        }
        
        if(check == false)
        {
            free(cmp);
            return false;
        }
    }
    
    free(cmp);
    return true;
}

/*free all spaces*/
void dict_free(dict* x)
{
   free(x->bloom);
   free(x);
}

unsigned long* _hashes(const char* s, dict* x)
{

    unsigned long* hashes = ncalloc(KHASHES, sizeof(unsigned long));
    unsigned long bh = _hash(s,x->size);
    int ln = strlen(s);
    /* Distiguish two strings which have same hash number
     using bh to generate a sequence */
    srand(bh*(ln*s[0] + s[ln-1]));
    unsigned long h2 = bh;
    for (int i=0; i<KHASHES; i++) {
    h2 = 33 * h2 ^ rand();
    hashes[i] = h2;
    }

    return hashes;
}

unsigned long _hash(const char* str, int tablesize)
{
    /*5381 & 33 are the magic number from Bernstein */
    unsigned long hash = 5381;
    int s;
    while((s=(*str++)))
    {
        hash = 33*hash^s;//XOR will be faster than ADD
    }
    return hash%tablesize;
}



