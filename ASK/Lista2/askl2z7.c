#include "stdio.h"

int bitabs(int x){
  int mask = x >> 31;
  return (mask^x) - mask;
}
int main(){
  int x = 0x80000001;
  printf("%d\n", x);
  printf("%d\n", bitabs(x));
  return 0;
}
