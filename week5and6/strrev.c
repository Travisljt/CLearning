#include<stdio.h>
#include<string.h>
#define SWAP(A,B) {char tem; tem = A; A=B; B = tem;}

void strrev(char* s,int start,int end);

int main(void)
{
    char str[]="Hello world!";
    strrev(str,0,strlen(str)-1);
    printf("%s\n",str);
    return 0;
}

void strrev(char* s, int start,int end)
{
    printf("first-%i\n",start);
    if(start>=end){
        return;
    }
    SWAP(s[start],s[end]);
    strrev(s,start+1,end-1);
    printf("second-%i\n",start);

}

