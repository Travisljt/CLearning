#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


/*
   Tests whether string s1 contains alphabetical
   characters which are ordered i.e. the next letter
   is alphabetically >= to the current one. All non-letters
   (e.g. spaces, punctuation etc.) are ignored..
*/

bool strsorted(const char* s1);

int main(void)
{

   
   assert(strsorted("abc"));
  assert(strsorted("AbC"));
   assert(strsorted("AAA"));
   assert(strsorted("A-AZ-"));
   assert(strsorted("a m z !"));

  assert(!strsorted("cba"));
  assert(!strsorted("CbA"));
  assert(!strsorted("!Cb *A!"));

   return 0;
}

bool strsorted(const char* s1)
{
   int len = (int)strlen(s1);
   char buf[26];
   int cnt=0;
  // int check=0;
   for(int i=0;i<len;i++)
   {   
      if(isalpha(s1[i]))
      {
          buf[cnt]=tolower(s1[i])-'a';
          cnt++;
      }   
      
   }
   
   for(int i=0;i<cnt-1;i++)
   {

       if(buf[i]>buf[i+1])
       {
           return false;
       }
   }
   
    return true;

}