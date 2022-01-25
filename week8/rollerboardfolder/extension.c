#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define JUMP -1
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN  3
#define MAX 6
#define MAXIUM 100
#define STORE 500
#define LARGE 5000


/*This extension.c is quite same between the rollerboard file,
  I just add one more function at the bottom*/


char* temp_p;
struct roller
{
    char arr[MAX][MAX];
    int row;
    int col;
    int flag;
    int parent;
    int direction; //Add A dierction flag
};
typedef struct roller roller;

FILE* file_open(char* filename);
void  print_error(const char* str);
void* my_malloc(int size);
int move_num(char* s,roller* st);
void print_move(roller* st,int move);
void test(void);
bool vaildline(char* str);
void copytoarr(roller* r, FILE* fp);
roller* ini_roll();
bool vaildboard(int num1, int num2, char* str);
void consequence(roller* r,roller* conseq);
roller row_left_right(roller* r, int d, int row);
roller col_up_down(roller*r,int d, int col);
bool isSame(const roller* parent, const roller* child);
roller arrtoarr(roller* r);
void store(int element,roller* r,roller* s);
void print_move_more(roller* st, int move);

int main(int argc, char **argv)
{

  test();
  roller st[MAXIUM];
  int move;
  if(argc==2)
  {
      move=move_num(argv[1],st);
      fprintf(stdout,"%d moves\n",move);
  }
  
  if(argc==3 && (strcmp(argv[1],"more")==0))
  {
      move=move_num(argv[2],st);
      print_move_more(st,move);
  }
 
  if(argc==3 && (strcmp(argv[1],"-v")==0))
  {
      move=move_num(argv[2],st);
      print_move(st,move);
  }

  if(argc>3)
  {
      print_error("Error format: ./rollerboard <File> || ./rollerboard -v <File>");
  }
  
  
  return 0;
}

void test(void)
{
    roller* r = ini_roll();
    assert((file_open("3x3crn.rbd")));
    FILE* fp = file_open("3x3crn.rbd");
    assert(vaildline("5 4 "));
    assert(!vaildline("123455"));
    assert(vaildboard(3,3,"111000000"));
    assert(!vaildboard(3,4,"111000000"));
    assert(!vaildboard(3,3,"111100000"));
    copytoarr(&r[0],fp);
    roller h[MAX];
    char* ip1 = "000010011";
    char* ip2 = "001001010";
    for(int i=0;i<r->row;i++){
      for(int j=0;j<r->col;j++){
          h[0].arr[i][j]=ip1[i*r->col+j];
          h[1].arr[i][j]=ip2[i*r->col+j];
      }
    }
    r[1]=row_left_right(&r[0],LEFT,1);
    r[2]=col_up_down(&r[0],UP,2);
    h[2]=arrtoarr(&r[2]);
    assert(isSame(&r[1],&h[0]));
    assert(isSame(&r[2],&h[1]));
    assert(isSame(&r[2],&h[2]));
    free(r);
}

