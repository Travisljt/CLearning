#include "crossword.h"


bool Downclue(const crossword* cw,int row,int column);
bool Acrossclue(const crossword* cw,int row, int column);
char Changestr(crossword* cw, int row, int column);
int floatToint(float f);
// Might be useful to be able to print them
// to hep with debugging
void print_crossword(const crossword* c)
{
   for(int y=0; y<c->sz; y++){
      for(int x=0; x<c->sz; x++){
         printf("%c", c->arr[y][x]);
      }
      printf("\n");
   }
}

bool str2crossword(int sz, char* ip, crossword* cw)
{
   if((ip == NULL) || (cw == NULL) || (sz<=0)||((int)(strlen(ip))!=(sz*sz))){
      return false;
   }

   /*Pass the string of the ip array into 2D array and change str if need*/
   cw->sz = sz;
   for(int i=0;i<sz;i++){
      for(int j=0;j<sz;j++){
         cw->arr[i][j]= ip[i*sz+j];
         cw->arr[i][j]=Changestr(cw,i,j);
      }
   }

   return true;
}


int getchecked(crossword c)
{
   int num = 0;
   int all = 0;
   int Percentage;

for(int i=0;i < c.sz; i++){
 for(int j=0;j < c.sz; j++){
   if((c.arr[i][j] =='.')){
      all++;//Calculate the all blank squares
      
      if(i==0){ //First row
        if((c.arr[i+1][j]=='.')&&(c.arr[i][j+1]=='.')){ //Focus on right & down
          num++;
          }
       else if((c.arr[i+1][j]=='.')&&(c.arr[i][j-1]=='.')){ //Focus on left & down
          num++;
          }
       }

      else if(j==0){ //First column
       if(((c.arr[i-1][j]=='.')||(c.arr[i+1][j]=='.'))&&(c.arr[i][j+1]=='.')){ //Focus on up & down & right
          num++;
          }
       }

      else if(((c.arr[i-1][j]=='.')||(c.arr[i+1][j]=='.'))&&((c.arr[i][j-1]=='.')||(c.arr[i][j+1]=='.'))){ //Focus on up & down & left & right
          num++;
          }
      }  
    }
  }
    
  float f = ((float)num/(float)all)*100;
  Percentage = floatToint(f);
  // printf("NUM=%d, ALL=%d,,,",num,all);
  ///printf("percentage=%d\n",Percentage);
    
  return Percentage;
}

void getcluestring(const crossword* c, char* str)
{
  int cnt = 0;

  /*Use calloc to achieve dynamic memory allocation*/
  char *Across = (char*)calloc((c->sz),(c->sz)*(c->sz)*sizeof(char));
  char *Down = (char*)calloc((c->sz),(c->sz)*(c->sz)*sizeof(char));
  char *Tem = (char*)calloc((c->sz),(c->sz)*(c->sz)*sizeof(char));
  char *buffer = (char*)calloc((c->sz),(c->sz)*(c->sz)*sizeof(char));
  //2Darray的扣分项，需要在calloc之后对这些类型的指针进行一个判断，if语句，例如： if(Across!=NULL)则进行下一步
  //可以学老师的，额外写一个函数 ncalloc，用于判断是否为空指针，且对初值进行干预 详细见chapter P  
  /*Initialize the first character*/
  Across[0] = 'A';
  Down[0] = 'D';
  Tem[0]='|';
 
  for(int i=0;i < c->sz; i++){
		for(int j=0;j < c->sz; j++){
         if(Downclue(c,i,j)||Acrossclue(c,i,j)){//Determine the position that belongs to the Down | Across clue 
          cnt++;
          if(cnt>=10){
             sprintf(buffer,"-%2d",cnt);//Prevent buffer overflow
          }
          else{ 
             sprintf(buffer,"-%d",cnt);
         }

         /*Add the serial number after Across or Down*/
          if(Downclue(c,i,j)){
            strcat(Down,buffer);
            
          }
          if(Acrossclue(c,i,j)){
             strcat(Across,buffer);
             
          }
       } 
      }
  } 
  //Connect each string into "str"
  strcpy(str,Across);
  strcat(Tem,Down);
  strcat(str,Tem);

  
  free(Across);
  free(Down);
  free(Tem);
  free(buffer);
  
  //for(int i=0;i<100;i++){
  //  printf("%c",str[i]);
  //}printf("\n");
}

void test(void)
{
   crossword c;
   assert(str2crossword(5," . .X **.X.X. ... * XX.. ",&c));//Check Changstr fuction is correct or not
  
   assert(Acrossclue(&c,2,2));
   assert(Acrossclue(&c,4,2));//Check arcoss fuction is working or not 
   assert(!Downclue(&c,4,2));
   assert(Downclue(&c,2,2));//Check Down fuction is working or not
   
   assert(floatToint(52.92)==53);
   assert(floatToint(51.12)==51);
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

bool Downclue(const crossword* cw, int row, int column)
{
			if(cw->arr[row][column]=='.'){
            if (((cw->arr[row-1][column]) =='X')&&((cw->arr[row+1][column]) =='.'))  {	//Above the current square is black
					    return true;
              }
             if((row-1<0)&&((cw->arr[row+1][column]) =='.')){//Above the current square is off the grid
                 return true;
             }
         }
    
  return false;
}

bool Acrossclue(const crossword* cw,int row, int column)
{
		 if(cw->arr[row][column]=='.'){
				  if(((cw->arr[row][column-1]) =='X')&&((cw->arr[row][column+1]) =='.')){	//To the left of the current square is black
                  return true;
				    }
              if((column-1<0)&&((cw->arr[row][column+1]) =='.')){//To the left of the current square is off the grid
                  return true;
             }
         }
     
   return false;
}
/*Rounding off method */
int floatToint(float f)
{
   int i = 0;
   i = (f*10+5)/10;

   return i;
}
