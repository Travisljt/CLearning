#include "nlab.h"

int main(int argc, char* argv[])
{
    test();
    if(argc==2)
    {
        //Start the program
        isProgram(argv[1]);
    }
    else 
    {
        fprintf(stderr,"ERROR : Incorrect input. try "\
        "%s <File> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}

//General functions
void* nfopen(char* fname, char* mode)
{
   FILE* fp;
   fp = fopen(fname, mode);
   if(!fp){
      on_error("Cannot open file");
   }
   return fp;
}

//General functions
void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

//General functions
void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

void isProgram(char* str)
{
    //Initialize
    Program* p = prog_initialize();
    stack* s = stack_initialize();
    FILE* fp = nfopen(str,"rt");
    char buf[WORDSIZE];
    bool check = false;
    int i = 0;

    //Read from file
    do 
    {
        if(fscanf(fp,"%s",buf)!=1)
        {
            check = true;
        }
        else
        {
            strcpy(p->text[i],buf);
            i++;
        }
    }while(!check);

    //Search for the program entry -> 'BEGIN' and '{' 
    for(int i=0;p->text[i];i++)
    {
        if(strsame(p->text[i],"BEGIN") && strsame(p->text[i+1],"{"))
        {
        p->cword = i+PROGSTART;//Start  
        instrclist(p,s);
        break;
        }
    }

    fclose(fp);
    assert(stack_free(s));
    prog_free(p);
    }

//Stack functions
stack* stack_initialize(void)
{
    stack* s = (stack*)ncalloc(sizeof(stack),1);
    s->num = 0;
    return s;
}

//Stack functions
void stack_push(stack* s, char* str)
{
    if(s!=NULL)
    {
        node* tmp = (node*)ncalloc(sizeof(node),1);
        strcpy(tmp->c,str);
        tmp->next = s->top;
        s->top = tmp; 
        s->num = s->num + 1;
    }   
}

//Stack functions
bool stack_pop(stack* s, char* str)
{
    node* tmp;
    if(s == NULL || s->top == NULL)
    {
        return false;
    }
    tmp = s->top->next;
    strcpy(str,s->top->c);
    free(s->top);
    s->top = tmp;
    s->num = s->num - 1;

    return true; 
}

//Stack functions
bool stack_free(stack* s)
{
   if(s)
   {
      node* tmp;
      node* p = s->top;
      while(p)
      {
          tmp = p->next;
          free(p);
          p = tmp;
      }
      free(s);
   }
    return true;
}

//Program initialize
Program* prog_initialize(void)
{
    Program* p = (Program*)ncalloc(1,sizeof(Program));
    p->text = (List*)ncalloc(sizeof(List),LISTSIZE);
    for(int i=0;i<LISTSIZE;i++)
    {
        p->text[i] = (char*)ncalloc(sizeof(char),WORDSIZE);
    }
    p->store = (varn*)ncalloc(sizeof(varn),ALPHASIZE);
    p->cword = 0;

    return p;
}

//Program free
void prog_free(Program* p)
{
    for(int i=0;i<LISTSIZE;i++)
    {
        free(p->text[i]);
    }
    free(p->text);
    free(p->store);
    free(p);
}

void nextword(Program* p)
{
    p->cword = p->cword + 1;
}

void int2arr(Program* p, char* str1, char* str2)
{
    /*Judgment on two strings, if it is a number, 
    expand the size of the array to be consistent with another variable*/
    if(isNum(str1))
    {
       int n,m=0;
       sscanf(str1,"%d",&n);
       for(int i=0;i<ALPHASIZE;i++)
       {
           if(strsame(str2,p->store[i].var))
           {
               m = i;
           }
       }
       //Storing digits briefly in another area
       strcpy(p->store[TEMSTORE+1].var,str1);
       p->store[TEMSTORE+1].sizecol = p->store[m].sizecol;
       p->store[TEMSTORE+1].sizerow = p->store[m].sizerow;
       for(int x=0;x<(p->store[m].sizerow);x++)
       {
           for(int y=0;y<(p->store[m].sizerow);y++)
           {
               p->store[TEMSTORE+1].arr[x][y] = n;
           }
       }
    }
    if(isNum(str2))
    {
       int n,m=0;
       sscanf(str2,"%d",&n);
       for(int i=0;i<ALPHASIZE;i++)
       {
           if(strsame(str1,p->store[i].var))
           {
               m = i;
           }
       }
       strcpy(p->store[TEMSTORE+1].var,str2);
       p->store[TEMSTORE+1].sizecol = p->store[m].sizecol;
       p->store[TEMSTORE+1].sizerow = p->store[m].sizerow;
       for(int x=0;x<(p->store[m].sizerow);x++)
       {
           for(int y=0;y<(p->store[m].sizerow);y++)
           {
               p->store[TEMSTORE+1].arr[x][y] = n;
           }
       }
    }

    /*Determine if one of the variables is an array of size 1x1 
    and make its array size equal to the array size of the other element*/
    if(isscale(p,str1))
    {
        int n=0, m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
           if(strsame(str1,p->store[i].var))
           {
               n = i;
           }
           if(strsame(str2,p->store[i].var))
           {
               m = i;
           }
        }
        int num = p->store[n].arr[0][0] ;
        p->store[n].sizecol = p->store[m].sizecol;
        p->store[n].sizerow = p->store[m].sizerow;
        for(int x=0;x<(p->store[n].sizerow);x++)
        {
            for(int y=0;y<(p->store[n].sizerow);y++)
            {
                p->store[n].arr[x][y] = num;
            }
        }
    }
    if(isscale(p,str2))
    {
        int n=0, m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
           if(strsame(str2,p->store[i].var))
           {
               n = i;
           }
           if(strsame(str1,p->store[i].var))
           {
               m = i;
           }
        }
        int num = p->store[n].arr[0][0] ;
        p->store[n].sizecol = p->store[m].sizecol;
        p->store[n].sizerow = p->store[m].sizerow;
        for(int x=0;x<(p->store[n].sizerow);x++)
        {
            for(int y=0;y<(p->store[n].sizerow);y++)
            {
                p->store[n].arr[x][y] = num;
            }
        }
    }
    
}

bool isscale(Program* p, char* str)
{
    int n = 0;
    for(int i=0;i<ALPHASIZE;i++)
    {
        if(strsame(str,p->store[i].var))
        {
            n = i;
        }
    }
    //Judge if it is 1x1 scale
    if(p->store[n].sizecol==1 && p->store[n].sizerow==1)
    {
        return true;
    }
    return false;
}

bool isInstrc(Program* p)
{
    if(strsame(p->text[p->cword],"ONES"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"SET"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"PRINT"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"READ"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"LOOP"))
    {
        return true;
    }

    return false;
}

bool isCreate(Program* p)
{
    if(strsame(p->text[p->cword],"ONES"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"READ"))
    {
        return true;
    }
    return false;
}

bool isSET(Program* p)
{
    if(strsame(p->text[p->cword],"SET"))
    {
        return true;
    }
    return false;
}

bool isPRINT(Program* p)
{
    if(strsame(p->text[p->cword],"PRINT"))
    {
        return true;
    }
    return false;
}

bool isLoop(Program* p)
{
    if(strsame(p->text[p->cword],"LOOP"))
    {
        return true;
    }
    return false;
}

bool isVarname(Program* p)
{
   char* pstr = p->text[p->cword];
   if(pstr[0]=='$')
   {
       if(isalpha(pstr[1]))
       {
           return true;
       }
   }
   return false;
}

bool isPolishlist(Program* p)
{
    if(strsame(p->text[p->cword],";"))
    {
        return true;
    }
    if(isPolish(p))
    {
        return true;
    }

    return false;
}

bool isPolish(Program* p)
{
    if(isPushdown(p))
    {
       return true;
    }
    if(isUnaryop(p))
    {
       return true;
    }
    if(isBinaryop(p))
    {
       return true;
    }
    
    return false;
}


bool isPushdown(Program* p)
{
    if(isVarname(p))
    {
        return true;
    }
    if(isInteger(p))
    {
        return true;
    }
   
   return false;
}

bool isUnaryop(Program* p)
{
    if(strsame(p->text[p->cword],"U-NOT"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"U-EIGHTCOUNT"))
    {
        return true;
    }

    return false;
}

bool isBinaryop(Program* p)
{
    if(strsame(p->text[p->cword],"B-AND"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-OR"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-GREATER"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-LESS"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-ADD"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-TIMES"))
    {
        return true;
    }
    if(strsame(p->text[p->cword],"B-EQUALS"))
    {
        return true;
    }
    return false;
}

bool isInteger(Program* p)
{
   char* pstr = p->text[p->cword];
   for(int i=0;i<(int)strlen(pstr);i++)
   {
      if(!isdigit(pstr[i]))
      {
          return false;
      }
   }
   return true;
}

bool isNum(char* str)
{
   for(int i=0;i<(int)strlen(str);i++)
   {
      if(!isdigit(str[i]))
      {
          return false;
      }
   }
   return true;
}

bool isSamesize(Program* p, int n, int m)
{
    
    if(p->store[n].sizerow == p->store[m].sizerow)
    {
        if(p->store[n].sizecol == p->store[m].sizecol)
        {
            return true;
        }
    }

    return false;
}

bool isString(Program* p)
{
    char* pstr = p->text[p->cword];
    int len = (int)strlen(pstr);
    if(pstr[0]=='"' && pstr[len-1]=='"')
    {
        return true;
    }
    return false;
}





void instrclist(Program* p, stack* s)
{
    if(strsame(p->text[p->cword],"}"))
    {
        return;
    }
    else if(isInstrc(p))
    {
        //recursion
        instrc(p,s);
        nextword(p);
        instrclist(p,s);
    }
    else if(strsame(p->text[p->cword],"#"))
    {
        //Skip the characters after # 
        //Find the next keyword
        while(p->text!=NULL)
        {
           p->cword += 1;
           if(isInstrc(p))
           {
               break;
           }
        }
        instrc(p,s);
        nextword(p);
        instrclist(p,s);
    }
    else
    {
        on_error("Was expecting an instruction (in instrclist)");
    }
}

void instrc(Program* p, stack* s)
{
    if(isCreate(p))
    {
        if(strsame(p->text[p->cword],"ONES"))
        {
            nextword(p);
            func_ONES(p,s);
        }
        if(strsame(p->text[p->cword],"READ"))
        {
            nextword(p);
            func_READ(p,s);
        }
    }
    if(isLoop(p))
    {
        nextword(p);
        func_LOOP(p,s);
    }
    if(isSET(p))
    {
        nextword(p);
        func_SET(p,s);
    }

    if(isPRINT(p))
    {
        nextword(p);
        func_PRINT(p);
    }
}

void func_ONES(Program* p, stack* s)
{
    if(isInteger(p))
    {
        stack_push(s,p->text[p->cword]);//Push the number (Normally for two) 
        nextword(p);
        func_ONES(p,s);
    }
    else if(isVarname(p))
    {
        char row[WORDSIZE],col[WORDSIZE];
        assert(stack_pop(s,col));//second number
        assert(stack_pop(s,row));//first number
        int i,j,n;
        sscanf(row,"%d",&i);
        sscanf(col,"%d",&j);
        char* pstr = p->text[p->cword];
        n = pstr[1] - 'A';//n = $A
         //Select the second element from "$[A-Z]", which is '[A-Z]'
         //Store into the 'varn'
        strcpy(p->store[n].var,p->text[p->cword]);
        for(int x=0;x<i;x++)
        {
            for(int y=0;y<j;y++)
            {
                p->store[n].arr[x][y] = 1;
            }
        }
        p->store[n].sizerow = i;
        p->store[n].sizecol = j;
    }
    else
    {
       on_error("ERROR: in func_ONES");
    }
}


void func_SET(Program* p, stack* s)
{
    // Set ->   <Varname> := <Polishlist>
    if(isVarname(p))
    {
        int n;
        n = p->text[p->cword][1] - 'A';
        strcpy(p->store[n].var,p->text[p->cword]);
        stack_push(s,p->text[p->cword]);
        nextword(p);
        if(strsame(p->text[p->cword],":="))
        {
           nextword(p);
            if(isPolishlist(p))
            {
               polishlist(p,s);
            }
            else
            {
               on_error("ERROR: Happened in 'fuc_SET'");
            }
        }
         else
        {
            on_error("ERROR: Happened in 'fuc_SET'");
        }
    }
    else
    {
        on_error("ERROR: Happened in 'fuc_SET'");
    }

}


void polishlist(Program* p,stack* s)
{

    // p = "$A 2 B-ADD"
    if(isPolish(p))
    {
       polish(p,s);
       nextword(p);//p->cword
       polishlist(p,s); 
    }
    else if(strsame(p->text[p->cword],";"))
    {
        //At the end of SET function, pop up all elements in the stack
        //Assign the first element to the second element
        char str[VARIABLESIZE], temp[VARIABLESIZE];
        assert(stack_pop(s,temp));
        assert(stack_pop(s,str));
        //If it is number, assign it directly
        if(isNum(temp))
        {
           int num,ele=0;
           sscanf(temp,"%d",&num);
           for(int i=0;i<ALPHASIZE;i++)
           {
              if(strsame(p->store[i].var,str))
              {
                 ele = i;
              }
           }
           p->store[ele].arr[0][0] = num;
           p->store[ele].sizecol = 1;
           p->store[ele].sizerow = 1;
        }
        //Otherwise, array to array
        else
        {
        int n=0, m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(p->store[i].var,str))
            {
               n = i;
            }
            if(strsame(p->store[i].var,temp))
            {
               m = i;
            }
        }
        for(int i=0;i<(p->store[m].sizerow);i++)
        {
            for(int j=0;j<(p->store[m].sizecol);j++)
            {
                p->store[n].arr[i][j] = p->store[m].arr[i][j];
            }
        }
        p->store[n].sizerow = p->store[m].sizerow;
        p->store[n].sizecol = p->store[m].sizecol;
        }
          
    }
    else
    {
        on_error("ERROR: in polishlist");
    }
}


void polish(Program* p, stack* s)
{
    if(isPushdown(p))
    {
        pushdown(p,s);
    }
    else if(isUnaryop(p))
    {
        unary(p,s);
    }
    else if(isBinaryop(p))
    {
        binary(p,s);
    }
    else
    {
       on_error("ERROR: in polish");
    }

}

void pushdown(Program* p, stack* s)
{
    if(isVarname(p))
    {
       stack_push(s,p->text[p->cword]);
    }
    else if(isInteger(p))
    {
       stack_push(s,p->text[p->cword]);
    }
    else
    {
        on_error("ERROR: in pushdown");
    }
}

void unary(Program* p, stack* s)
{
    if(strsame(p->text[p->cword],"U-NOT"))
    {
        u_NOT(p,s);
    }
    if(strsame(p->text[p->cword],"U-EIGHTCOUNT"))
    {
        u_EIGHTCOUNT(p,s);
    }   
}

void binary(Program* p, stack* s)
{
    if(strsame(p->text[p->cword],"B-AND"))
    {
        b_AND(p,s);
    }
    if(strsame(p->text[p->cword],"B-OR"))
    {
        b_OR(p,s);
    }
    if(strsame(p->text[p->cword],"B-GREATER"))
    {
        b_GREATER(p,s);
    }
    if(strsame(p->text[p->cword],"B-LESS"))
    {
        b_LESS(p,s);
    }
    if(strsame(p->text[p->cword],"B-ADD"))
    {
        b_ADD(p,s);
    }
    if(strsame(p->text[p->cword],"B-TIMES"))
    {
        b_TIMES(p,s);
    }
    if(strsame(p->text[p->cword],"B-EQUALS"))
    {
        b_EQUAL(p,s);
    }
}

void u_NOT(Program* p, stack* s)
{
    //Pop up element, then push the result
    char str[VARIABLESIZE],  tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str));
    if(isNum(str))
    {
        int n;
        sscanf(str,"%d",&n);
        strcpy(p->store[TEMSTORE].var,tem);
        //Not gate
        if(n==0)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        int n=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str,p->store[i].var))
            {
                n = i;
            }
        }
        int x;
        strcpy(p->store[TEMSTORE].var,tem);
        for(int i=0;i<(p->store[n].sizerow);i++)
        {
            for(int j=0;j<(p->store[n].sizecol);j++)
            {
                x = p->store[n].arr[i][j];
                if(x==0)
                {
                    p->store[TEMSTORE].arr[i][j] = 1;
                }
                else
                {
                    p->store[TEMSTORE].arr[i][j] = 0;
                }
            }
        }
        p->store[TEMSTORE].sizecol = p->store[n].sizecol;
        p->store[TEMSTORE].sizerow = p->store[n].sizerow;
        stack_push(s,tem);
    }     
}

