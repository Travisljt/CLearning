#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100

 struct crossword{
   char arr[GRID][GRID];
   int sz;
};
typedef struct crossword crossword; 
void getcluestring(const crossword* c);
void print_crossword(const crossword* c)
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
  crossword c;
  int *ip;
  ip[26] = "....X.XX.X.X......X.XX...";
     c.sz = 5;
   
   //memset(cw.arr,0,sizeof(cw.arr));
   for(int i=0;i<5;i++){
      for(int j=0;j<5;j++){
          c.arr[i][j]= ip[i*5+j];
      }
   }
  print_crossword(&c);
  getcluestring(&c);
}

void getcluestring(const crossword* cw)
{
 //int a[BIGSTR]={0},d[BIGSTR]={0};
   int cnt = 0;
	for(int i=0;i < cw->sz; i++){
		for(int j=0;j < cw->sz; j++){
            
				  if (((cw->arr[i][j]=='.')&&(cw->arr[i-1][j]) =='X')&&((cw->arr[i+1][j]) =='.'))  {	//当前格上方为黑格
					    cnt++;
                   //a[i]=cnt;
                   printf("%d-i\n",cnt);
                 }
				  
				  if((cw->arr[i][j]=='.')&&((cw->arr[i][j-1]) =='X')&&((cw->arr[i][j+1]) =='.')){	//当前格左侧为黑格
					    cnt++;
                  // d[j]=cnt;
                   printf("%d-j\n",cnt);
				    }
          
				//其余情况不需要计数
			
		}
	} 
}