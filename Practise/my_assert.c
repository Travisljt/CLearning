#include<stdio.h>
#include<assert.h>

int TIMES(int a, int b);
void TEST(void);

int main()
{
   int i,j;
   printf("Insert two number: \n");
   scanf("%d %d",&i,&j);
   TEST();
   printf("%d times %d is %d\n",i,j,TIMES(i,j));
}

int TIMES(int a, int b)
{
  int c,d=0;
 /* if (a!=0||b!=0)
  {
      for(c=0;c<b;c++)
    {
      d += a;
    }
  }
  else
  {

  }
  */
  for(c=0;c<b;c++)
    {
      d += a;
    }
  return d;
 
}

void TEST(void)
{
    assert(TIMES(3,5)==15);
    assert(TIMES(5,3)==15);
    assert(TIMES(7,8)==56);
    assert(TIMES(8,7)==56);
    assert(TIMES(0,5)==0);
    assert(TIMES(5,0)==0);
}