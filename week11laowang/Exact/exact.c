#include "specific.h"

//哈希表初始化
dict *dict_init(unsigned int maxwords)
{
    dict *d;
    
    d = (dict*)malloc(sizeof(struct dict));
    if (d == NULL)
        printf("Out of Space!!");

    d->TableSize = maxwords*2;

    d->TheLists = (LinkList*)malloc(sizeof(LinkList) * d->TableSize);
    if (d->TheLists == NULL)
        printf("Out of Space!!");

    //header
    int i = 0;
    for (i = 0; i < d->TableSize; i++)
    {
        d->TheLists[i] = (LinkList)malloc(sizeof(struct node));
        if (d->TheLists[i] == NULL)
        {
            printf("Out of Space!!\n");
        }
            d->TheLists[i]->next = NULL;
        
    }

    return d;
}

int hash(unsigned int sz, const char *s)
{
    unsigned long hash = 5381;
    int c;
    while ((c = (*s++)))
    {
        hash = 33 * hash ^ c;
    }

    return (int)(hash % sz);
}

bool dict_add(dict *x, const char *s)
{
    if(x == NULL||s == NULL)
    {
        return false;
    }

    bool isExist;
    LinkList P, L;

    isExist = dict_spelling(x, s);
    if (!isExist)
    {
        P = (LinkList)malloc(sizeof(struct node));
        if (P == NULL)
        {
            printf("Out of Space!!!");
        }
    
        strcpy(P->words,s);
        L = x->TheLists[hash(x->TableSize, s)];

        while(L->next)
        {
            L = L->next;
        }
        P->next = L->next;
        L->next = P;
    }
    

    return true;
}

bool dict_spelling(dict *x, const char *s)
{
    if (x == NULL||s == NULL)
    {
        return false;
    }

    LinkList L, P;

    L = x->TheLists[hash(x->TableSize, s)];
    P = L->next;

    if (P)
    {
        if(strcmp(P->words, s)==0)
        {
            return true;
        }
  
        P =  P->next;
    }

    return false;
}

void dict_free(dict* x)
{
    int i;
    for ( i = 0; i < x->TableSize; i++)
    {
        LinkList tmp, p = x->TheLists[i];

        while(p)
        {
            tmp = p;
            p = tmp->next;
            free(tmp);
        }
    }

    free(x->TheLists);
    free(x);
}
