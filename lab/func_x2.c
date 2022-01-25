#include "common.h"

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
          buf[cnt]=s1[i];
          cnt++;
      }   
   }

   for(int i=0;i<len-1;i++)
   {

       if(buf[i]>buf[i+1])
       {
           return false;
       }
   }
   
    return true;

}