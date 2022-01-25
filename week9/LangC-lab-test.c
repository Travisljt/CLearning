/*
   Returns a Boolean, depending upon whether the
   string s1 is composed entirely from characters that
   occur in s2 or not.
*/

// #include "common.h"

// bool struses(const char* s1, const char* s2);

// int main(void)
// {
//    /* What words can you make using only the
//       Top line of a traditional qwerty keyboard ?*/

//    struses("perpetuity", "qwertyuiop");
//    assert(struses("perpetuity", "qwertyuiop"));
//    assert(struses("PERPETUITY", "QWERTYUIOP"));
//    assert(struses("typewriter", "qwertyuiop"));
//    assert(struses("", "qwertyuiop"));

//    assert(!struses("printers", "qwertyuiop"));
//    assert(!struses("typist", "qwertyuiop"));
//    assert(!struses("typist", "qwertyuiop"));

//    /* Middle Line */
//    assert(struses("alfalfas", "asdfghjkl"));
//    assert(struses("galahads", "asdfghjkl"));

//    assert(!struses("goldilocks", "asdfghjkl"));
//    assert(!struses("darkness", "asdfghjkl"));

//    assert(!struses("sdm,nc,ncd|SDFKSKO$$W", ""));

//    return 0;
// }

// bool struses(const char* s1, const char* s2){
//    int str_one = strlen(s1);
//    int str_two = strlen(s2);

//    if(str_two == 0){
//       return false;
//    }

//    for(int j = 0; j < str_one; j++){
//       int wrong_no = 0;

//       for(int i = 0; i < str_two; i++){
//          if(s1[j] != s2[i]){
//             wrong_no++;
//          }
//          if(wrong_no == str_two){
//             return false;
//          }
//       }
//    }

//    return true;
// }

/*
   Returns a copy of string s1 with all of the duplicate
   characters removed.
*/

// #include "common.h"

// #define STRLENGTH 256

// char* strnodupes(const char* s);

// int main(void)
// {
//    char* s2;

//    s2 = strnodupes("Hello World!");
//    assert(strcmp("Helo Wrd!", s2)==0);
//    free(s2);
//    s2 = strnodupes("a-aaaaaAAAAAAAAaaaaaaaa");
//    assert(strcmp("a-A", s2)==0);
//    free(s2);
//    s2 = strnodupes("HHiHHiiidiHiHiedHidiHi");
//    assert(strcmp("Hide", s2)==0);
//    free(s2);
//    s2 = strnodupes("Subdermatoglyphic");
//    assert(strcmp("Subdermatoglyphic", s2)==0);
//    free(s2);

//    return 0;
// }

// char* strnodupes(const char* s){
//    int str_no = strlen(s);
//    static char* modify_str;

//    modify_str = (char *)malloc(sizeof(char)*50);

//    modify_str[0] = s[0];

//    int k = 1;
//    for(int j = 0; j < str_no; j++){
//       int diff_times = 0;
//       for(int i = 0; i < k; i++){
//          if(s[j] != modify_str[i]){
//             diff_times++;
//          }
//       }
//       if(diff_times == k){
//          modify_str[k] = s[j];
//          k++;
//       }
//    }
//    modify_str[k] = '\0';

//    return modify_str;
// }

/* 
   Return the count of numbers in the array l (of size n)
   which are unique (i.e. duplicates are not counted)
*/

// #include "common.h"

// #define ARRLENGTH 50

// int numdiff(const int l[], const int n);

// int main(void)
// {
//    int l[] = {100484783, 2, 30, -999999999, 3, 222222, -89492981, 1, 456889009};
//    int m[] = {-567, 4, 99999, 0, 4, 4};

//    assert(numdiff(l, 9)==9);
//    assert(numdiff(m, 6)==4);
//    assert(numdiff(m, 5)==4);
//    assert(numdiff(m, 3)==3);
//    assert(numdiff(NULL, 0)==0);
//    return 0;
// }

// int numdiff(const int l[], const int n){
//    if(l == NULL){
//       return 0;
//    }

//    int copied_array[n];
//    int new_array[ARRLENGTH];
   
//    for(int i = 0; i < n; i++){
//       copied_array[i] = l[i];
//    }

//    new_array[0] = copied_array[0];

//    int k = 1;
//    int num_unique = 1;

//    for(int j = 1; j < n; j++){
//       int diff_times = 0;

//       for(int i = 0; i < k; i++){
//          if(copied_array[i] != copied_array[k]){
//             diff_times++;
//          }
//          if(diff_times == k){
//             new_array[k] = copied_array[k];
//             num_unique++;
//          }
//       }
//       k++;
//    }

//    return num_unique;
// }

/*
   Return which number in the array l (of size n) is numerically closest
   to the average (mean) of all the numbers. In the case of a tie (i.e.
   1 or more of them are equally distant from the average) then the first
   such number in the list is returned.
*/

#include "common.h"

int closestmean(const int l[], const int n);

int main(void)
{
   int l[] = {10, 20, 30, 40};
   int m[] = {-5, 0, 10, -10, 5};
   int r[] = {10000000, 20000000, 0, -50000000};
   int t[] = {-5, 5};

   closestmean(l, 4);
   assert(closestmean(l, 4)==20);
   assert(closestmean(m, 5)==0);
   assert(closestmean(l, 1)==10);
   assert(closestmean(r, 4)==0);
   assert(closestmean(t, 2)==-5);
   assert(closestmean(&l[1], 3)==30);
   return 0;
}

int closestmean(const int l[], const int n){
   int copied_array[n];
   int average;
   int sum = 0;
   int closest, distance;

   for(int i = 0; i < n; i++){
      copied_array[i] = l[i];
   }

   for(int i = 0; i < n; i++){
      sum = sum + copied_array[i];
   }
   average = sum / n;

   distance = abs(copied_array[0] - average);
   closest = copied_array[0];

   if(n == 1){
      return closest;
   }

   for(int i = 1; i < n; i++){
      if(distance > abs(copied_array[i] - average)){
         distance = abs(copied_array[i] - average);
         closest = copied_array[i];
      }

   }

   return closest;
}