int move_num(char* s,roller* st)//BFS
{
    roller* r = ini_roll();
    FILE* fp = file_open(s);
    copytoarr(&r[0],fp);
    roller conseq;
    consequence(&r[0],&conseq);
    roller* h = (roller*)my_malloc(sizeof(roller*)*STORE);
   
    int cnt=0;
    int hflag[4]={true,true,true,true};
    int element=0;
    for(int x=0;x<=cnt;x++)
    {  
      if(r[x].flag==0)
      {  
       for(int i =0; i<r->row;i++)
         {
          for(int j =0; j<r->col;j++)
          {
             if(r[x].arr[i][j]=='1')
             {
                h[LEFT]=row_left_right(&r[x],LEFT,i);
                h[RIGHT]=row_left_right(&r[x],RIGHT,i);
                h[UP]=col_up_down(&r[x],UP,j);
                h[DOWN]=col_up_down(&r[x],DOWN,j);
                  
                
                for(int k=0;k<=cnt;k++){
                  if(isSame(&r[k],&h[LEFT])) {hflag[LEFT]=false;}
                 }
                  if(hflag[LEFT])
                 {
                    cnt++;
                    r[cnt]=arrtoarr(&h[LEFT]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                    r[cnt].direction=LEFT; //each time in "if", mark it.
                    if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;
                    }
                  }
                
                for(int k=0;k<=cnt;k++){
                   if(isSame(&r[k],&h[RIGHT])) {hflag[RIGHT]=false;}
                }
                  if(hflag[RIGHT])
                {
                    cnt++;
                    r[cnt]=arrtoarr(&h[RIGHT]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                    r[cnt].direction=RIGHT;//each time in "if", mark it.
                      if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;
                    }   
                }
                
                for(int k=0;k<=cnt;k++){
                   if(isSame(&r[k],&h[UP])) {hflag[UP]=false;}
                }
                  if(hflag[UP])
                {
                    cnt++;
                    r[cnt]=arrtoarr(&h[UP]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                    r[cnt].direction=UP;//each time in "if", mark it.
                      if(isSame(&r[cnt],&conseq))
                    { 
                        element=cnt;
                        x=cnt+1;
                    }            
                }
                
                for(int k=0;k<=cnt;k++){
                    if(isSame(&r[k],&h[DOWN])) {hflag[DOWN]=false;}
                }
                  if(hflag[DOWN])
                {
                    cnt++;
                    r[cnt]=arrtoarr(&h[DOWN]);
                    
                    r[cnt].col=r->col;
                    r[cnt].row=r->row;
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                    r[cnt].direction=DOWN;//each time in "if", mark it.
                      if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;
                    }       
                } 

                hflag[LEFT]=true;
                hflag[RIGHT]=true;
                hflag[UP]=true;
                hflag[DOWN]=true;
             }
          } 
       } 
        r[x].flag = 1;
     }
          if(cnt>=(LARGE-MAXIUM))
       {
         print_error("No solutions");
       }
    }

    int n = 0;
    int temp=1;
    while(temp!=JUMP)
    {
      st[n]=arrtoarr(&r[element]);
      st[n].flag=r[element].flag;
      st[n].direction=r[element].direction;
      st[n].parent=r[element].parent;
      element = r[element].parent;
      temp=st[n].parent;
      if(isSame(&st[n],&r[0]))
      {
        temp=JUMP;
      }
        n++;
    }             

    free(r);
    free(h);
   
   return n-1;
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

void* my_malloc(int size)
{
    void* space = malloc(size);
    if(space==NULL){
        print_error("Couldn't malloc() space");
    }
    return space;
}
void copytoarr(roller* r, FILE* fp)
{
   char buffer[MAXIUM]={0};
   char s;
   char str[MAX]={0};
   temp_p=fgets(str,MAX,fp);
   if(vaildline(str))
   {
       int k = 0;
       r->row = str[0]-'0';
       r->col = str[2]-'0';
       while((s=fgetc(fp))!=EOF)
       {
         if(s!='\n')
         {
             buffer[k]=s;
             k++;
         }
       }
        if(vaildboard(r->col,r->row,buffer))
        {
          for(int i = 0; i<r->row;i++){
           for(int j = 0; j<r->col;j++){
            r->arr[i][j]=buffer[i*r->col+j];
          }
         }
        }
        else
        {
           print_error("Open an invaild roller board");
        }
   }
    else
        {
      print_error("Open an invaild roller board");
        }

    fclose(fp);

}

bool vaildline(char* str)
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

roller* ini_roll()
{
    roller* r = (roller*)my_malloc(sizeof(roller*)*LARGE);
    r->col = 0;
    r->row = 0;
    r->flag = 0;
    r->parent = 0;
    r->direction = -1;
    return r;
}

bool vaildboard(int num1, int num2, char* str)
{
   int cnt = 0;
   int k = 0;
   for(int i=0;i<=(int)strlen(str);i++)
   {
       if(str[i]=='1')
       { 
          cnt++;
       }
       if(str[i]=='0')
       {
           k++;
       }

   }
   if((num1*num2)==(cnt+k))
   {
       if(num1==cnt)
       {
         return true;
       }
       
   }

    return false;
}

void consequence(roller* r,roller* conseq)
{
     
     for(int i = 0; i<r->row;i++)
    {
      for(int j =0;j<r->col;j++)
         {
             if(i==0)
             {
                conseq->arr[i][j]='1'; 
             }
             else{
                 conseq->arr[i][j]='0';
             }
         }
    } 
}

roller row_left_right(roller* r, int d, int row)
{
    roller new_r = arrtoarr(r);
    if(d==LEFT)
    {
        for(int i = 0;i<r->col;i++)
        {
            if(i==r->col-1)
            {new_r.arr[row][i]=r->arr[row][0];}
            else
            {new_r.arr[row][i]=r->arr[row][i+1];}
        }
    }
    
    if(d==RIGHT)
    {
        for(int i = 0;i<r->col;i++)
        {
            if(i==0)
            { new_r.arr[row][i]=r->arr[row][r->col-1];}
            else
            {new_r.arr[row][i]=r->arr[row][i-1];}
        }
    }
    return new_r;
}

roller col_up_down(roller*r,int d, int col)
{
    roller new_r = arrtoarr(r);
    if(d==UP)
    {
        for(int i = 0;i<r->row;i++)
        {
            if(i==r->row-1)
            {new_r.arr[i][col]=r->arr[0][col];}
            else
            {new_r.arr[i][col]=r->arr[i+1][col];}
        }
    }
    
     if(d==DOWN)
    {
        for(int i = 0;i<r->row;i++)
        {
            if(i==0)
            { new_r.arr[i][col]=r->arr[r->row-1][col];}
            else
            {new_r.arr[i][col]=r->arr[i-1][col];}
        }
    }
    return new_r;
}

bool isSame(const roller* parent, const roller* child)
{
     int k = 0;
       for(int i = 0; i<parent->row;i++){
           for(int j = 0; j<parent->col;j++){
               if(((parent->arr[i][j])-(child->arr[i][j]))!=0){
                   k++;
               }
          }
         }
    if(k>0)
    {
        return false;
    }
    return true;
}

roller arrtoarr(roller* r)
{
    roller new_r;
    new_r.col = r->col;
    new_r.row = r->row;
    for(int i = 0; i<r->row;i++){
        for(int j = 0; j<r->col;j++){
            new_r.arr[i][j]=r->arr[i][j];
          }
         }
    return new_r;
}


void print_move(roller* st,int move)
{
    int num=0;
    for(int x=move;x>=0;x--)
    {
         printf("%d:\n",num);
         for(int i =0; i<st->row;i++)
         {
          for(int j =0; j<st->col;j++)
          {    
              printf("%c",st[x].arr[i][j]);
          }
          printf("\n");
         }
         printf("\n");
         num++;
    }             
  
}

/* That is the only one new function*/
void print_move_more(roller* st, int move)
{
    int num=0;
    /*create a new roller board which is as same as st*/
    roller queue[MAXIUM];

    /*to mark the reach point*/
    int rowi[MAX];
    int colj[MAX];


    for(int k=move;k>=0;k--)
    {
     queue[move-k]=arrtoarr(&st[k]);
    }
    for(int k=0;k<move;k++)
    {
       
         for(int i =0; i<st->row;i++)
         {
          for(int j =0; j<st->col;j++)
          {    
            if(st[move-k].arr[i][j]-st[move-k-1].arr[i][j]!=0)
            {
                //Mark each different, it should be add one more '1'
                queue[k].arr[i][j]='1';
                
            }
          }
         }
    }    
               
    for(int k=0;k<move;k++)
    {
         for(int i =0; i<st->row;i++)
         {
          for(int j =0; j<st->col;j++)
          {    //Get the reach point
            if(st[move-k].arr[i][j]-queue[k].arr[i][j]!=0)
            {
                rowi[k]=i;
                colj[k]=j;
            }
          }
         }
     }  
       
    for(int x=move;x>=0;x--)
    {   
        if(st[x].direction==-1)
        {
           printf("%d: This is the \033[31m original \033[0mrollerboard\n",num);
        } 
        if(st[x].direction==LEFT)
        {  //\033[31m ....\033[0m '31' make the word become red, and '32' become green
           printf("%d: The '1' roll \033[31m left\033[0m and reach \033[32m (%d,%d)\033[0m\n",num,rowi[move-x-1],colj[move-x-1]);
        }
        
        if(st[x].direction==RIGHT)
        {
           printf("%d: The '1' roll \033[31m right\033[0m and reach \033[32m (%d,%d)\033[0m\n",num,rowi[move-x-1],colj[move-x-1]);
        }
        
        if(st[x].direction==UP)
        {
           printf("%d: The '1' roll \033[31m up\033[0m and reach \033[32m (%d,%d)\033[0m\n",num,rowi[move-x-1],colj[move-x-1]);
        }
       
        if(st[x].direction==DOWN)
        {
           printf("%d: The '1' roll \033[31m down\033[0m and reach \033[32m (%d,%d)\033[0m\n",num,rowi[move-x-1],colj[move-x-1]);
        }
         for(int i =0; i<st->row;i++)
         {
          for(int j =0; j<st->col;j++)
          {    
              printf("%c",st[x].arr[i][j]);
          }
          printf("\n");
         }
         printf("\n");
         num++;
    }             
   
}
