#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

int numdiff(const int l[], const int n);

int main(void)
{
   int l[] = {100484783, 2, 30, -999999999, 3, 222222, -89492981, 1, 456889009};
   int m[] = {-567, 4, 99999, 0, 4, 4};
   assert(numdiff(l, 9)==9);
   assert(numdiff(m, 6)==4);
   assert(numdiff(m, 5)==4);
   assert(numdiff(m, 3)==3);
   assert(numdiff(NULL, 0)==0);
   return 0;
}

int numdiff(const int l[], const int n)
{
    int cnt=0;
    int tem[10];
    if(l==NULL)
    {
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
         if(l[i]==l[j])
            {
                tem[i]=1;
            }
        }    
    }
    for(int i=0;i<n;i++)
    {
        if(tem[i]==1)
        {
            cnt++;
            tem[i]=0;
        }
 
    }

    return (n-cnt);
}