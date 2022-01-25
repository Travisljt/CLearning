#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define SIZE 30
#define MAXNUMTOKEN 100
#define MAXTOKENSIZE 50
#define strsame(A,B) (strcmp(A,B)==0)
#define ERROR(PHRASE) { fprintf(stderr,"Fatal Error %s occurred in %s, line %d\n",PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define A_ASCII 'A'
#define Z_ASCII 'Z'
#define Number_0 '0'
#define Number_9 '9'
#define alphabet 26
#define LIST 30

struct node{
  char c[5];
  struct node* next;
};
typedef struct node node;

struct stack{
  int num;
  node* top;
};
typedef struct stack stack;

typedef struct store
{
    char arr[MAXTOKENSIZE][MAXTOKENSIZE];//     $I = 1 ;    !!! 1 = arr[0][0]=1;
    int row;//row = 1;!!
    int col;//col = 1;!!
}store;


struct prog{
    char wds[MAXNUMTOKEN][MAXTOKENSIZE];
    int cw;
    store list[LIST];//list[0] - - "A"
 
};
typedef struct prog prog;



void Start_Program(prog* p);
void Instrclist(prog* p, stack* s);
void Instrc(prog* p,stack* s);
void Print(prog* p);
void Varname(prog* p);
void String(prog* p);
void Set(prog* p, stack* s);
void Polishlist(prog* p,stack* s);
void Polish(prog* p, stack* s);
void Pushdown(prog* p, stack* s);
void Integer(prog* p);
void Binaryop(prog* p, stack* s);
void Unaryop(prog* p, stack* s);
void Create(prog* p,stack* s);
void Filename(prog* p);
void Loop(prog* p,stack* s);




prog* isprogram(char* argv[]);
bool Isinstrc(prog* p);
void stack_push(char* p,stack* s);
void stack_pop(char* tem, stack* s);
//void stack_initialize
//void stack_free
bool boolNum(char* str);
void arr(prog* p, char* str1, char* str2);
bool Samesize(prog* p, int a, int b);




int main(int argc, char* argv[]){

    //test();
     if(argc != 2){
        fprintf(stderr, "Usage %s <filein><sileout\n>",argv[0]);
        exit(EXIT_FAILURE);
    }
    if(argc == 2)
    {
        prog* p = isprogram(&argv[1]);
        //  FILE* fp = fopen(argv[1],"r");  prog* parser = (prog*)calloc(1, sizeof(prog));
        Start_Program(p);
        printf("parsed OK!\n");
        return 0;
    }
        
        
}



prog* isprogram(char** argv)
{
    FILE* fp = fopen(*argv,"r");
    if(!fp){
        fprintf(stderr, "cannot write from %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    prog* parser = (prog*)calloc(1, sizeof(prog));
    int i = 0;
    while(fscanf(fp, "%s",parser->wds[i++])==1 && i < MAXNUMTOKEN){
        assert(i < MAXNUMTOKEN);
    }
    fclose(fp);
    return parser;

}

void Start_Program(prog* p)
{
    
    printf("this is start\n");
    stack* s = (stack*)calloc(sizeof(stack),1);
    s->num = 0;
    // for(int i=0;p->wds[i];i++){
    //     if(p->wds[i]=="BEGIN" && p->wds[i+1] == "{"){
    //         break;
    //     }   
    // }
   while(1){
    if(strsame(p->wds[p->cw],"BEGIN") &&strsame(p->wds[p->cw+1],"{")){
        p->cw = p ->cw + 2;
        Instrclist(p,s);
        break;
    }
    p->cw = p ->cw + 1;
    
   }
    
}
void Instrclist(prog* p, stack* s)
{
    // printf("this is instrclist  %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"}")){
        return;
    }//"A"
    else{
        if(Isinstrc(p)){
            Instrc(p,s);
            Instrclist(p,s);
        }
        else{
            ERROR("Something wrong instruction");
        }
    }
    
}
//     if(strsame(p->text[p->cword],"}"))
//     {
//         return;
//     }
//     else if(isInstrc(p))
//     {
//       instrc(p,s);
//       nextword(p);
//       instrclist(p,s);
//     }
//     else
//     {
//         on_error("Was expecting an instruction (in instrclist)");
//     }

bool Isinstrc(prog* p)
{
    if(strsame(p->wds[p->cw],"PRINT")){
        return true;
    }
    else if(strsame(p->wds[p->cw],"ONES") || strsame(p->wds[p->cw],"READ") ){
        return true;
    }
    else if(strsame(p->wds[p->cw],"SET")){
        return true;
    }
    else if(strsame(p->wds[p->cw],"LOOP")){
        return true;
    }
    else{
        ERROR("Soemthing wrong with <INSTRC>");
    }
}
void Instrc(prog* p,stack* s)
{
    // printf("this is instrc %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"PRINT")){
        p->cw = p ->cw + 1;
        Print(p);
    }
    else if(strsame(p->wds[p->cw],"ONES") || strsame(p->wds[p->cw],"READ") ){
        Create(p,s);
    }
    else if(strsame(p->wds[p->cw],"SET")){
        p->cw = p ->cw + 1;
        Set(p,s);
    }
    else if(strsame(p->wds[p->cw],"LOOP")){
        p->cw = p ->cw + 1;
        Loop(p,s);
    }
    else{
        ERROR("Soemthing wrong with <INSTRC>");
    }
    
}
void Print(prog* p)
{
    printf("this is print  %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] == '$'){
        Varname(p);
        int num = p->wds[p->cw][1] - A_ASCII;
        int P_col = p->list[num].col;
        int P_row = p->list[num].row;


        printf(" 這是 num   %d\n",num);
        printf(" 這是 col   %d\n",P_col);
        printf(" 這是 row   %d\n",P_row);
        for(int i = 0; i < P_row;i++){
            for(int j = 0; j < P_col;j++){
                printf(" %d",p->list[num].arr[i][j]);
            }
            printf("\n");
        }
        p->cw = p ->cw + 1;
 
        
        
    }
    else if(p->wds[p->cw][0] == '"'){
        String(p);
        int length = strlen( p->wds[p->cw]);
        for(int i = 1; i < length -1; i ++){
            printf("%c",p->wds[p->cw][i]);
        }
        printf("\n");
    }
    else{
        ERROR("Something wrong with Varname or String in Print");
    }
    
}

