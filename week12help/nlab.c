#include "nlab.h"

void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

int main(int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "Usage %s <filein><sileout\n>",argv[0]);
        exit(EXIT_FAILURE);
    }
    if(argc == 2)
    {
        prog* p = isprogram(&argv[1]);
        Start_Program(p);
        free(p);
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
    prog* parser = (prog*)ncalloc(1, sizeof(prog));
    int i = 0;
    while(fscanf(fp, "%s",parser->wds[i++])==1 && i < MAXNUMTOKEN){
        assert(i < MAXNUMTOKEN);
    }
    fclose(fp);
    return parser;
}

void Start_Program(prog* p)
{
    
    // printf("this is start\n");
    stack* s = (stack*)ncalloc(sizeof(stack),1);
    s->num = 0;
   while(1){
    if(strsame(p->wds[p->cw],"BEGIN") &&strsame(p->wds[p->cw+1],"{")){
        p->cw = p ->cw + 2;
        Instrclist(p,s);
        break;
    }
    p->cw = p ->cw + 1;
    
   }
    stack_free(s);
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

bool Isinstrc(prog* p)
{
    if(strsame(p->wds[p->cw],"PRINT")){
        return true;
    }
    else if(strsame(p->wds[p->cw],"ONES")){
        return true;
    }
    else if(strsame(p->wds[p->cw],"READ")){
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
    else if(strsame(p->wds[p->cw],"ONES")){
        Create(p,s);
    }
    else if(strsame(p->wds[p->cw],"READ")){
        Read(p,s);
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
    if(p->wds[p->cw][0] == '$'){
        Varname(p);
        int num = p->wds[p->cw][1] - 'A';
        int P_col = p->list[num].col;
        int P_row = p->list[num].row;
        for(int i = 0; i < P_row;i++){
            for(int j = 0; j < P_col;j++){
                printf("%d",p->list[num].arr[i][j]);
            }
            printf("\n");
        }
        p->cw = p ->cw + 1;
 
        
        
    }
    else if(p->wds[p->cw][0] == '"'){
        String(p);
        p->cw = p ->cw + 1;
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
    // printf("this is varname %s\n",p->wds[p->cw]);
    if(p->wds[p->cw][0] != '$'){
        ERROR("Should have $ sign");
    }
    int length = strlen(p->wds[p->cw]);
    if(length != 2 ){
        ERROR("One of the 26 possible variable between A to Z");
    }
    if(p->wds[p->cw][1] < 'A' || p->wds[p->cw][1] > 'Z' ){
        ERROR("Should between A to Z");
    }
    if(p->wds[p->cw][1] >= 'A' || p->wds[p->cw][1] <= 'Z'){
        return;
    }
    else{
        ERROR("Something wrong here!");
    }

}

void String(prog* p)
{
    // printf("this is string  %s\n",p->wds[p->cw]);
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
    return;
}

void Set(prog* p, stack* s)
{   
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
    if(p->wds[p->cw][0] == ';'){
        char var[SIZE];
        char tem[SIZE];
        stack_pop(tem,s);
        stack_pop(var,s);
        if(boolNum(tem)){
            int num = atoi(tem);
            int sequence = var[1] - 'A';
            p->list[sequence].arr[0][0] = num;
            p->list[sequence].row = 1;
            p->list[sequence].col = 1;
        }

        else{
            int sequence1 = ALPHABET;
            int sequence2 = var[1] - 'A';
            int col = p->list[sequence1].col;
            int row = p->list[sequence1].row;
            for(int i = 0 ;i < row; i ++){
                for(int j = 0; j < col;j++){
                    p->list[sequence2].arr[i][j] = p->list[sequence1].arr[i][j];
                }
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
    
    if((p->wds[p->cw][0] < 'A' || p->wds[p->cw][0] > 'Z') ||p->wds[p->cw][0] < '0' || p->wds[p->cw][0] > '9' ){
        
        Pushdown(p,s);
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
    else if(p->wds[p->cw][0] < 'A' || p->wds[p->cw][0] > 'Z'){
        Integer(p);
        stack_push(p->wds[p->cw],s);
    }
    
}

void Integer(prog* p)
{
    // printf("this is integer %s\n",p->wds[p->cw]);
    int length = strlen(p->wds[p->cw]);
    for(int i = 0; i < length; i ++){
        if(p->wds[p->cw][0] < '0' || p->wds[p->cw][0] > '9'){
            ERROR("Number should ne a non negative number");
        }
    }
}

void Unaryop(prog* p,stack* s)
{
    // printf("this is unaryop %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"U-NOT"))
    {
        U_NOT(p,s);
    }
    if(strsame(p->wds[p->cw],"U-EIGHTCOUNT"))
    {
        U_EIGHTCOUNT(p,s);
    }   
    if(!strsame(p->wds[p->cw],"U-EIGHTCOUNT") && !strsame(p->wds[p->cw],"U-NOT") ){
        ERROR("Something wrong with U-NOT AND U-EIGHTCOUNT");
    }
}

void Binaryop(prog* p, stack* s)
{
    
    // printf("this is brnaryop %s\n",p->wds[p->cw]);
    if(strsame(p->wds[p->cw],"B-AND")){
        B_AND(p,s);
    }
    else if(strsame(p->wds[p->cw],"B-OR")){
        B_OR(p,s);
    }
    else if(strsame(p->wds[p->cw],"B-GREATER")){
        B_GREATER(p,s);
    }
    else if(strsame(p->wds[p->cw],"B-LESS")){
        B_LESS(p,s);
    }
    else if(strsame(p->wds[p->cw],"B-ADD")){ // B-ADD  stack_pop(st2)  stack_pop(str1)    if(str1 && str2 都是数字){ %d + %d}
        B_ADD(p,s);                                    //else{ str1 or str2 isnumber? 假设str1是数字，那就将他的row，col跟str2相等。反之，str2是数字，将他的row，col跟str1相等    if(str1 && str2是否一个size)  for循环两次传值}
    }
    else if(strsame(p->wds[p->cw],"B-TIMES")){
        B_TIMES(p,s);
    }
    else if(strsame(p->wds[p->cw],"B-EQUALS")){
        B_EQUALS(p,s);
    }
    else{
        ERROR("Something wrong with B-AND or B-OR or B-GREATER or B-LESS or B-ADD or B-TIMES or B-EQUALS");
    }
}


void Create(prog* p,stack* s)
{
    // printf("this is create  %s\n",p->wds[p->cw]);
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
        int sequence = p->wds[p->cw][1] - 'A';
        for(int i = 0; i < m; i ++){
            for(int j = 0; j < n; j ++){
                p->list[sequence].arr[i][j] = 1;
            }
        }
        p->list[sequence].row = m;
        p->list[sequence].col = n;
        p->cw = p ->cw + 1;

    }
    else{
        ERROR("something wrong in ONES or READ");
    }

}
void Read(prog* p,stack* s)
{
    if(strsame(p->wds[p->cw],"READ")){
        p->cw = p ->cw + 1;
        String(p);
        char word[SIZE];
        strcpy(word,p->wds[p->cw]);
        int length = strlen(word);
        char f[SIZE];
        if(word[0] == '"' && word[length-1] == '"'){
            for(int i = 1; i < length -1; i ++){
                f[i-1] = word[i];
            }
        }
        f[length-2] = '\0';
        FILE* fp1 = fopen(f,"r");
        if(!fp1){
        fprintf(stderr,"cannot read from %s\n",f);
        exit(EXIT_FAILURE);
        }
        char tmp[SIZE] = "TMP";
        char tmp1[SIZE];
        int row;
        int col;
        int a[3];
        int scanf_row = 0;
        int count = 0;
        stack_push(tmp,s);
        while(fgets(tmp1, sizeof(tmp1),fp1)){ 
        if(scanf_row == 0){
            sscanf(&tmp1[0],"%d",&row);
            sscanf(&tmp1[2],"%d",&col);
        }
        else{
            count = 0;
            int length = strlen(tmp1)-1;
            for(int i = 0; i < length;i++){
                if(tmp1[i]!=' '){
                    sscanf(&tmp1[i],"%d",a);
                    p->list[ALPHABET].arr[scanf_row-1][count] = a[0];
                    count ++;
                }
            }
        }
        scanf_row++;
        }
        p->list[ALPHABET].row = row;
        p->list[ALPHABET].col = col;
        p->cw = p ->cw + 1;
        Varname(p);
        char str[SIZE];
        stack_pop(str, s);
        int b = p->wds[p->cw][1] - 'A';
        p->list[b].row = p->list[ALPHABET].row;
        p->list[b].col = p->list[ALPHABET].col;
        int row1;
        int col1;
        row1 = p->list[b].row;
        col1 = p->list[b].col;
        for(int i = 0; i < row1; i ++){
            for(int j = 0; j < col1; j ++){
                p->list[b].arr[i][j] = p->list[ALPHABET].arr[i][j];
            }
        }
        p->cw = p ->cw + 1;
        fclose(fp1);
        }
    else{
        ERROR("ERROR Something wrong with READ function\n");
    }
}


void Loop(prog* p,stack* s)
{
    Varname(p);
    stack_push(p->wds[p->cw],s);
    p->cw = p ->cw + 1;
    Integer(p);
    stack_push(p->wds[p->cw],s);
    p->cw = p ->cw + 1;
    if(strsame(p->wds[p->cw],"{")){
        char str1[SIZE];
        char str2[SIZE];
        int number;
        int b;//
        int count;
        stack_pop(str1, s);
        stack_pop(str2, s);
        if(boolNum(str1) && !boolNum(str2)){
            number = str2[1] - 'A';
            p->list[number].arr[0][0] = 1;
            p->list[number].row = 1;
            p->list[number].col = 1;
            p->cw = p ->cw + 1;
            int loop = p->cw;
            sscanf(str1,"%d",&b);
            count = p->list[number].arr[0][0];
            while(count < b){
                Instrclist(p,s);
                p->cw = loop;
                count ++;
                p->list[number].arr[0][0]++;
            }
            Instrclist(p,s);
        }
        else{
            ERROR("something wrong with loop function");
        }
        


        
    }
    
}

void U_NOT(prog* p,stack* s)
{
    char str1[SIZE];
    char tmp[SIZE] = "TMP";
    stack_pop(str1,s);
    if(boolNum(str1)){
        int a;
        sscanf(str1,"%d",&a);
        if(a == 0){
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].col = 1;
            p->list[ALPHABET].row = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].col = 1;
            p->list[ALPHABET].row = 1;
        }
        stack_push(tmp,s);
    }
    else{
        int a;
        a = str1[1] - 'A';
        int row = p->list[a].row;
        int col = p->list[a].col;
        for(int i = 0; i < row; i ++){
            for(int j = 0; j < col; j ++){
                if(p->list[a].arr[i][j] == 0){
                    p->list[ALPHABET].arr[i][j] = 1;
                }
                else{
                    p->list[ALPHABET].arr[i][j] = 0;
                }
            }
        }
        p->list[ALPHABET].col = p->list[a].col;
        p->list[ALPHABET].row = p->list[a].row;
        stack_push(tmp,s);
    }
        
}

void U_EIGHTCOUNT(prog* p,stack* s)
{
    char str1[SIZE];
    char tmp[SIZE] = "TMP";
    stack_pop(str1,s);
    if(boolNum(str1)){
        p->list[ALPHABET].arr[0][0] = 0;
        p->list[ALPHABET].row = 1;
        p->list[ALPHABET].col = 1;
        stack_push(tmp,s);
    }
    else{
        
        int a;
        a = str1[1] - 'A';
        int row = p->list[a].row;
        int col = p->list[a].col;
        for(int i = 0; i < row; i ++){
            for(int j = 0; j < col; j ++){
                int count = 0;
                count = p->list[a].arr[(i - 1 + row) % row][j]+ p->list[a].arr[(i + 1 + row) % row][j] + p->list[a].arr[i][(j - 1 + col) % col] + \
                        p->list[a].arr[i][(j + 1 + col ) % col] + p->list[a].arr[(i + 1 + row)% row][(j+1+col)%col] + p->list[a].arr[(i - 1 + row)% row][(j+1+col)%col] + \
                        p->list[a].arr[(i + 1 + row)% row][(j-1+col)%col]+ p->list[a].arr[(i - 1 + row)% row][(j-1+col)%col];
                p->list[ALPHABET].arr[i][j] = count;
            }
        }
        p->list[ALPHABET].col = p->list[a].col;
        p->list[ALPHABET].row = p->list[a].row;
        stack_push(tmp,s);
    }
}

void B_AND(prog* p,stack* s)
{
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
        if(a<b)
        {
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int row = p->list[a].row;
            int col = p->list[a].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    if(p->list[a].arr[i][j]>0 && p->list[b].arr[i][j]>0){
                        p->list[ALPHABET].arr[i][j] = 1;
                    }
                    else{
                        p->list[ALPHABET].arr[i][j] = 0;
                    }
                }
            }
            p->list[ALPHABET].col = p->list[a].col;
            p->list[ALPHABET].row = p->list[a].row;
            stack_push(tmp,s);
        }

    }
    return;
}

void B_OR(prog* p,stack* s)
{
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
        if(a>0 || b>0){
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int row = p->list[b].row;
            int col = p->list[b].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    if(p->list[b].arr[i][j]>0 || p->list[a].arr[i][j]>0){
                        p->list[ALPHABET+1].arr[i][j] = 1;
                    }
                    else{
                        p->list[ALPHABET+1].arr[i][j] = 0;
                    }
                }
            }

            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    p->list[ALPHABET].arr[i][j] = p->list[ALPHABET+1].arr[i][j];
                }
            }

            p->list[ALPHABET].col = p->list[b].col;
            p->list[ALPHABET].row = p->list[b].row;




            stack_push(tmp,s);
        }

    }
    return;
}

