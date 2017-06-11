#include "stdio.h"
#include "stdint.h"

int32_t comp(int32_t x, int32_t y){
  //return ((x-y)^((x^y)&((x-y)^x)))>>31 & 0x00000001;
  return ((x&(~y))|(~(x^y) & (x-y)))>>31 & 0x00000001; //oba poprawne
}

int32_t compu(uint32_t x, uint32_t y){
  return ((~x&y)|(~(x^y)&(x-y)))>>31 & 0x00000001;
}

int main(){
  int32_t a, b;
  uint32_t ua, ub;
  a = 5;
  b = 5;
  ua = 45;
  ub = 4;


  printf("%d\n", comp(a, b));
  printf("%d\n", compu(ua, ub));

  return 0;

}
