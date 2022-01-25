#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>

#define NUMBER pow(10,7) /* Set all NUMBER equal to 10,000,000*/ 

int Hailstone(long int t); /* The function is to calculate the each number's Hailstone sequence */
int Hailstone_max(long int t);/* The function is to find the each number's largest number of Hailstone seq*/ 

int main()
{
  /* Use dynamic arrays to ensure that the array has sufficient capacity */
  int* a = (int*)malloc(NUMBER*sizeof(int));
 // int* b = (int*)malloc(NUMBER*sizeof(int));
  
  int longest = 0;
  int ini_max = 0;
 /* Sets the initial value to find the longest sequence above*/
  //int largest = 0;
  //int num_max = 0;
 /* Sets the initial value to find the largest number in sequence above */
  assert(Hailstone(11)==15);
  assert(Hailstone_max(11)==52);
  /* Test */
  
  for(int i=0;i<NUMBER;i++)
  {
      a[i] = Hailstone(i); /* Put each number of sequence into the array, from 1 to 10^7 */
      if(a[i]>longest)/* Select the longest one */
      {
           longest = a[i];
           ini_max = i;
      }
     /* b[i] = Hailstone_max(i); 
      if(b[i]>largest)
      {
          largest = b[i];
          num_max = i;
      }*/
  }
  
  printf("The Initial number is %d, and create the longest sequence is %d\n",ini_max,longest);
  /*exercise 2.2 above*/
  //printf("The Initial number is %d, and create the largest number is %d\n",num_max,largest);
  /*exercise 2.3 above*/
  free(a);
  //free(b);
  /*free the dynamic array for a and b, in order to protect the machine */ 
  return 0;

}
 
 int Hailstone(long int t) /* 'long int' make the number range larger than 'int' */
{
  int length = 1; /* The initial value should also be accounted for */
  while(t>1)
  {
    (t%2)?(t=3*t+1):(t=t/2);/* Same as if function, find the seq */
    length++;
  }
  return length;
}


int Hailstone_max(long int t)
{
  long int max = 1; /* The initial value should also be accounted for */
  while(t>1)
  {
      if(t%2==0)
      {
          t = t/2;
      }
      else
      {
          t = 3*t + 1;
      }
      if(t>max)
      {
          max = t;
      }
  }
  return max;
}
