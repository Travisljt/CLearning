#include <stdio.h>
#include <string.h>

/* Copy the letters 'Office' into string 'strd' */
int main() {
  char strs[] = "Office-24423";
  char strd[6];
  strncpy(strd, strs, 6);
  printf("strd is %s\n",strd);
  return 0;
}
