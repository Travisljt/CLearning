#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100
#define NUMBER 50

struct crossword{
   char arr[GRID][GRID];
   int sz;
};
typedef struct crossword crossword;

bool Downclue(const crossword* cw,int row,int column);
bool Acrossclue(const crossword* cw,int row, int column);
char changestr(crossword* cw, int row, int column);
int floatToint(float f);
//int Label(const crossword* cw,int row, int column);

void test(void);
bool str2crossword(int sz, char* ip, crossword* cw);
void getcluestring(const crossword* c, char* str);
int getchecked(crossword c);
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
   //test();
   char str[BIGSTR];
   crossword c;
   
   // Invalid (string NULL)
   assert(!str2crossword(1, NULL, &c));
   // Invalid (crossword* NULL)
   assert(!str2crossword(2, "", NULL));
   // Invalid (size incorrect)
   assert(!str2crossword(-7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   // Invalid (string too short)
   assert(!str2crossword(7, "", &c));
   // Invalid (string too long)
   assert(!str2crossword(5, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   // Invalid (size too large)
   assert(!str2crossword(500, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));

   // Valid Crosswords 
   assert(str2crossword(3, ".........", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-5|D-1-2-3", str)==0);
   // All squares are shared (checked)
   assert(getchecked(c)==100);

   // Example from handout
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str)==0);
   assert(getchecked(c)==53);

   assert(str2crossword(5, "X...X...............X...X", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str)==0);
   assert(getchecked(c)==100);

   // Can be ' ' and '*', not just '.' and 'X'
   assert(str2crossword(5, "*   *               *   *", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str)==0);
   assert(getchecked(c)==100);

   assert(str2crossword(7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-6-8|D-2-4-5-6-7", str)==0);
   assert(getchecked(c)==32);

   assert(str2crossword(7, "X.X........X.XX.X.X.X.......X.X.X.X....X.XX.X....", &c));
   getcluestring(&c, str);
   assert(strcmp("A-2-4-5-6-7|D-1-2-3", str)==0);
   assert(getchecked(c)==33);

   assert(str2crossword(7, "...X....X...X....X...X.XXX.X...X....X...X....X...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6-8-10-12-14-15-16|D-1-2-3-4-7-9-10-11-12-13", str)==0);
   assert(getchecked(c)==67);

   assert(str2crossword(7, "........X.XXX..X......X.X.X......X..XXX.X........", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7|D-1-2-3-5", str)==0);
   assert(getchecked(c)==33);

   assert(str2crossword(8, ".....X.XX.X.X..........XX.X.X......X.X.XX..........X.X.XX.X.....", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-5-6-7-8-11-12-13|D-2-3-4-5-9-10", str)==0);
   assert(getchecked(c)==43);

   
}
char Changestr(crossword* cw, int row, int column)
{
   if(cw->arr[row][column]=='*'){
      return 'X';
   }
   
   if(cw->arr[row][column]==' '){
      return '.';
   }

   return cw->arr[row][column];
}
/*bool Downclue(const crossword* cw, int row, int column)
{
 if((cw->arr[row][column]=='.')||(cw->arr[row][column]==' ')){
  if ((((cw->arr[row-1][column]) =='X')||(row-1<0))&&((cw->arr[row+1][column]) =='.'))  { //当前格上方为黑格
     return true;
  }
 }
 return false;
}

bool Acrossclue(const crossword* cw,int row, int column)
{
    if((cw->arr[row][column]==' ')||(cw->arr[row][column]=='.')){//当前格为白格
  if((((cw->arr[row][column-1]) =='*')||(column-1<0))&&((cw->arr[row][column+1]) ==' ')){ //当前格左侧为黑格
            return true;
  }
    }
 return false;
}
*/
bool str2crossword(int sz, char* ip, crossword* cw)
{

	if((ip == NULL) || (*ip=='\0')||(cw == NULL) || (sz<=0)||((strlen(ip))!=(sz*sz))){
      return false;
   }
   cw->sz = sz;
   for(int i=0;i<sz;i++){
      for(int j=0;j<sz;j++){
         cw->arr[i][j]= ip[i*sz+j];
      }
   }
   for(int i=0;i<cw->sz;i++){
      for(int j=0;j<cw->sz;j++){
       cw->arr[i][j]=Changestr(cw,i,j);
      }
   }
   return true;
}

bool Downclue(const crossword* cw, int row, int column)
{
			if(cw->arr[row][column]=='.'){
            if (((cw->arr[row-1][column]) =='X')&&((cw->arr[row+1][column]) =='.'))  {	//当前格上方为黑格
					    return true;
              }
             if((row-1<0)&&((cw->arr[row+1][column]) =='.')){
                 return true;
             }
         }
    
  return false;
}
bool Acrossclue(const crossword* cw,int row, int column)
{
		 if(cw->arr[row][column]=='.'){//当前格为白格
				  if(((cw->arr[row][column-1]) =='X')&&((cw->arr[row][column+1]) =='.')){	//当前格左侧为黑格
                  return true;
				    }
              if((column-1<0)&&((cw->arr[row][column+1]) =='.')){
                  return true;
             }
         }
     
   return false;
}

// Convert crossword to string of across & down numbers
void getcluestring(const crossword* cw, char* str)
{
  int cnt = 0;
  char Across[NUMBER]="A";
  char Down[NUMBER]="D";
  char buffer[NUMBER];
  char tem[NUMBER]="|";
  for(int i=0;i < cw->sz; i++){
		for(int j=0;j < cw->sz; j++){
         if(Downclue(cw,i,j)||Acrossclue(cw,i,j)){    
          cnt++;
          sprintf(buffer,"-%d",cnt);
          if(Downclue(cw,i,j)){
            strcat(Down,buffer);
          }
          if(Acrossclue(cw,i,j)){
             strcat(Across,buffer);
          }
       } 
      }
  } 
  strcat(tem,Down);
  strcat(Across,tem);
  strcpy(str,Across);
  
  for(int i=0;i<NUMBER;i++){
     printf("%c",str[i]);
  }printf("\n");
    
}
			

// 获取两条线索之间共享的空方块的百分比

int getchecked(crossword c)
{
    int num = 0;
    int all = 0;
    for(int i=0;i < c.sz; i++){
		for(int j=0;j < c.sz; j++){
   if((c.arr[i][j] =='.')){
        if(i==0){ //第一行
        if((c.arr[i+1][j]=='.')&&(c.arr[i][j+1]=='.')){ //只看下&右
          num++;
          }
       else if((c.arr[i+1][j]=='.')&&(c.arr[i][j-1]=='.')){ //只看下&右
          num++;
          }
         }
       else if(j==0){ //第一列
     if(((c.arr[i-1][j]=='.')||(c.arr[i+1][j]=='.'))&&(c.arr[i][j+1]=='.')){ //只看上&下&右
              num++;
             }
       }
       else if(((c.arr[i-1][j]=='.')||(c.arr[i+1][j]=='.'))&&((c.arr[i][j-1]=='.')||(c.arr[i][j+1]=='.'))){ //上&下&左&右
        num++;
           }
       }  
      }
    }
    for(int i=0;i < c.sz; i++){
		for(int j=0;j < c.sz; j++){
         if(c.arr[i][j]=='.'){
            all++;
         }
      }
    }
    int Percentage;
    float f = ((float)num/(float)all)*100;
    Percentage = floatToint(f);
    printf("NUM=%d, ALL=%d,,,",num,all);
    printf("percentage=%d\n",Percentage);
    return Percentage;
}

int floatToint(float f)
{
   int i = 0;
   if(f>0){
    i = (f*10+5)/10;
   }
   else if(f<0){
     i =(f*10-5)/10;
   }
   else i = 0 ;

   return i;

}
