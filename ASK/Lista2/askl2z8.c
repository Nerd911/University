#include "stdio.h"

int sign(int x){
  int mask = x >> 31;
  return mask|(x != 0);
}
int main(){
  int x = -3;
  printf("%d\n", x);
  printf("%d\n", sign(x));
  return 0;
}