void B_GREATER(prog* p,stack* s)
{
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
        if(a<b)
        {
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int row = p->list[a].row;
            int col = p->list[a].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    if(p->list[a].arr[i][j]>p->list[b].arr[i][j]){
                        p->list[ALPHABET].arr[i][j] = 1;
                    }
                    else{
                        p->list[ALPHABET].arr[i][j] = 0;
                    }
                }
            }
            p->list[ALPHABET].col = p->list[a].col;
            p->list[ALPHABET].row = p->list[a].row;
            stack_push(tmp,s);
        }

    }
    return;
}


void B_LESS(prog* p,stack* s)
{
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
        if(a<b)
        {
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int row = p->list[a].row;
            int col = p->list[a].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    if(p->list[a].arr[i][j]<p->list[b].arr[i][j]){
                        p->list[ALPHABET].arr[i][j] = 1;
                    }
                    else{
                        p->list[ALPHABET].arr[i][j] = 0;
                    }
                }
            }
            p->list[ALPHABET].col = p->list[a].col;
            p->list[ALPHABET].row = p->list[a].row;
            stack_push(tmp,s);
        }

    }
    return;
}



void B_ADD(prog* p, stack* s)
{
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
            p->list[ALPHABET].arr[0][0] = a + b;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
            stack_push(tmp,s);
        }
        else{
            
            arr(p,str2, str1);
            int a;
            int b;
            if(boolNum(str1))
            {
               a = ALPHABET+1;
               b = str2[1] - 'A';
            }
            else if(boolNum(str2))
            {
               a = ALPHABET+1;
               b = str1[1] - 'A';
            }
            else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
            if(Check_row_and_col(p,a,b)){
                int m;
                int n;
                int row = p->list[a].row;
                int col = p->list[a].col;
                for(int i = 0; i < row; i ++){
                    for(int j = 0; j < col; j ++){
                        m = p->list[a].arr[i][j];
                        n = p->list[b].arr[i][j];
                        p->list[ALPHABET].arr[i][j] = m + n;
                    }
                }
                p->list[ALPHABET].col = p->list[a].col;
                p->list[ALPHABET].row = p->list[a].row;
                stack_push(tmp,s);
            }
        }
        return;
}

