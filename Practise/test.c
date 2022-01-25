#include<stdio.h>
#define PI 3.1415926


int TIMES(int a, int b);
int POINTER(int *s, int *t);

int main(void)
{
    int i,j,k;
    
    int *x = &i;
    int *y = &j;

    int z = 5, t = 9;

    printf("Please insert the first number: ");
    scanf("%d",&i);
    printf("Please insert the second number: ");
    scanf("%d",&j);
    k = TIMES(i,j);
    printf("%d times %d is %d\n",i,j,k);

    POINTER(x,y);
    printf("i is %d, and j is %d\n",i,j);
    printf("x is %d, and y is %d\n",*x,*y);
    printf("z is %d, and t is %d\n",z,t);
    POINTER(&z,&t);
    printf("z is %d, and t is %d\n",z,t);
    //printf("Test PI is %lf\n",PI);
    return 0;
}

int TIMES(int a, int b)
{
  int c,d=0;
  for(c=0;c<b;c++)
  {
      d += a;
  }
  return d;
 
}

int POINTER(int *s, int *t)
{
  *s = 1;
  *t = 2;
}