#include "rollerboard.h"

FILE* file_open(char* filename)
{
    FILE* file_pointer = fopen(filename, "r");
    
    //Check if the file can open or not
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
    void* space = calloc(size,1);//最好使用 *calloc，可以直接帮忙初始化，不然就会报错uninitialize value
    
    //Check if the space can be malloc or not
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

   //Get the first line of the fp
   temp_p = fgets(str,MAX,fp);
   if(vaildline(str))
   {
       int k = 0;

       //Assign values to height and width
       r->row = str[0]-'0';
       r->col = str[2]-'0';

       //Get the rollerboard from the second line of the file
       while((s=fgetc(fp))!=EOF)
       {
         if(s!='\n')
         {
             buffer[k]=s;
             k++;
         }
       }

       //Determine whether the '1' is consistent with the width of the chessboard
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
  //Check the format is "%d %d" or not
  if((strlen(str)==4)&&(str[1]==' '))
  {
      int cnt = 0;
     for(int i =0; i<=(int)strlen(str);i++)
  {
      //Ascii code from 48 to 57 is '0~9'
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

roller* ini_roll(int num)
{
    //Use the structure r as an array and apply for a large space
    roller* r = (roller*)my_malloc(sizeof(roller*)*num);
    r->col = 0;
    r->row = 0;
    r->flag = 0;
    r->parent = 0;
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
   /*Check whether '1' is equal to the width of the rollerboard, 
   and whether the '1' and '0' is equal to all the elements of the rollerboard*/
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
             //Make the first row all '1's, and all other '0's
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
        /*Move the whole line to the left, 
        if it can’t be done, fill it from the right*/
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
        /*Move the whole line to the right, 
        if it can’t be done, fill it from the left*/
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
        //Same as above
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
        //Same as above
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
    //If is same, k will remain 0
    if(k>0)
    {
        return false;
    }
    return true;
}

roller arrtoarr(roller* r)
{
    //Transfer the arr elements then return
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

void print_move(roller* st, int move)
{
    int num=0;
   
   /*Because the access is from the result to the beginning, 
   it is necessary to print in reverse*/
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

void print_nosolution(roller* r, roller* h)
{
    free(r);
    free(h);
    print_error("No solution");
}