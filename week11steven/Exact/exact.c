#include "../dict.h"
#include "specific.h"

dict* dict_init(unsigned int maxwords){
    int arr_len = maxwords * 2;

    dict* hash_table = malloc(sizeof(dict));
    if(hash_table == NULL){
        return NULL;
    }

    hash_table->dict_table = malloc(sizeof(table*) * arr_len);
    if(hash_table->dict_table == NULL){
        return NULL;
    }

    for(int i = 0; i < arr_len; i++){
        hash_table->dict_table[i] = NULL;
    }
    hash_table->dict_size = arr_len;


    return hash_table;
}

bool dict_add(dict* x,  const char* s){
    if(x == NULL){
        return false;
    }

    table* node = malloc(sizeof(struct table));

    int str_length = strlen(s);

    int sum = 0;

    node->next = NULL;
    for(int i = 0; i < str_length; i++){
        node->string[i] = s[i];
        sum = sum + s[i];
    }

    int index = sum%x->dict_size;

    if(x->dict_table[index] == NULL){
        strcpy(node->string, s);
        node->next = x->dict_table[index];
        x->dict_table[index] = node;
        // printf("%s\n", x->dict_table[index]->string);
    }else{
        table *check = x->dict_table[index];
        
        do{
            if(strcmp(check->string, s) == 0){
                free(node);
                return true;
            }
            check = check->next;
        }while(check != NULL);
        
        strcpy(node->string, s);
        node->next = x->dict_table[index];
        x->dict_table[index] = node;
    }

    return true;
}

bool dict_spelling(dict* x, const char* s){
    if(x == NULL){
        return false;
    }

    int str_length = strlen(s);

    int sum = 0;

    for(int i = 0; i < str_length; i++){
        sum = sum + s[i];
    }

    int index = sum%x->dict_size;

    if(x->dict_table[index] == NULL){
        return false;
    }else{
        table *check = x->dict_table[index];
        
        do{
            if(strcmp(check->string, s) == 0){
                return true;
            }
            check = check->next;
        }while(check != NULL);
    }

    return false;
}

void dict_free(dict* x){     
    for(int i = 0; i < x->dict_size; i++){
        if(x->dict_table[i] != NULL){
            table* check = x->dict_table[i]; 
            while(check!=NULL){
                table* tmp = check->next;
                free(check);
                check = tmp;
            }
        }
    }
    free(x->dict_table);
    free(x);
}

