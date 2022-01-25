#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*
   For a square 5x5 2D integer array, find the
   longest run of identical numbers in any column.
*/
int arrrun(const int a[5][5]);

int main(void)
{

   // No identical numbers in column
   const int a[5][5] = { { 1, 2, 3, 4, 5},
                   { 6, 7, 8, 9,10},
                   {11,12,13,14,15},
                   {16,17,18,19,20},
                   {21,22,23,24,25} };
   assert(arrrun(a)==1);

   // 2 ones in first column
   const int b[5][5] = { { 1, 2, 3, 4, 5},
                   { 1, 7, 8, 9,10},
                   {11,12,13,14,15},
                   { 1,17,18,19,20},
                   { 1,22,23,24,25} };
   assert(arrrun(b)==2);
 
   // 3 eights in middle column
   const int c[5][5] = { { 1, 2, 3, 4, 5},
                   { 6, 7, 8, 9,10},
                   {11,12, 8,14,15},
                   {16,17, 8,19,20},
                   {21,22,23,24,25} };
   assert(arrrun(c)==3);
 
   // 4 tens in final column
   const int d[5][5] = { { 1, 2, 3, 4, 5},
                   { 6, 7, 8, 9,10},
                   {11,12,13,14,10},
                   {16,17,18,19,10},
                   {21,22,23,24,10} };
   assert(arrrun(d)==4);

   return 0;
}


int arrrun(const int a[5][5])
{
    int cnt=0;
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++){

         if(a[i][j]==a[i][j+1])
         {
             cnt++;
         }
         if(a[i+1][j]==a[i][j])
         {
             cnt++;
         }
      }
    }
    if(cnt==0)
    {
        cnt++;
    }
    printf("cnt=%d\n",cnt);
    return cnt;
}