void Varname(prog* p)
{
    printf("this is varname %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] != '$'){
        ERROR("Should have $ sign");
    }
    int length = strlen(p->wds[p->cw]);
    if(length != 2 ){
        ERROR("One of the 26 possible variable between A to Z");
    }
    if(p->wds[p->cw][1] < A_ASCII || p->wds[p->cw][1] > Z_ASCII ){
        ERROR("Should between A to Z");
    }
    if(p->wds[p->cw][1] >= A_ASCII || p->wds[p->cw][1] <= Z_ASCII){
        return;
    }
    else{
        ERROR("Something wrong here!");
    }

}

void String(prog* p)
{
    printf("this is string  %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] != '"'){
        ERROR("Should have "" sign in the begining");
    }
    int length = strlen(p->wds[p->cw]);
    for(int i = 1; i < length -1; i ++){
        if(p->wds[p->cw][i]== ' '){
            ERROR("Cannot have space in it");
        }
    }
    if(p->wds[p->cw][length-1] != '"'){
        ERROR("Should have "" sign in the end");
    }
    
    p->cw = p ->cw + 1;
    return;
}

void Set(prog* p, stack* s)
{   
    printf("this is set  %s\n",p->wds[p->cw]);
    Varname(p);
    stack_push(p->wds[p->cw],s);
    p->cw = p ->cw + 1;
    if(!strsame(p->wds[p->cw], ":=")){ 
        ERROR("No := in Set ?");
    }
    p->cw = p ->cw + 1;
    Polishlist(p,s);


}
void Polishlist(prog* p,stack* s)
{
    // printf("this is polishlist %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] == ';'){
        // char var[] char tem[] stack_pop(s,tem)  stack_pop(s,var)
        //if tem is integer,  $A -> p->list[A].arr[0][0] = 5; p->list[A].row = 1 , p->list[A].col = 1;
        //if tem is $B   $B - $A size is same or not  {  tem.data -> var.data }
        char var[SIZE];
        char tem[SIZE];
        stack_pop(tem,s);
        stack_pop(var,s);
        printf("tem = %s, var = %s\n",tem,var);
        if(boolNum(tem)){
            int num = atoi(tem);
            int sequence = var[1] - A_ASCII;
            p->list[sequence].arr[0][0] = num;
            p->list[sequence].row = 1;
            p->list[sequence].col = 1;
        }

        else{
            int sequence1 = alphabet;
            int sequence2 = var[1] - A_ASCII;
            printf("var = %c\n",var[1]);
            int col = p->list[sequence2].col;
            int row = p->list[sequence1].row;
            for(int i = 0 ;i < row; i ++){
                for(int j = 0; j < col;j++){
                    p->list[sequence2].arr[i][j] = p->list[sequence1].arr[i][j];
                    printf("%d",p->list[sequence2].arr[i][j]);
                }printf("\n");
            }
            p->list[sequence2].row = p->list[sequence1].row;
            p->list[sequence2].col = p->list[sequence1].col;
        }
        

        p->cw = p ->cw + 1;
        return;
    }
    
   
    else{
       Polish(p,s);
       p->cw = p ->cw + 1;
       Polishlist(p,s);
    }
    
}

