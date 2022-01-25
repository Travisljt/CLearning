#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define MAXIMUM 46
#define MAXLIST 50000
#define SWAP(A,B) {char temp = *A; *A = *B; *B = temp;}

struct word
{
   char arr[MAXIMUM];
   int len;
};

typedef struct word word;
int cnt = 0;
void copytoarr(word* w, char* str);
void isAnagram(word* w, char* str);
void permute(char* a, int s, int e, const word* w);
void test(void);

int main(int argc, char *argv[])
{
  word list[MAXLIST];
  char str[MAXIMUM];
  int numberofword = 0;

  if(argc != 2){
      fprintf(stderr,"Miss word:%s <word>\n",argv[0]);
      exit(EXIT_FAILURE);
  }
  
  FILE* fp = fopen("34words.txt","r");
  //FILE* fp= fopen("draw-fromHarry.c","r");
  if(fp==NULL){
      fprintf(stderr,"Error:Can not open the file\n");
      exit(EXIT_FAILURE);
  }
  
  for (int i = 0; fscanf(fp,"%s",str)==true; i++)
  {
      copytoarr(&list[i],str);
      numberofword = i;
  }
  //printf("testnode1\n");
  //test();
  //fprintf(stdout,"It has %d words\n",numberofword);
  /*
  for(int i=0; i<=numberofword;i++){
      printf("%s\n",list[i].arr);
  }
  */
  for(int i=0;i<=numberofword;i++){
    isAnagram(&list[i],argv[1]);
      //fprintf(stdout,"%d:%s\n",cnt,list[i].arr); 
  }
  printf("\n");
  //printf("testnode2\n");
  if(cnt>0){
  fprintf(stdout,"There is %d anagram word\n",cnt);
  } 
  else{
      fprintf(stderr,"There is no anagram word\n");
  } 
 
  fclose(fp);
  exit(EXIT_SUCCESS);
}

void copytoarr(word* w,char* str)
{
   strcpy(w->arr,str);
   w->len = strlen(str);
}

void isAnagram(word* w, char* str)
{
    int l = strlen(str);
    char * tmp = str;
    permute(tmp,0,l-1,w);
}

void permute(char* a, int s, int e, const word* w)
{
    if(s == e){
        if(strcmp(a,w->arr)==0)
        {
            fprintf(stdout,"%s\n",w->arr); 
            cnt++;
        }
        return;
    }

    for(int i = s; i<=e;i++){
        SWAP((a+s),(a+i));
        permute(a,s+1,e,w);
        SWAP((a+s),(a+i));
    }
}

void test(void)
{
    
}