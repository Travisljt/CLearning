#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define MAX 3


/*struct grid
{
    int arr[MAX][MAX];
    int sz;
};
typedef struct grid grid;
*/
int cnt = 0;
void recurs_grid(int arr[MAX][MAX],int x, int y, int z);
void print_grid(int arr[MAX][MAX], int sz)
{
   for(int y=0; y<sz; y++){
      for(int x=0; x<sz; x++){
         printf("%2d ", arr[y][x]);
      }
      printf("\n");
   }
}
int main(void)
{
   int arr[MAX][MAX];
   for(int i=0;i<MAX;i++){
      for(int j=0;j<MAX;j++){
         arr[i][j]= 0;
      }
   }
    //print_grid(arr,MAX);
    recurs_grid(arr,0,0,1);
    printf("There is %d possibilities\n",cnt);
}

void recurs_grid(int arr[MAX][MAX],int x, int y, int z)
{
    if(x<0||y<0||x>=MAX||y>=MAX){
        return;
    }
    if(arr[x][y]>0){
        return;
    }
    
    arr[x][y] = z;

    if(z==(MAX*MAX)){
        print_grid(arr,MAX);
        printf("\n");
        cnt++;
        arr[x][y] = 0;
        return;
    }
    
     
    recurs_grid(arr,x+1,y,z+1);
    recurs_grid(arr,x-1,y,z+1);
    recurs_grid(arr,x,y+1,z+1);
    recurs_grid(arr,x,y-1,z+1);

    arr[x][y]=0;
}


  