void u_EIGHTCOUNT(Program* p, stack* s)
{
    char str[VARIABLESIZE],  tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str));
    if(isNum(str))
    {
        strcpy(p->store[TEMSTORE].var,tem);
        p->store[TEMSTORE].arr[0][0] = 0; //1x1 scale has no around cells
        p->store[TEMSTORE].sizecol = 1;
        p->store[TEMSTORE].sizerow = 1;
        stack_push(s,tem);
    }
    else
    {
        int n=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str,p->store[i].var))
            {
                n = i;
            }
        }
        int countarr[ARRMAX][ARRMAX];
        strcpy(p->store[TEMSTORE].var,tem);
        for(int i=0;i<(p->store[n].sizerow);i++)
        {
            for(int j=0;j<(p->store[n].sizecol);j++)
            {
                //Calculate the number
               countarr[i][j] = func_eightneighbour(p,n,i,j);
            }
        }
        for(int i=0;i<(p->store[n].sizerow);i++)
        {
            for(int j=0;j<(p->store[n].sizecol);j++)
            {
               p->store[TEMSTORE].arr[i][j] = countarr[i][j];    
            }
        }
        p->store[TEMSTORE].sizecol = p->store[n].sizecol;
        p->store[TEMSTORE].sizerow = p->store[n].sizerow;
        stack_push(s,tem);
    }     
}

