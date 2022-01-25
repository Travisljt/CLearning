#include<stdio.h>
#include<assert.h>
//Make a love heart graph through character '*'

int main()
{
    char x,y,z;
    printf("For my dear (Insert first captial character): ");
    scanf("%c%c%c",&x,&y,&z);
    /*
    assert(x == 'T');
    assert(y == 'K');
    assert(z == 'F');
    */
    if(x == 'T' && y == 'K' && z == 'F')
    {
        printf("Give her your love\n");
        int  i, j, k, l, m;

        char c='*'; 

     /* for (i=1; i<=2; i++)  
      {  
          printf("\n"); //Leave two lines blank at the beginning
      } 
      */

      for (i=1; i<=3; i++) //Leave the first three row blank, divide to four part
      { 

        for (j=1; j<=32-2*i; j++)  printf(" "); //Each next line has 2 fewer left Spaces than the previous line

        for (k=1; k<=4*i+1; k++)  printf("%c", c);//Output the left half of the character

        for (l=1; l<=13-4*i; l++)  printf(" "); //Each middle line has 4 fewer Spaces than the previous line

        for (m=1; m<=4*i+1; m++)  printf("%c", c);//Output the right half of the character

         printf("\n");  //Newline at the end of each line
      }

      for (i=1; i<=3; i++)//There are no Spaces in the middle of the next three lines
       { 

        for (j=1; j<=24+1; j++)   printf(" "); //Space on the left //8*(n-1)+1

        for (k=1; k<=29; k++)   printf("%c", c);//Output the character

         printf("\n");  //Newline at the end of each line

        }

      for (i=7; i>=1; i--)//The next seven lines
       { 

        for (j=1; j<=40-2*i; j++)  printf(" "); //Each next line has 2 fewer Spaces to the left than the previous line//8*(n+1)-2*i

        for (k=1; k<=4*i-1; k++)  printf("%c", c);//Each line has 4 fewer characters than the previous line (this loop is i--)  

        printf("\n");  //Everyline output then break

       }

        for (i=1; i<=39; i++)    printf(" "); //Leave 39 blank of the last line

        printf("%c\n", c);  //The last one '*'

        /*for (i=1; i<=2; i++)    printf("\n");  */ //Leave two line at the end
    }
    else
    {
        printf("You are such a bitch? Even though could not remember your lover name isn't it?? \n");
    }
    
    return 0;
    
}