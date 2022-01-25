#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define SWAP(A,B) {char temp = *A; *A = *B; *B = temp;}
#define START_POINT 2
#define MAXIMUM 5
//#define MAXLIST 5000

struct word
{
   char* arr;
   int len;
};
typedef struct word word;

FILE* File_open(char* filename);
void* my_malloc(int size);
void  print_error(const char* str);
void* my_calloc(int n, size_t size);
void* my_realloc(word* wordslist, int newsize);
void init_word(word* wordslist, int max);
void free_word(word* wordslist);
void copytoarr(word* wordslist,char* str);
void Read_words(FILE* fp, word* wordslist);
void print_word(word* wordslist);

//int argc, char** argv[]

int main()
{
   word* wordslist;
   init_word(wordslist,MAXIMUM);
   char* filename = ("34words.txt");
   FILE* file_pointer = File_open(filename);
   //printf("testnode\n");
   Read_words(file_pointer, wordslist);
   //printf("testnode\n");
   fclose(file_pointer);
   free_word(wordslist);
}


FILE* File_open(char* filename)
{
    FILE* file_pointer = fopen(filename, "r");
    if(file_pointer==NULL){
        print_error("Couldn't open file");
    }
    return file_pointer;
}

void* my_malloc(int size)
{
    void* space = malloc(size);
    if(space==NULL){
        print_error("Couldn't malloc() space");
    }
    return space;
}

void  print_error(const char* str)
{
    fprintf(stderr,"%s\n",str);
    exit(EXIT_FAILURE);
}

void* my_calloc (int n, size_t size)
{
   void* space = calloc(n,size);
   if(space==NULL){
        print_error("Couldn't calloc() space");
    }
    return space;
}

void* my_realloc(word* wordslist, int newsize)
{
    word* new_wordslist = (word*) realloc(wordslist, sizeof(word) * newsize);
    if(new_wordslist==NULL){
        print_error("Couldn't re-allocate new space");
    }
    wordslist = new_wordslist;
    return wordslist;
}

void init_word(word* wordslist, int max)
{
    wordslist = (word*)my_malloc(sizeof(word)*max);
    if(wordslist == NULL)
    {
        print_error("Couldn't initialize the wordslist");
    }
    else
    {
    //wordslist->arr = (char*)my_malloc(sizeof(char)*max);
    wordslist->len = 0;
    }
}

void free_word(word* wordslist)
{
    for(int i =0; wordslist[i].arr;i++)
    {
        free(wordslist[i].arr);
    }
    free(wordslist);
}

void copytoarr(word* wordslist, char* str)
{
   wordslist->len = strlen(str);
   wordslist->arr = (char*)my_malloc(sizeof(char)*(wordslist->len)+1);
   strcpy(wordslist->arr,str);
}

void Read_words(FILE* fp, word* wordslist)
{
   char str[MAXIMUM];
   int storage = MAXIMUM;
    for (int i = 0; fscanf(fp,"%s",str)==true; i++)
  {
      if(i>=storage-1)
      {
          storage *= 2;
          wordslist = my_realloc(wordslist,storage);
      }
      copytoarr(&wordslist[i],str);
      //print_word(wordslist);
  }
}

void print_word(word* wordslist)
{
  for(int i=0;wordslist[i].arr;i++){
      printf("%s\n",wordslist[i].arr);
  }
}