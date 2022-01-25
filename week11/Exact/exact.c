#include "specific.h"

/*dictionary initilize*/
dict* dict_init(unsigned int maxwords)
{
   dict* d = (dict*)ncalloc(1,sizeof(dict));
   d->tablesize = maxwords*2;
   /*Create the hash table*/
   d->Thelist = (position*)ncalloc(d->tablesize,sizeof(position));

   /*Allocate space for all cells*/
   for(int i=0;i<d->tablesize;i++)
   {
       d->Thelist[i]=(list*)ncalloc(1,sizeof(list));
       d->Thelist[i]->next = NULL;
   }
   return d;
}


bool dict_add(dict* x,  const char* s)
{
   position newp, l;
   if(x==NULL||s==NULL)
   {
       return false;
   }
   
   /*Check if it is a duplicate word*/
   if(!dict_spelling(x,s))
   {
       newp = (position)ncalloc(1,sizeof(list));
       strcpy(newp->word,s);
       l = x->Thelist[hash_func(s,x->tablesize)];
       
       /*Check the position of each 
       pointer until find the end*/
       while(l->next)
       {
           l = l->next;
       }
       /*Insert the word at the end*/
       newp->next = l->next;
       l->next = newp;
   }
   
   return true;
}

bool dict_spelling(dict* x, const char* s)
{
    if(x==NULL||s==NULL)
   {
       return false;
   }

   position l = x->Thelist[hash_func(s,x->tablesize)];
   
   /*Start looking for the same word 
   in the next case in this position*/
   position p = l->next;
   while(p)
   {
       if(strcmp(s,p->word)==0)
       {
           return true;
       }
       p = p->next;
   }

   return false;
}

void dict_free(dict* x)
{
    for(int i=0;i<x->tablesize;i++)
   {
       /*Frees space for all Pointers in the linked list*/
       position q, p = x->Thelist[i];
        while(p)
        {
            q = p;
            p = q->next;
            free(q);
        }
   }
   free(x->Thelist);
   free(x);
}

int hash_func(const char* str, int tablesize)
{
    /*5381 & 33 are the magic number from Bernstein */
    unsigned long hash = 5381;
    for(int i=0;str[i];i++)
    {
        hash = 33*hash^str[i];//XOR will be faster than ADD
    }
    return (int)(hash%tablesize);
}

void test(void)
{
   assert(hash_func("one",100)==61);
   assert(hash_func("two",100)==53);
   assert(hash_func("three",100)==51);
   assert(hash_func("four",100)==87);
}