void b_AND(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    //If both are number
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        if(n>0 && m>0)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        //Change number or 1x1 scale to the same size
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
            n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
            m = i;
            }
        }
        //Judgement of array size
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    if(x>0&&y>0)
                    {
                        p->store[TEMSTORE].arr[i][j] = 1;
                    }
                    else
                    {
                        p->store[TEMSTORE].arr[i][j] = 0;
                    }
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-AND %s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }  
}

void b_OR(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        if(n>0 || m>0)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
            n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
            m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    if(x>0 || y>0)
                    {
                        p->store[TEMSTORE].arr[i][j] = 1;
                    }
                    else
                    {
                        p->store[TEMSTORE].arr[i][j] = 0;
                    }
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-OR %s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }  
}

void b_GREATER(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        if(n>m)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
            n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
            m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    if(x>y)
                    {
                        p->store[TEMSTORE].arr[i][j] = 1;
                    }
                    else
                    {
                        p->store[TEMSTORE].arr[i][j] = 0;
                    }
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-GREATER%s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }   
}

void b_LESS(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        if(n<m)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
            n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
            m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    if(x<y)
                    {
                        p->store[TEMSTORE].arr[i][j] = 1;
                    }
                    else
                    {
                        p->store[TEMSTORE].arr[i][j] = 0;
                    } 
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-LESS%s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }    
}

