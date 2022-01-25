#include<stdio.h>
#include<math.h>
// If use the math library, it is better to use "-lm" when in config

int main()
{
    printf("test number is 3 to third power: %f\n",pow(3,3));
    printf("test number is the square root of 25: %f\n", sqrt(25));
    printf("45 divide to 10 is equal to %d\n",45/10);
    printf("28955161 %% 7910 is equal to %d\n",28955161%7910);// Test remainder
    //When use math function, it should remember that the type is "double"
}