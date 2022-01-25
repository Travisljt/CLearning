#include  "../dict.h"
#include "specific.h"


/* The maximum number of words we will want to input.
   Exact : Hashtable will be twice this size
   Approx : Hashtable will be (e.g.) 20 times this size
*/
dict* dict_init(unsigned int maxwords)
{
    int i;
    dict* Hash_Table = NULL;
    int length = maxwords*2;
    Hash_Table = (dict*)ncalloc(1,sizeof(dict));
    Hash_Table->table= (node**)ncalloc(length,sizeof(node*));
    


    // Hash_Table = (dict*)malloc(sizeof(dict));
    // Hash_Table->table = (node**)malloc(length*sizeof(node*));

    for(i = 0; i < length; i ++){
        Hash_Table->table[i] = (node*)ncalloc(1,sizeof(node));
        Hash_Table->table[i]->next = NULL;
     }
    Hash_Table->size = length;
    return Hash_Table;

}



/* Add string to dictionary
   Exact : A deep-copy is stored in the hashtable only if the word
           has not already been added to the table.
   Approx : Multiple hashes (e.g. 11) are computed and corresponding
            Boolean flags set in the Bloom hashtable. 
*/



bool dict_add(dict* x,  const char* s)
{ 
    static int count = 0;
    count ++;
    // printf("輸入了幾個 %d\n",count);
    if(x == NULL){
       
        return false;
    }
    if(s == NULL){
        return false;
    }
    int i;
    int value = 0;
    int str_length = strlen(s);
    int Table_size = x->size;
    
    
//algo
    
    
   for(i = 0; i < str_length; i ++){
      value += s[i];
      value = (value*s[i])%Table_size;
   }

   //copy word in to f
        char copy_word[50];
        for(int i = 0; i < str_length;i++){
            copy_word[i] = s[i];
        }
        copy_word[str_length] = '\0';

        //move to f
        node* f = ncalloc(1,sizeof(node));
        f->value = value; //value進去
        for(i = 0; i < str_length; i ++){
            f->key[i] = copy_word[i];
        }
        
        


//add
//如果hash table是空的
    if(x->table[value] == NULL){
        // printf("這是空的 所以加進去 然後這是value%d\n",value);
        x->table[value] = f;
        return true;
    }
    else{
        node* tmp = x->table[value];
        do{
            if(strcmp(tmp->key,s) == 0){
                free(f);// printf("這是一樣的不用加 %s\n",x->table[value]->key);
                return true;
        }
        tmp = tmp->next;
        }while(tmp!=NULL);

        f->next = x->table[value];
        x->table[value] = f;
        // printf("這是加進去的喔喔喔喔喔喔喔 value是%d\n",value);
        return true;
 
    }
        
    // return false;
}


/* Returns true if the word is already in the dictionary,
   false otherwise.
*/


bool dict_spelling(dict* x, const char* s)
{
    if(x == NULL){
        // printf("有到！");
        return false;
    }
    if(s == NULL){ //???
        return false;
    }
    int i;
    int str_length = strlen(s);
    int value = 0;
    int Table_size = x->size;
    for(i = 0; i < str_length; i ++){
      value += s[i];
      value = (value*s[i])%Table_size;
   }
    
    if(x->table[value] == NULL){
        return false;
    }
    
    
   




    node* tmp = x->table[value];
    // printf("%s\n",tmp->key);
    bool collision = false;
    do{
        if(strcmp(tmp->key,s) == 0){
            collision = true;
            // printf("有重複\n");
            return true;
            
        }
    tmp = tmp->next;
    }while(tmp!=NULL);
    // printf("沒有重複\n");
   return false;


}







/* Frees all space used */

void dict_free(dict* x)
{
    int i;
    int Table_size = x->size;
    for(i = 0; i < Table_size; i++){
            node* p = x->table[i];
            node* tmp;
            while(p){
                tmp = p;
                p = tmp->next;
                free(tmp);
            }
            
        
    }
    free(x->table);
    free(x);
}






