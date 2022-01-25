#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

void strmerge(const char* s1, const char* s2, char*s3);
unsigned nstrlen(const char s[]);

#define LARGESTRING 1000

int main(void)
{
    char s[LARGESTRING];
    strmerge("Hello World!", "World! & Everyone.", s);
    assert(strcmp(s, "Hello World! & Everyone.")==0);

    strmerge("The cat sat", "sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("The cat sat on the mat", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("One ", "Two", s);
    assert(strcmp(s, "One Two")==0);

    strmerge("", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("The cat sat on the mat.", "", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("123412341234", "1234", s);
    assert(strcmp(s, "123412341234")==0);
        
    return 0;
}

void strmerge(const char* s1, const char* s2, char*s3){
    int number1, number2;
    int times1 = 0;
    int times2 = 0;
    char first1[100], first2[100], first3[100], first4[100], first5[100];
    char second1[100], second2[100], second3[100], second4[100], second5[100];

    number1 = nstrlen(s1);
    number2 = nstrlen(s2);

    for(int i = 0; i <= number1; i++){
        if(s1[i] == 32){
            times1++;
        }
    }
    for(int i = 0; i <= number2; i++){
        if(s2[i] == 32){
            times2++;
        }
    }

    if(times1 == 0 && times2 != 0){
        strcat(s3, s1);
        strcat(s3, s2);
        return;
    }else if (times1 != 0 && times2 == 0){
        strcat(s3, s1);
        strcat(s3, s2);
        return;
    }

    if(times1 == 1 && times2 == 2){
        sscanf(s1, "%s %s", first1, first2);
        sscanf(s2, "%s %s %s", second1, second2, second3);

        if(strncmp(first2, second1, 2) == 0){
            strcat(s3, first1);
            strcat(s3, " ");
            strcat(s3, s2);
        }
    }
}

unsigned nstrlen(const char s[]){
    register unsigned n = 0;
    while(s[n] != '\0'){
        ++n;
    }
    return n;
}