void b_ADD(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        p->store[TEMSTORE].arr[0][0] = n + m;
        p->store[TEMSTORE].sizecol = 1;
        p->store[TEMSTORE].sizerow = 1;
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
                n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
                m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    p->store[TEMSTORE].arr[i][j] = x + y;
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-ADD %s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }
}

void b_TIMES(Program* p, stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        p->store[TEMSTORE].arr[0][0] = n * m;
        p->store[TEMSTORE].sizecol = 1;
        p->store[TEMSTORE].sizerow = 1;
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
                n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
                m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    p->store[TEMSTORE].arr[i][j] = x * y;
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-TIMES %s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }
}

void b_EQUAL(Program* p,stack* s)
{
    char str1[VARIABLESIZE], str2[VARIABLESIZE], tem[VARIABLESIZE] ="$TEM";
    assert(stack_pop(s,str2));
    assert(stack_pop(s,str1));
    if(isNum(str1)&&isNum(str2))
    {
        int n,m;
        sscanf(str1,"%d",&n);
        sscanf(str2,"%d",&m);
        strcpy(p->store[TEMSTORE].var,tem);
        if(n == m)
        {
            p->store[TEMSTORE].arr[0][0] = 1;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        else
        {
            p->store[TEMSTORE].arr[0][0] = 0;
            p->store[TEMSTORE].sizecol = 1;
            p->store[TEMSTORE].sizerow = 1;
        }
        stack_push(s,tem);
    }
    else
    {
        int2arr(p,str1,str2);
        int n=0,m=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(str1,p->store[i].var))
            {
            n = i;
            }
            if(strsame(str2,p->store[i].var))
            {
            m = i;
            }
        }
        if(isSamesize(p,n,m))
        {
            int x,y;
            strcpy(p->store[TEMSTORE].var,tem);
            for(int i=0;i<(p->store[n].sizerow);i++)
            {
                for(int j=0;j<(p->store[n].sizecol);j++)
                {
                    x = p->store[n].arr[i][j];
                    y = p->store[m].arr[i][j];
                    if(x == y)
                    {
                        p->store[TEMSTORE].arr[i][j] = 1;
                    }
                    else
                    {
                        p->store[TEMSTORE].arr[i][j] = 0;
                    }
                }
            }
            p->store[TEMSTORE].sizecol = p->store[n].sizecol;
            p->store[TEMSTORE].sizerow = p->store[n].sizerow;
            stack_push(s,tem);
        }
        else
        {
            fprintf(stderr, "B-EQUALS %s and %s arrays are not the same size\n", str1,str2);
            exit(EXIT_FAILURE);
        }
    }  
}


