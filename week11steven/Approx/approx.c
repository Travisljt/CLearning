#include "../dict.h"
#include "specific.h"

#define KHASHES 11

unsigned long _hash(const char *s)
{
    int str_length = strlen(s);

    unsigned long sum = 0;

    for(int i = 0; i < str_length; i++){
        sum = sum + s[i];
        sum = sum * sum;
    }
    return sum;
}

unsigned long* _hashes(const char* s) 
{
    // You’ll need to free this later
    unsigned long* hashes = ncalloc(KHASHES, sizeof(unsigned long)); 
    // Use Bernstein from Lecture Notes (or other suitable hash)

    unsigned long bh = _hash(s);

    int ln = strlen(s);
    /* If two different strings have the same bh, then
    we need a separate way to distiguish them when using
    bh to generate a sequence */

    srand(bh*(ln*s[0]+s[ln-1])); 
    unsigned long h2 = bh;
    for (int i=0; i<KHASHES; i++) 
    { 
        h2 = 33 * h2 ^ rand(); 
        hashes[i] = h2;
    }
    // Still need to apply modulus to these to fit table size
    return hashes;
}

dict* dict_init(unsigned int maxwords){
    int arr_len = 20 * maxwords;

    dict* hash_table = malloc(sizeof(dict));
    if(hash_table == NULL){
        return NULL;
    }

    hash_table->size = arr_len;

    hash_table->arr = (long long int*)malloc(sizeof(long long int) * arr_len);

    for(int i = 0; i < arr_len; i++){
        hash_table->arr[i] = 0;
    }

    return hash_table;
}

bool dict_add(dict* x,  const char* s){
    if(x == NULL){
        return false;
    }

    unsigned long* number = _hashes(s);
    
    long long int arr_size = x->size;

    for(int i = 0; i < KHASHES; i++){
        long long int index = number[i]%arr_size;
        x->arr[index] = 1;
    }

    free(number);
    return true;
}

bool dict_spelling(dict* x, const char* s){
    if(x == NULL){
        return false;
    }

    unsigned long* number = _hashes(s);
    
    long long int arr_size = x->size;

    for(int i = 0; i < KHASHES; i++){
        long long int index = number[i]%arr_size;

        if(x->arr[index] == 0){
            free(number);
            return false;
        }
    }
    free(number);
    return true;
}

void dict_free(dict* x){
    free(x->arr);
    free(x);
}
