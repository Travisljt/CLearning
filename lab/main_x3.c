/*
   s2 : A copy of the string s1, but with the position of the
   letters (only) reversed. Any non-letters (punctuation, spaces etc.)
   are unmoved. Case of letters is unchanged.
*/

#include "common.h"

void strrevletters(const char* s1, char* s2);

int main(void)
{

   char str[1000];

   strrevletters("a", str); assert(strcmp(str, "a")==0);
   strrevletters("abc", str); assert(strcmp(str, "cba")==0);
   strrevletters("ABC", str); assert(strcmp(str, "CBA")==0);
   strrevletters("a z", str); assert(strcmp(str, "z a")==0);
   strrevletters("ab*c", str); assert(strcmp(str, "cb*a")==0);
   strrevletters("!=a b=?", str); assert(strcmp(str, "!=b a=?")==0);

   return 0;
}
