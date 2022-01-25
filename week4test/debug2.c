#include <stdio.h>

/* Prints out the string set */
int main(){
  int i = 0;
  char *StringSet[] = {
      "string1 1 0 2 0",
      "string2 1 2 0 5 9",
      "string3 0 9 2",
      ""
  };

  while(StringSet[i] != NULL){
    printf("String %s\n",StringSet[i]);
    i++;
  }

  return 0;
}
