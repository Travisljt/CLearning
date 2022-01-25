#include <math.h>

#define INIT_SIZE 17
#define ALPHANUM 26
#define OVERLOAD_FACTOR 0.5
#define MAGIC_NUM 102

typedef enum bool{false, true} bool;

typedef struct hashnode
{
    void *data;
    void *key;
    int exist;
} hashnode;

typedef struct assoc
{
    int keysize;
    int cur_size;
    int total_size;
    hashnode *list;
} assoc;

int* get_prime(int* prime);
int next_prime(int n);
int hash_func(assoc* hashmap, char* word, int* prime, int i);
char* int2str(int i);
assoc* resize(assoc* hashmap, int* prime);
void get_primeList(int prime[], int num);
