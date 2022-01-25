
#include "specific.h"
#include "../dict.h"


/* The maximum number of words we will want to input.
   Exact : Hashtable will be twice this size
   Approx : Hashtable will be (e.g.) 20 times this size
*/

unsigned long _hash(const char *s)
{
    int i;
    int str_length = strlen(s);
    unsigned int value = 0;
    for(i = 0; i < str_length; i ++){
    value += s[i];
    value = (value*s[i]);
   }
   return value;
}
//hash是一個11個 int 的 array
unsigned long* _hashes(const char* s)
{
                                      // you will need to free this later!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    unsigned long* hashes = (unsigned long *) ncalloc(KHASHES, sizeof(unsigned long));
    //use Bernstein from Lecture Notes(or other suitable has)
    unsigned long bh = _hash(s);
    int ln = strlen(s);
    srand(bh*(ln*s[0]+s[ln-1]));
    unsigned long h2 = bh;
    for(int i = 0; i < KHASHES;i++){
        h2 = 33* h2^rand();
        hashes[i] = h2;
    }
    //still need to apply modulus to these to fit table size
    return hashes;
}






dict* dict_init(unsigned int maxwords)
{
    int total = maxwords*20;
    dict* first = (dict*)ncalloc(1,sizeof(dict));
    first->a = (long long int*)ncalloc(total,sizeof(long long int));
    for(int i = 0; i < total; i ++){
        first->a[i] = 0;
    }
    first ->size= total;
    return first;

}   



bool dict_add(dict* x,  const char* s)
{
    if(x == NULL){
        return false;
    }
    if(s == NULL){
        return false;
    }
    long long int  total = x->size;
    long long int index;
    

    unsigned long* index_number =_hashes(s);
    for(int i = 0; i < KHASHES;i++){
        index = index_number[i]%total;
        x->a[index] = 1;
    }
    free(index_number);
    return true;

}

bool dict_spelling(dict* x, const char* s)
{
    if(x == NULL){
        return false;
    }
    if(s == NULL){
        return false;
    }
    bool duplicate= true;
    long long int compare_index;
    unsigned long* compare_number = _hashes(s);
    int total_words = x->size;



    for(int i = 0; i < KHASHES;i++){
        compare_index = compare_number[i]%total_words;
            if(x->a[compare_index] == 0){
            duplicate = false;
            }
    }
    free(compare_number);
    if(duplicate == false){
        for(int i = 0; i < KHASHES;i++){
        x->a[compare_index] = 1;
        }
        return false;
    }
    else{
        return true;
    }
    
}



void dict_free(dict* x)
{
    free(x->a);
    free(x);
}
