void B_TIMES(prog* p,stack* s)
{
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
        p->list[ALPHABET].arr[0][0] = a * b;
        p->list[ALPHABET].row = 1;
        p->list[ALPHABET].col = 1;
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int m;
            int n;
            int row = p->list[b].row;
            int col = p->list[b].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    m = p->list[b].arr[i][j];
                    n = p->list[a].arr[i][j];
                    p->list[ALPHABET].arr[i][j] = m*n;
                }
            }
            p->list[ALPHABET].col = p->list[b].col;
            p->list[ALPHABET].row = p->list[b].row;
            stack_push(tmp,s);
        }

    }
    return;
}


void B_EQUALS(prog* p,stack* s)
{
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
        if(a == b){
            p->list[ALPHABET].arr[0][0] = 1;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        else{
            p->list[ALPHABET].arr[0][0] = 0;
            p->list[ALPHABET].row = 1;
            p->list[ALPHABET].col = 1;
        }
        stack_push(tmp,s);
    }
    else{ 
        arr(p,str2, str1);
        int a;
        int b;
        if(boolNum(str1)){
            a = ALPHABET+1;
            b = str2[1] - 'A';
        }
        else if(boolNum(str2)){
            a = ALPHABET+1;
            b = str1[1] - 'A';
        }
        else{
            if(strsame(str1,"TMP")){
                a = ALPHABET;
                b = str2[1]-'A';
            }
            else if(strsame(str2,"TMP")){
                a = str1[1]-'A';
                b = ALPHABET;
            }
            else{
                a = str1[1]-'A';
                b = str2[1]-'A';
            }
            
        }
        if(Check_row_and_col(p,a,b)){
            int row = p->list[a].row;
            int col = p->list[a].col;
            for(int i = 0; i < row; i ++){
                for(int j = 0; j < col; j ++){
                    if(p->list[a].arr[i][j] == p->list[b].arr[i][j]){
                        p->list[ALPHABET].arr[i][j] = 1;
                    }
                    else{
                        p->list[ALPHABET].arr[i][j] = 0;
                    }
                }
            }
            p->list[ALPHABET].col = p->list[b].col;
            p->list[ALPHABET].row = p->list[b].row;
            stack_push(tmp,s);
        }
    }
    return;
}



