#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUMBER 100

struct maze
{
    int sz;
    char arr[NUMBER][NUMBER];
};

typedef struct maze maze;


bool strto2d(int sz, char* str, maze* c);
bool escape(maze* c);
bool goingup();
bool goingdown();
bool goingleft();
bool goingright();


void print_maze(const maze* c)
{
   for(int y=0; y<c->sz; y++){
      for(int x=0; x<c->sz; x++){
         printf("%c", c->arr[y][x]);
      }
      printf("\n");
   }
}

int main(void)
{
  maze c;
  strto2d(5,"X.XXXX...XXXX.XX...XX.XXX",&c);
  print_maze(&c);
  
  
}

bool escape(maze* c)
{
  
  return false;
}

bool strto2d(int sz, char* str, maze* c)
{
  if((str == NULL) || (c == NULL) || (sz<=0)||((int)(strlen(str))!=(sz*sz))){
      return false;
   }
  c->sz = sz;

  for(int i=0;i<sz;i++){
      for(int j=0;j<sz;j++){
         c->arr[i][j]= str[i*sz+j];
      }
   }

   return true;

}