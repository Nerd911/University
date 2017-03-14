#include "stdio.h"
#include "stdint.h"

//2^23
#define FRAC 0x4B000000

int32_t float2int(int32_t f){
  if(f >= 0)
    return (f + FRAC) - FRAC;
  return FRAC - (FRAC - f);
}
int main(){
  float f = 32.9;

  int32_t i = float2int(f);
  printf("%d\n", i);
  return 0;
}
