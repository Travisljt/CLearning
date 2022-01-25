#include<stdio.h>
#include<string.h>
#define SWAP(A,B) {char tem = *A; *A=*B; *B = tem;}

void permute(char* a,int s,int e);

int main()
{
    char str[]="ABC";
    int n = strlen(str);
    permute(str,0,n-1);
    return 0;
}


void permute(char* a,int s,int e)
{
    if(s==e){
        printf("%s\n",a);
        return;

    }
    for(int i =s; i<=e;i++){
        SWAP((a+s),(a+1));
        permute(a,s+1,e);
        SWAP((a+s),(a+i));
    }
}
