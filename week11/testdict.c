/*
Trivial testing file for Dictionary; notice it is case-sensitive.
Should work for the any Dictionary implementation
*/
#include "dict.h"

#define BIGSTR 1000

int main(void)
{
   printf("Start!\n");
   assert(!dict_add(NULL, ""));
   printf("finish-1\n");
   assert(!dict_add(NULL, "one"));
   printf("finish-2\n");
   assert(!dict_spelling(NULL, ""));
   printf("finish-3\n");
   assert(!dict_spelling(NULL, "one"));
   printf("finish-4\n");

   dict* d = dict_init(50);
   printf("finish-5\n");
   assert(dict_add(d, "one"));
   printf("finish-6\n");
   assert(dict_add(d, "one"));
   printf("finish-7\n");
   assert(dict_add(d, "two"));
   printf("finish-8\n");

   assert(dict_spelling(d, "one"));
   printf("finish-9\n");
   assert(dict_spelling(d, "two"));
   printf("finish-10\n");
   assert(!dict_spelling(d, "Two"));
   printf("finish-11\n");
   assert(!dict_spelling(d, "One"));
   printf("finish-12\n");
   assert(dict_add(d,"four"));
   printf("finish-13\n");

   dict_free(d);
   return EXIT_SUCCESS;
}
