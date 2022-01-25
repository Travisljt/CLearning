#include<stdio.h>

int main()
{
    int hour1,hour2,min1,min2;
    int sum_hour_min1,sum_hour_min2,diff_hour_min;
    printf("Enter two times(the second time is the next day time): ");
    /*Initial that the second time is next day time*/
    scanf("%d:%d %d:%d",&hour1,&min1,&hour2,&min2);
    sum_hour_min1 = hour1*60+ min1;
    sum_hour_min2 = (24+hour2)*60+ min2;
    diff_hour_min = sum_hour_min2 - sum_hour_min1;
    /*printf("Difference is ");
    if((diff_hour_min/60)<10)
    {
       printf("0%d:",diff_hour_min/60);
    }
    else
    {
      printf("%d:",diff_hour_min/60);
    }
    if((diff_hour_min%60)<10)
    {
       printf("0%d\n",diff_hour_min%60);
    }
    else
    {
        printf("%d\n",diff_hour_min%60);
    }
    The code above isn't the single output, it has less speed*/

     printf("Difference is %02d:%02d\n",diff_hour_min/60,diff_hour_min%60);
     /* %02d means you need to add a '0' to satisfied 2 bits */
}

