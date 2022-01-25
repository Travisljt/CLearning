#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

int closestmean(const int l[], const int n);

int main(void)
{
   int l[] = {10, 20, 30, 40};
    int m[] = {-5, 0, 10, -10, 5};
   int r[] = {100, 200, 0, -500};
   int t[] = {-5, 5};
   /*int x1 = closestmean(l, 4);
   printf("x=%d\n",x1);
   printf("\n");
   int x2 = closestmean(m, 5);
   printf("x=%d\n",x2);
   printf("\n");
   int x3 = closestmean(l, 1);
   printf("x=%d\n",x3);
   printf("\n");
   int x4 = closestmean(r, 4);
   printf("x=%d\n",x4);
   printf("\n");
   int x5 = closestmean(t, 2);
   printf("x=%d\n",x5);
   printf("\n");
   int x6 = closestmean(&l[1], 3);
   printf("x=%d\n",x6);
   printf("\n");*/
   assert(closestmean(l, 4)==20);
   assert(closestmean(m, 5)==0);
   assert(closestmean(l, 1)==10);
   assert(closestmean(r, 4)==0);
   assert(closestmean(t, 2)==-5);
   assert(closestmean(&l[1], 3)==30);
   return 0;
}

int closestmean(const int l[], const int n)
{
    int all=0;
    int avg=0;
    int tem[10];
    
    int element=0;
    for(int i=0;i<n;i++)
    {
        all+=l[i];
    }
    avg = all/n;
    int small = abs(l[0]);
    for(int j=0;j<n;j++)
    {
           tem[j]=abs(l[j]-avg);

        //printf("i=%d,tem[i]=%d\n",j,tem[j]);
        if(small>tem[j]||tem[j]==0)
        {
            small=tem[j];
            element=j;
        }
      
    }
    
    //printf("all=%d,avg=%d,element=%d,l[element]=%d\n",all,avg,element,l[element]);
    return l[element];
}