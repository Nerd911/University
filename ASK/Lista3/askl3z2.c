#include "stdio.h"
#include "stdint.h"
#include "limits.h"

int32_t div3(int32_t n){
  int64_t res = n + (n!=INT_MAX);
  res *= 0x0000000055555555;
  printf("%ld\n", res);
  return res >> 32;
}

int main(){
  printf("%d\n", div3(-4));
  return 0;
}