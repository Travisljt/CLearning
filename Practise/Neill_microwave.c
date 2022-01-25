#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>

#define MIN10 600
#define MIN1 60
#define SEC10 10


int PressBotton(int a);


/*   struct Botton
{
    int min_10;
    int min_1;
    int sec_10;
};  */

// typedef struct Botton Botton;

int main(void)
{
  int need_time;
  printf("Type the time require:\n");
  scanf("%d",&need_time);
  assert(PressBotton(705)==7);
  printf("Number of Botton press: %d\n",PressBotton(need_time));
  return 0;
}

int PressBotton(int a)
{  
  // Use normal method
  /* int cnt = 0;
   while(a>SEC10)  
  {
      while(a>MIN1 )
   {
       while(a>MIN10)
      
      {
        cnt += (a/MIN10);
         a = a%MIN10;
      }
      cnt += (a/MIN1);
      a = a%MIN1;
   }
    cnt += (a/SEC10);
    a = a%SEC10;
  }
  
  if(a<=SEC10)
  {
    cnt++;
  }

  return cnt;
*/

//  Use array methods
  const int min_10 = 0;//Sets the first location of the array
  const int min_1 = 1;//Sets the second location of the array
  const int sec_10 = 2;//Sets the third location of the array
  
  int ARRAYBOTTON[7] = {MIN10,MIN1,SEC10};//set 0 after third location   {600,60,10,0,0,0,0,}
   
   while(a>ARRAYBOTTON[sec_10])  
  {
      while(a>ARRAYBOTTON[min_1])
   {
       while(a>ARRAYBOTTON[min_10])
      
      {
         ARRAYBOTTON[3]+= (a/MIN10);
         a = a%MIN10;
      }
      ARRAYBOTTON[4] += (a/MIN1);
      a = a%MIN1;
   }
    ARRAYBOTTON[5]+= (a/SEC10);
    a = a%SEC10;
  }
  
  if(a<=SEC10)
  {
    ARRAYBOTTON[6]++;
  }

 return ARRAYBOTTON[3]+ARRAYBOTTON[4]+ARRAYBOTTON[5]+ARRAYBOTTON[6];
// Add total time then return

}
