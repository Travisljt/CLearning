#include "rollerboard.h"

int move_num(char* s,roller* st)//BFS
{
    roller* r = ini_roll(LARGE);//Initialize r
    FILE* fp = file_open(s);
    copytoarr(&r[0],fp);
    roller conseq;
    consequence(&r[0],&conseq);//Get the consequence

    //Apply for a transit array
    roller* h = (roller*)my_malloc(sizeof(roller*)*STORE);
   
    //Counter for each "if not the same board"
    int cnt=0;

    //Flag for check if it is same or not
    int hflag[4]={true,true,true,true};

    //Used to record the last array element where the result appears
    int element=0;

    //Enter the queue loop
    for(int x=0;x<=cnt;x++)
    {  
      //Check if the element has been carried out
      if(r[x].flag==0)
      {  
       for(int i =0; i<r->row;i++)
         {
          for(int j =0; j<r->col;j++)
          {
            //Move every '1'
             if(r[x].arr[i][j]=='1')
             {
                //Four direction
                h[LEFT]=row_left_right(&r[x],LEFT,i);
                h[RIGHT]=row_left_right(&r[x],RIGHT,i);
                h[UP]=col_up_down(&r[x],UP,j);
                h[DOWN]=col_up_down(&r[x],DOWN,j);
                  
                //Iterate over the subset of the array and check for duplicates
                for(int k=0;k<=cnt;k++){
                  if(isSame(&r[k],&h[LEFT])) {hflag[LEFT]=false;}
                 }
                  if(hflag[LEFT])
                 {
                    cnt++;//ADD to rollerboard array
                    r[cnt]=arrtoarr(&h[LEFT]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;//Guiding the parent element in array

                    //Check if it is the result or not
                    if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;//Give a larger value to exit the loop
                    }
                  }
                

                //Same as above
                for(int k=0;k<=cnt;k++){
                   if(isSame(&r[k],&h[RIGHT])) {hflag[RIGHT]=false;}
                }
                  if(hflag[RIGHT])
                {
                    cnt++;
                    r[cnt]=arrtoarr(&h[RIGHT]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                      if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;
                    }   
                }
                
                //Same as above
                for(int k=0;k<=cnt;k++){
                   if(isSame(&r[k],&h[UP])) {hflag[UP]=false;}
                }
                  if(hflag[UP])
                {
                    cnt++;
                    r[cnt]=arrtoarr(&h[UP]);
                    r[cnt].flag=0;
                    r[cnt].parent=x;
                      if(isSame(&r[cnt],&conseq))
                    { 
                        element=cnt;
                        x=cnt+1;
                    }            
                }
                
                //Same as above
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
                      if(isSame(&r[cnt],&conseq))
                    {
                        element=cnt;
                        x=cnt+1;
                    }       
                } 
                
                //When all elements are checked, reset hflag
                hflag[LEFT]=true;
                hflag[RIGHT]=true;
                hflag[UP]=true;
                hflag[DOWN]=true;
             }
          } 
       } 

        //reset the flag
        r[x].flag = 1;
     }

       /*If no result is found in the requested space,
        stop searching and exit the program*/
       if(cnt>=(LARGE-MAXIUM))
       {
         print_nosolution(r,h);
       }
    }
    
    //Counter for mark the solution's elements
    int n = 0;

    //Use to jump out of the loop
    int temp=1;

    //Filter the required elements through the parent board
    while(temp!=JUMP)
    {
      st[n]=arrtoarr(&r[element]);
      st[n].flag=r[element].flag;
      st[n].parent=r[element].parent;
      element = r[element].parent;
      temp=st[n].parent;
      
      //Check if it is the result
      if(isSame(&st[n],&r[0]))
      {
        temp=JUMP;
      }
        n++;
    }             

    free(r);
    free(h);
   
   return n-1;//Elements-1 is equal to moves number
}