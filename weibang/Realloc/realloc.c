#include "specific.h"
#include "assoc.h"

assoc* assoc_init(int keysize){
    assoc* a = (assoc*)calloc(1, sizeof(assoc));
    a->cur_size = 0;
    a->total_size = INIT_SIZE;
    a->list = (hashnode*)calloc(a->total_size, sizeof(hashnode));
    a->keysize = keysize;
    a->list->exist = false;
    return a;
}

void assoc_insert(assoc **a, void* key, void* data){
    int hash_index, i = 0;
    int* prime = (int*)calloc(ALPHANUM, sizeof(int));
    int key_init;
    /*turn int into strs*/
    if((*a)->keysize == sizeof(int)){
        key_init = *(int*)key;
        key = int2str(key_init);
    }
    /*need to resize*/
    prime = get_prime(prime);
    if((*a)->cur_size >= (*a)->total_size * OVERLOAD_FACTOR){
        (*a) = resize((*a), prime);
    }
    do{
        hash_index = hash_func(*a, key, prime, i++);
        if(i + (*a)->cur_size >= (*a)->total_size){
            (*a) = resize((*a), prime);
            i = 0;
        }
    }while((*a)->list[hash_index].key != NULL && strcmp((*a)->list[hash_index].key, key) != 0);
    /*insert*/
    if((*a)->list[hash_index].key == NULL){
        (*a)->list[hash_index].key = key;
        (*a)->list[hash_index].data = data;
        (*a)->list[hash_index].exist = true;
        (*a)->cur_size++;
    }
}

assoc* resize(assoc* a, int* prime){
    assoc* new_a = (assoc*)calloc(1, sizeof(assoc));
    int i, j;
    int hash;
    new_a->total_size = next_prime(2 * a->total_size);
    new_a->list = (hashnode*)calloc(new_a->total_size, sizeof(hashnode));
    new_a->keysize = a->keysize;
    for(i = 0; i < a->total_size; i++){
        if(a->list[i].key != NULL){
            j = 0;
            do{
                hash = hash_func(new_a, a->list[i].key, prime, j);
                if (j + new_a->cur_size >= new_a->total_size){
                    new_a = resize(new_a, prime);
                }
                j++;
            }while (new_a->list[hash].key != NULL);
            new_a->list[hash].key = a->list[i].key;
            new_a->list[hash].data = a->list[i].data;
            new_a->cur_size++;
        }
    }
    free(a->list);
    free(a);
    return new_a;
}

int *get_prime(int *prime){
    int i;
    int tmp[26] = {0};
    get_primeList(tmp, MAGIC_NUM);
    for(i = 0; i < ALPHANUM; i++){
        prime[i] = tmp[i];
    }
    return prime;
}

int next_prime(int n){
    int tmp = n + 1, num, flag = 0;
    while(1){
        for (num = 2; ((num < tmp) && (flag == 0)); num++){
            if (tmp % num == 0){
                flag = 1;
            }
        }
        if ((num == tmp) && (flag == 0)){
            return tmp;
        }else{
            tmp++;
            flag = 0;
        }
    }
}

unsigned int assoc_count(assoc* a){
    return a->cur_size;
}

int hash_func(assoc* hashmap, char* key, int* prime, int index){
    int len = strlen(key);
    int i, j, k, cur1, cur2;
    unsigned int hash1, hash2, result, multi, tmp, hash_index;
    result = 0;
    /*get hash1*/
    multi = 1;
    for(i = 0; i < len; i++){
        cur1 = (int)(key[i] - 'a');
        multi *= prime[cur1];
    }
    hash1 = multi;
    /*get hash2*/
    for(j = 0; j < len; j++){
        tmp = 1;
        for(k = 0; k < j; k++){
            tmp += 'a';
        }
        cur2 = (int)(key[j] - 'a');
        result += tmp * cur2;
    }
    result %= hashmap->total_size;
    hash2 = index * result;

    hash_index = (hash1 + hash2) % hashmap->total_size;
    return (int)hash_index;
}

void assoc_free(assoc* map){
    if (map == NULL)
        return;
    else
        free(map);
}

void* assoc_lookup(assoc* a, void* key){
    int i = 0;
    int hash;
    int* prime = (int*)calloc(ALPHANUM, sizeof(int));
    prime = get_prime(prime);
    do{
        hash = hash_func(a, key, prime, i);
        i++;
        if(a->list[hash].key == NULL || i > a->total_size)
            return NULL;
    }while(strcmp(a->list[hash].key, key) != 0);
    return a->list[hash].data;
}

char* int2str(int init_key){
    char* str;
    int len = 0, digit, tmp1, tmp2, i;
    char alphalist[ALPHANUM] = {0};
    for(i = 0; i < ALPHANUM; i++){
        alphalist[i] = 'a'+ i;
    }

    tmp1 = init_key;
    if(init_key == 0){
        str = (char*)calloc(2, sizeof(char));
        str[0] = 'a';
    }else{
        while(tmp1 != 0){
            tmp1 /= ALPHANUM;
            len++;
        }
        str = (char*)calloc(len + 1, sizeof(char));
        tmp1 = init_key;
        for(i = len - 1; i >= 0; i--){
            tmp2 = (int)pow(ALPHANUM, i);
            digit = tmp1 / tmp2;
            str[len - i - 1] = alphalist[digit];
            tmp1 %= tmp2;
        }
        str[len] = '\0';
    }
    return str;
}

void get_primeList(int prime[], int num){
    int i, j;
    int k = 0;
    int ret;
    for(i = 2; i < num; i++){
        ret = 1;
        for(j = i - 1; j > 1; j--){
            if(i%j == 0){
                ret = 0;
            }
        }
        if(ret == 1){
            prime[k] = i;
            k++;
        }
    }
}
