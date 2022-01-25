#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

char* strnodupes(const char* s);

int main(void)
{

   char* s2;

   s2 = strnodupes("Hello World!");
   assert(strcmp("Helo Wrd!", s2)==0);
   free(s2);
   s2 = strnodupes("a-aaaaaAAAAAAAAaaaaaaaa");
   assert(strcmp("a-A", s2)==0);
   free(s2);
   s2 = strnodupes("HHiHHiiidiHiHiedHidiHi");
   assert(strcmp("Hide", s2)==0);
   free(s2);
   s2 = strnodupes("Subdermatoglyphic");
   assert(strcmp("Subdermatoglyphic", s2)==0);
   free(s2);

   return 0;
}

char* strnodupes(const char* s)
{
    char* st = (char*)calloc(sizeof(char*),(int)strlen(s));
    int len = (int)strlen(s);
    //int buf[20];
    //int cnt=1;
    st[0]=s[0];
    int k = 1;
   for(int j = 0; j < len; j++){
     int diff_times = 0;
       for(int i = 0; i < k; i++){
         if(s[j] != st[i]){
           diff_times++;
        }
      }
      if(diff_times == k){
         st[k] = s[j];
          k++;
      }
    }
    st[k] = '\0';
   
    for(int i=0;i<(int)strlen(st);i++)
       { printf("%c",st[i]);}
       printf("\n");
     return st;
    
}