void func_PRINT(Program* p)
{
    if(isVarname(p))
    {
        //Compile interpreter
        #ifdef INTERP
        int n=0;
        for(int i=0;i<ALPHASIZE;i++)
        {
            if(strsame(p->text[p->cword],p->store[i].var))
            {
                n = i;
            }
        }
        for(int i=0;i<(p->store[n].sizerow);i++)
        {
            for(int j=0;j<(p->store[n].sizecol);j++)
            {
                printf("%d ",p->store[n].arr[i][j]);
            }
            printf("\n");
        }
        #endif
        return;
    }
    if(isString(p))
    {
        #ifdef INTERP
        char* pstr = p->text[p->cword];
        int len = (int)strlen(pstr);
        if(pstr[0]=='"' && pstr[len-1]=='"')
        {
            for(int i=1;i<len-1;i++)
            {
                printf("%c",pstr[i]);
            }
            printf("\n");
        }
        #endif
        return;
    }
}

void func_LOOP(Program* p, stack* s)
{
    //Loop -> <Varname> <Integer> {
    if(isVarname(p))
    {
        int m;
        m = p->text[p->cword][1] - 'A';
        strcpy(p->store[m].var,p->text[p->cword]);
        stack_push(s,p->text[p->cword]);
        nextword(p);
        if(isInteger(p))
        {
            stack_push(s,p->text[p->cword]);
            nextword(p);
            if(strsame(p->text[p->cword],"{"))
            {
                char str1[VARIABLESIZE], str2[VARIABLESIZE];
                assert(stack_pop(s,str2));
                assert(stack_pop(s,str1));
                if(isNum(str2)&&!isNum(str1))
                {
                    int count,n=0;
                    sscanf(str2,"%d",&count);
                    for(int i=0;i<ALPHASIZE;i++)
                    {
                        if(strsame(str1,p->store[i].var))
                        {
                            n = i;
                            p->store[n].arr[0][0]= 1;
                            p->store[n].sizecol = 1;
                            p->store[n].sizerow = 1;
                        }
                    }
                    nextword(p);
                    //Mark the word number, then go back to calculate like a loop
                    int endword,startword;
                    startword = p->cword;
                    do
                    {
                        instrclist(p,s);
                        endword = p->cword;
                        p->cword = startword;
                        for(int i=0;i<(p->store[n].sizerow);i++)
                        {
                            for(int j=0;j<(p->store[n].sizecol);j++)
                                {
                                    p->store[n].arr[i][j] = p->store[n].arr[i][j] + 1;
                                }
                        }
                    }while(p->store[n].arr[0][0]<=count);
                    p->cword = endword;
                    instrclist(p,s);
                }
                else
                {
                   fprintf(stderr, "%s and %s arrays are non-compliant\n", str1,str2);
                   exit(EXIT_FAILURE);
                }

            }
            else
            {
                on_error("ERROR: <varname> <integer> '{'");
            }
        }
        else
        {
            on_error("ERROR: <varname> <integer> '{'");
        }
    }
    else
    {
        on_error("ERROR: <varname> <integer> '{'");
    }
}

