#include<stdio.h>
#define A 7
#define C 5
#define M 11

int main(void)
{
    int seed=0;
    int LOOPS=20;//initial number,as you set by yourself
    int cnt=0;
    for(int i=0;i<LOOPS;i++)
    {
        seed = (A*seed+C)%M;
        printf("%d\n",seed);
        if(seed == C)//The first number of period must be the C
        {
        cnt++;
        }
    }

    printf("Period is %d\n",LOOPS/cnt);
    /*The total number of loops divided by the number of occurrences of C is the period*/
    return 0;

}