void arr(prog* p, char* str2, char* str1)
{
    if(boolNum(str2)){
        int a;
        sscanf(str2,"%d",&a);
        int sequence = str1[1] - 'A';
        p->list[ALPHABET+1].col = p->list[sequence].col;
        p->list[ALPHABET+1].row = p->list[sequence].row;
        for(int i = 0; i < p->list[sequence].row; i ++){
            for(int j = 0; j < p->list[sequence].col; j ++){
                p->list[ALPHABET+1].arr[i][j] = a;
            }
        }
    }

    if(boolNum(str1)){
        int a;
        sscanf(str1,"%d",&a);
        int sequence = str2[1] - 'A';
        p->list[ALPHABET+1].col = p->list[sequence].col;
        p->list[ALPHABET+1].row = p->list[sequence].row;
        for(int i = 0; i < p->list[sequence].row; i ++){
            for(int j = 0; j < p->list[sequence].col; j ++){
                p->list[ALPHABET+1].arr[i][j] = a;
            }
        }
    }
    

}


bool Check_row_and_col(prog* p, int a, int b)
{
    if(p->list[a].row == p->list[b].row){
        if(p->list[a].col == p->list[b].col){
            return true;
        }
    }

    return false;
}

void stack_push(char* p,stack* s)
{
    if(s){
        node* f = (node*)ncalloc(1,sizeof(node));
        strcpy(f->c,p);
        f->next = s ->top;
        s->top = f;
        s->num = s->num+1;
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


bool stack_free(stack* s)
{
    if(s){
        node* p = s->top;
        while(p!=NULL){
            node* tmp = p->next;
            free(p);
            p = tmp;
        }
        free(s);
    } 
    return true; 
}