void func_READ(Program* p, stack* s)
{
    //READ -> <String> <Varname>
    if(isString(p))
    {
        func_file(p,s);
        nextword(p);
        if(isVarname(p))
        {
            char str[VARIABLESIZE];
            assert(stack_pop(s,str));
            int n;
            n = p->text[p->cword][1] - 'A';
            strcpy(p->store[n].var,p->text[p->cword]);
            p->store[n].sizecol = p->store[TEMSTORE].sizecol;
            p->store[n].sizerow = p->store[TEMSTORE].sizerow;
            for(int i=0;i<p->store[n].sizerow;i++)
            {
                for(int j=0;j<p->store[n].sizecol;j++)
                {
                    p->store[n].arr[i][j] = p->store[TEMSTORE].arr[i][j];
                }
            }
        }
        else
        {
            on_error("ERROR: <filename> <varname>");
        }
    }
    else
    {
        on_error("ERROR: <filename> <varname>");
    }
}

int func_eightneighbour(Program* p, int n, int row, int col)
{
    //Game of life function
    int cnt=0;
    int sizerow = p->store[n].sizerow;
    int sizecol = p->store[n].sizecol;
    if(row-1<0)
    {
        if(col-1<0)
        {
            cnt = p->store[n].arr[row+1][col] + p->store[n].arr[row][col+1] + p->store[n].arr[row+1][col+1]; 
        }
        else if(col+1>=sizecol)
        {
            cnt = p->store[n].arr[row+1][col-1] + p->store[n].arr[row][col-1] + p->store[n].arr[row+1][col];
        }
        else
        {
            cnt = p->store[n].arr[row+1][col] + p->store[n].arr[row][col-1]>0 + p->store[n].arr[row][col+1] + \
            p->store[n].arr[row+1][col-1] + p->store[n].arr[row+1][col+1];
        }
    }

    else if(row+1>=sizerow)
    {
        if(col-1<0)
        {
            cnt = p->store[n].arr[row-1][col] + p->store[n].arr[row][col+1] + p->store[n].arr[row-1][col+1];
        }
        else if(col+1>=sizecol)
        {
            cnt = p->store[n].arr[row-1][col-1] + p->store[n].arr[row][col-1] + p->store[n].arr[row-1][col];
        }
        else
        {
            cnt = p->store[n].arr[row-1][col] + p->store[n].arr[row][col-1] + p->store[n].arr[row][col+1] + \
            p->store[n].arr[row-1][col-1] + p->store[n].arr[row-1][col+1];
        }
    }
    else if(col-1<0)
    {
        cnt = p->store[n].arr[row-1][col] + p->store[n].arr[row-1][col+1] + p->store[n].arr[row][col+1] + \
        p->store[n].arr[row+1][col+1] + p->store[n].arr[row+1][col];  
    }
    else if(col+1>=sizecol)
    {
        cnt = p->store[n].arr[row-1][col] + p->store[n].arr[row-1][col-1] + p->store[n].arr[row][col-1] + \
        p->store[n].arr[row+1][col-1] + p->store[n].arr[row+1][col];
    }
    else
    {
        cnt = p->store[n].arr[row+1][col] + p->store[n].arr[row-1][col] + \
        p->store[n].arr[row][col+1] + p->store[n].arr[row][col-1] + \
        p->store[n].arr[row+1][col+1] + p->store[n].arr[row+1][col-1] + \
        p->store[n].arr[row-1][col+1] + p->store[n].arr[row-1][col-1];
    }
    
    return cnt;
}

