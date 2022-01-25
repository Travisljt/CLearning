#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define MAX 6

FILE* file_open(char* filename);
void  print_error(const char* str);
bool vaildboard(char* str);



int main()
{
   int r_row;
   int r_col;
   char r_arr[MAX][MAX];
   char buffer[25];
   char s;
   char str[6];
   char* filename = "5x4crn.rbd";
   FILE* fp = file_open(filename);
   fgets(str,5,fp);
   if(vaildboard(str))
   {
       int k = 0;
       r_row = str[0]-'0';
       r_col = str[2]-'0';
       printf("%d %d\n",r_row,r_col);
       while((s=fgetc(fp))!=EOF)
       {
         if(s!='\n')
         {
             buffer[k]=s;
             k++;
         }
       }
        printf("%s\n",buffer);
        printf("\n");
        for(int i = 0; i<r_row;i++){
         for(int j = 0; j<r_col;j++){
            r_arr[i][j]=buffer[i*r_col+j];
            fprintf(stdout,"%c",r_arr[i][j]);
         }
         printf("\n");
       }

   }
   else
   {
      print_error("Open an invaild roller board");
   }
 
    fclose(fp);

}

bool vaildboard(char* str)
{
  if((strlen(str)==4)&&(str[1]==' '))
  {
      int cnt = 0;
     for(int i =0; i<=(int)strlen(str);i++)
  {
      if(str[i]>=48 && str[i]<=57)
      {
        cnt++;
      }
  }
  if(cnt == 2)
  {
      return true;
  }
  }
  return false;
}

FILE* file_open(char* filename)
{
    FILE* file_pointer = fopen(filename, "r");
    if(file_pointer==NULL){
        print_error("Couldn't open file");
    }
    return file_pointer;
}

void  print_error(const char* str)
{
    fprintf(stderr,"%s\n",str);
    exit(EXIT_FAILURE);
}
