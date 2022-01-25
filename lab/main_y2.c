/*
   For a 5x5 square integer array, return the
   number of unique integers that are in the array.
   Make no assumptions about the maximum or minimum
   number that can occur.
*/

#include "common.h"

int uniquenums(const int a[5][5]);

int main(void)
{

   // Only contains one number (10)
   const int a[5][5] = {
                   {10, 10, 10, 10, 10},
                   {10, 10, 10, 10, 10},
                   {10, 10, 10, 10, 10},
                   {10, 10, 10, 10, 10},
                   {10, 10, 10, 10, 10}
                  };
   assert(uniquenums(a)==1);

   // Contains three unique numbers (10,11,12)
   const int b[5][5] = {
                   {10, 11, 12, 10, 11},
                   {10, 11, 12, 10, 11},
                   {10, 11, 12, 10, 11},
                   {10, 11, 12, 10, 11},
                   {10, 11, 12, 10, 11}
                  };
   assert(uniquenums(b)==3);

   // Contains two unique numbers (0,10)
   const int c[5][5] = {
                   {10,  0, 10,  0, 10},
                   { 0, 10,  0, 10,  0},
                   {10,  0, 10,  0, 10},
                   { 0, 10,  0, 10,  0},
                   {10,  0, 10,  0, 10}
                  };
   assert(uniquenums(c)==2);

   // Contains 25 unique numbers
   const int d[5][5] = {
                   {-10, 9999999, 6, -34, 90},
                   {-547090, 123, 17, 1024, 8092},
                   {456, 789, -234, 678, -345,},
                   {-13, -14, -15, -17, -18},
                   {2, 4, 8, 16, 32}
                  };
   assert(uniquenums(d)==25);
     
   return 0;
}