void func_file(Program* p, stack* s)
{
    char* pstr = p->text[p->cword];
    char* fpstr = (char*)ncalloc(sizeof(char),WORDSIZE);
    int len = (int)strlen(pstr);
    if(pstr[0]=='"' && pstr[len-1]=='"')
    {
        for(int i=1;i<len-1;i++)
        {
            //Store the file name
            fpstr[i-1] = pstr[i];
        }
    }

    FILE* fp = nfopen(fpstr,"rt");
    char tem[VARIABLESIZE]="$TEM";
    char buf[WORDSIZE];
    int row,col;
    strcpy(p->store[TEMSTORE].var,tem);
    stack_push(s,tem);
    //Once scan row
    if(fscanf(fp,"%s",buf)==1)
    {
        sscanf(buf,"%d",&row);
    }
    //Twice scan col
    if(fscanf(fp,"%s",buf)==1)
    {
        sscanf(buf,"%d",&col);
    }
    //Scan the array
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(fscanf(fp,"%s",buf)==1)
            {
                sscanf(buf,"%d",&p->store[TEMSTORE].arr[i][j]);       
            }
        }
    }
    p->store[TEMSTORE].sizecol = col;
    p->store[TEMSTORE].sizerow = row;
    fclose(fp);
    free(fpstr);
}

