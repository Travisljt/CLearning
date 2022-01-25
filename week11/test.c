#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    char s[10]="abd";
    if(strcmp(s,"abd")==0)
    {
        printf("test ok\n");
    }
    return 0;
}