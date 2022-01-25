#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

int fvr(double t, int s);
typedef enum Condition {safe, warning} Condition;

int main(void)
{
    double Tem;
    char change;
    bool Scale ;
    printf("Do you want to use Fahrenheit to present? [y/n]:\n");
    scanf("%c",&change); 
    printf("You must know normal people's body temperture are between 35 to 40 in Celsius\n\n");
    printf("And also normal people's body temperture are between 95 to 104 in Fahrenheit\n\n");
    if(change == 'y')
    {
        Scale = true;
        printf("Your temperture is (Use Fahrenheit present):\n");
        scanf("%lf",&Tem);
    }
    if(change == 'n')
    {
        Scale = false;
        printf("Your temperture is (Use Celsius present):\n");
        scanf("%lf",&Tem);
    }
    
    assert(fvr(37.5,0)==1);
    assert(fvr(36.5,0)==0);
    assert(fvr(96.5,1)==0);
    assert(fvr(99.5,1)==1);
    if(fvr(Tem,Scale))
    {
      printf("You have fever right now\n");
    }
    else
    {
        printf("You are healthy\n");
    }
    return 0;
}

int fvr(double t, int s)
{
  Condition a;
  bool Scale = s;
  if(Scale)
  {
    t = (t-32)/1.8;  //Fahrenheit transfer to Celsius
  }
  if(t>=37.5)
  {
     a = warning;
  }
  else
  {
     a = safe;
  }
  return a;
}