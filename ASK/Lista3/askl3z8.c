#include "stdio.h"
#include "stdint.h"
#include "string.h"

//2^23
#define FRAC 0x4B000000

const char *byte_to_binary(int x)
{
    static char b[33];
    b[0] = '\0';

    unsigned int z;
    for (z = 0x80000000; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int32_t floatbits(float f){
  int32_t result;
  memcpy(&result, &f, sizeof(result));
  return result;
}
int32_t float2int(int32_t f){
  //0111 1111 1000 0000
  //C stroi fochy
  int s = 0x00000001 | (f>>31);
  int e = (((f & 0x7F800000) >> 23) - 127);
  int m = ((f&0x007FFFFF) << (e-1));

  printf("%d\n", m);
   return s*((1 << e)+m);

}
int main(){
  float f = 3;

  int32_t i = float2int(floatbits(f));
  printf("%s\n", byte_to_binary(floatbits(f)));
  printf("%d\n", i);
  return 0;
}