void test(void)
{
    Program* p = prog_initialize();
    p->cword = 0;
    strcpy(p->text[p->cword],"ONES");
    assert(isCreate(p));
    strcpy(p->text[p->cword],"READ");
    assert(isCreate(p));
    assert(isInstrc(p));
    strcpy(p->text[p->cword],"one");
    assert(!isCreate(p));
    strcpy(p->text[p->cword],"SET");
    assert(isSET(p));
    assert(isInstrc(p));
    strcpy(p->text[p->cword],"PRINT");
    assert(isPRINT(p));
    assert(isInstrc(p));
    strcpy(p->text[p->cword],"LOOP");
    assert(isLoop(p));
    assert(isInstrc(p));
    strcpy(p->text[p->cword],"$A");
    assert(isVarname(p));
    assert(isPushdown(p));
    assert(isPolish(p));
    strcpy(p->text[p->cword],"A");
    assert(!isVarname(p));
    strcpy(p->text[p->cword],"55");
    assert(isInteger(p));
    assert(isPushdown(p));
    assert(isPolish(p));
    strcpy(p->text[p->cword],"\"asd\"");
    assert(isString(p));
    strcpy(p->text[p->cword],";");
    assert(isPolishlist(p));
    strcpy(p->text[p->cword],"B-ADD");
    assert(isBinaryop(p));
    assert(isPolish(p));
    strcpy(p->text[p->cword],"b-times");
    assert(!isBinaryop(p));
    strcpy(p->text[p->cword],"U-NOT");
    assert(isUnaryop(p));
    assert(isPolish(p));

    char str[10] = "5";
    assert(isNum(str));

    int n=0,m=1;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            p->store[n].arr[i][j] = 2;
            p->store[m].arr[i][j] = 3;
        }
    }
    p->store[n].sizecol = 5;
    p->store[n].sizerow = 5;
    p->store[m].sizecol = 5;
    p->store[m].sizerow = 5;
    assert(isSamesize(p,n,m));
    
    char str1[10] = "$C";
    int k = 2;
    p->store[k].sizecol = 1;
    p->store[k].sizerow = 1;
    p->store[k].arr[0][0] = 5;
    isscale(p,str1);
    prog_free(p);
}