void Polish(prog* p, stack* s)
{
    
    // printf("this is polish  %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] == 'U'){
        Unaryop(p,s);
    }
    if(p->wds[p->cw][0] == 'B'){
        Binaryop(p,s);
    } 
    
    if((p->wds[p->cw][0] < A_ASCII || p->wds[p->cw][0] > Z_ASCII) ||p->wds[p->cw][0] < Number_0 || p->wds[p->cw][0] > Number_9 ){
        
        Pushdown(p,s);//
    }
    

    else{
        ERROR("Something wrong with Polish");
    }
}

void Pushdown(prog* p, stack* s)
{
    // printf("this is Pushdown  %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] == '$'){
        Varname(p);
        stack_push(p->wds[p->cw],s);

    }
    else if(p->wds[p->cw][0] < A_ASCII || p->wds[p->cw][0] > Z_ASCII){
        Integer(p);
        stack_push(p->wds[p->cw],s);
    }
    
}

void Integer(prog* p)
{
    printf("this is integer %s\n",p->wds[p->cw]);
    int length = strlen(p->wds[p->cw]);
    for(int i = 0; i < length; i ++){
        if(p->wds[p->cw][0] < Number_0 || p->wds[p->cw][0] > Number_9){
            ERROR("Number should ne a non negative number");
        }
    }
}

void Unaryop(prog* p,stack* s)
{
    // printf("this is unaryop %s\n",p->wds[p->cw]);
    if(!strsame(p->wds[p->cw],"U-EIGHTCOUNT") && !strsame(p->wds[p->cw],"U-NOT") ){
        ERROR("Something wrong with U-NOT AND U-EIGHTCOUNT");
    }
}

void Binaryop(prog* p, stack* s)
{
    
    // printf("this is brnaryop %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"B-AND")){
        return;
    }
    else if(strsame(p->wds[p->cw],"B-OR")){
        return;
    }
    else if(strsame(p->wds[p->cw],"B-GREATER")){
        return;
    }
    else if(strsame(p->wds[p->cw],"B-LESS")){
        return;
    }
    else if(strsame(p->wds[p->cw],"B-ADD")){ // B-ADD  stack_pop(st2)  stack_pop(str1)    if(str1 && str2 都是数字){ %d + %d}
                                            //else{ str1 or str2 isnumber? 假设str1是数字，那就将他的row，col跟str2相等。反之，str2是数字，将他的row，col跟str1相等    if(str1 && str2是否一个size)  for循环两次传值}
        char str1[SIZE];
        char str2[SIZE];
        char tmp[SIZE] = "TMP";
        stack_pop(str1,s);
        stack_pop(str2,s);

        
        if(boolNum(str1) && boolNum(str2)){ 
            int a;
            int b;
            sscanf(str1,"%d",&a);
            sscanf(str2,"%d",&b);
            p->list[alphabet].arr[0][0] = a + b;
            p->list[alphabet].row = 1;
            p->list[alphabet].col = 1;
            stack_push(tmp,s);
        }
        else{
            
            arr(p,str2, str1);
            int a;
            int b;
            if(boolNum(str1))
            {
               a = alphabet+1;
               b = str2[1] - A_ASCII;
            }
            else if(boolNum(str2))
            {
               a = alphabet+1;
               b = str1[1] - A_ASCII;
            }
            else
            {
               a = str1[1]-A_ASCII;
               b = str2[1]-A_ASCII;
            }
            printf("a=%d,b=%d\n",a,b);
            if(Samesize(p,a,b)){
                int m;
                int n;
                int row = p->list[a].row;
                int col = p->list[a].col;
                for(int i = 0; i < row; i ++){
                    for(int j = 0; j < col; j ++){
                        m = p->list[a].arr[i][j];
                        n = p->list[b].arr[i][j];
                        p->list[alphabet].arr[i][j] = m + n;
                        printf("%d ",p->list[alphabet].arr[i][j]);
                    }printf("\n");
                }
                p->list[alphabet].col = p->list[a].col;
                p->list[alphabet].row = p->list[a].row;
                stack_push(tmp,s);
            }
        }
        return;
    }
    else if(strsame(p->wds[p->cw],"B-TIMES")){
        return;
    }
    else if(strsame(p->wds[p->cw],"B-EQUALS")){
        return;
    }
    else{
        printf("hi\n");
        ERROR("Something wrong with B-AND or B-OR or B-GREATER or B-LESS or B-ADD or B-TIMES or B-EQUALS");
    }
}


