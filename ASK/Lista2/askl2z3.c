#include "stdio.h"

int check(int a, int b){
  int s = a + b;
  return ((~(a^b)&(a^s))>>31)&1;
}

int main(){
  int a, b;
  a = -1;
  b = 2;
  printf("%d\n", check(a,b));
  return 0;
}