void Create(prog* p,stack* s)
{
    printf("this is create  %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"ONES")){
        p->cw = p ->cw + 1;
        Integer(p);
        stack_push(p->wds[p->cw],s);  //if is integer 6, then  stack_push(s,p->wds[p->cw]);  //入栈
        p->cw = p ->cw + 1;
        Integer(p);
        stack_push(p->wds[p->cw],s);  //if is integer 5 then stack_push(s,p->wds[p->cw]);//入栈2
        p->cw = p ->cw + 1;
        Varname(p);//if is varname, char str1[x], char str2[x]  stack_pop(s,str1) ->5, stack_pop(s,str2) ->6;  sscanf(str1,"%d",&n); n = 5   sscanf(str2,"%d",&m);  m==6 
        //p->list[A].arr[i][j]   for(int i=0) for(int j=0) {p->list[A].arr[i][j] = 1;}   p->list[A].row = m; p->list[A].col = n;
        char row[SIZE];
        char col[SIZE];
        int n;
        int m;
        stack_pop(col,s);
        stack_pop(row,s);
        sscanf(row,"%d",&m);
        sscanf(col,"%d",&n);
        int sequence = p->wds[p->cw][1] - A_ASCII;
        for(int i = 0; i < m; i ++){
            for(int j = 0; j < n; j ++){
                p->list[sequence].arr[i][j] = 1;
            }
        }
        p->list[sequence].row = m;
        p->list[sequence].col = n;
        p->cw = p ->cw + 1;

    }
    if(strsame(p->wds[p->cw],"READ")){
        p->cw = p ->cw + 1;
         Filename(p);
         Varname(p);
         p->cw = p ->cw + 1;
    }

}
void Filename(prog* p)
{
    // printf("this is filename %s\n",p->wds[p->cw]);
    String(p);
}

void Loop(prog* p,stack* s)
{
    Varname(p);
    p->cw = p ->cw + 1;
    Integer(p);
    p->cw = p ->cw + 1;
    if(!strsame(p->wds[p->cw],"{")){
        ERROR("No { in Loop ?");
    }
    p->cw = p ->cw + 1;
    Instrclist(p,s);
}



void stack_push(char* p,stack* s)
{
    if(s){
        s->num = s->num+1;
        node* f = calloc(1,sizeof(node*));
        strcpy(f->c,p);
        f->next = s ->top;
        s->top = f;
    }

}
void stack_pop(char* tem, stack* s)
{
    if((s == NULL) || s->top == NULL){
        ERROR("Something wrong with stack_pop");
    }
    node* f = s->top->next;
    strcpy(tem,s->top->c);
    free(s->top);
    s->top = f;
    s->num = s->num - 1;

}




bool boolNum(char* str)
{
   int length =  strlen(str);
   for(int i=0;i<length;i++)
   {
      if(!isdigit(str[i]))
      {
          return false;
      }
   }
   return true;
}



void arr(prog* p, char* str2, char* str1)
{
    if(boolNum(str2)){
        int a;
        //int b;
        sscanf(str2,"%d",&a);
        int sequence = str1[1] - A_ASCII;
        p->list[alphabet+1].col = p->list[sequence].col;
        p->list[alphabet+1].row = p->list[sequence].row;
        for(int i = 0; i < p->list[sequence].row; i ++){
            for(int j = 0; j < p->list[sequence].col; j ++){
                p->list[alphabet+1].arr[i][j] = a;
            }
        }
    }

    if(boolNum(str1)){
        int a;
        //int b;
        sscanf(str1,"%d",&a);
        int sequence = str2[1] - A_ASCII;
        p->list[alphabet+1].col = p->list[sequence].col;
        p->list[alphabet+1].row = p->list[sequence].row;
        for(int i = 0; i < p->list[sequence].row; i ++){
            for(int j = 0; j < p->list[sequence].col; j ++){
                p->list[alphabet+1].arr[i][j] = a;
            }
        }
    }
    

}


bool Samesize(prog* p, int a, int b)
{
    if(p->list[a].row == p->list[b].row){
        if(p->list[a].col == p->list[b].col){
            return true;
        }
    }

    return false;
}
