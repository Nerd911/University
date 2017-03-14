#include "stdio.h"
#include "stdint.h"
#include "string.h"

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
/*
int32_t float2int(int32_t f){
  //to dziala
  int s = 0x00000001 | (f>>31);
  int e = (((f & 0x7F800000) >> 23) - 127);
  int m = ((f & 0x007FFFFF) >>(23-e));
  return s*((1 << e)+m);

}
*/

int32_t float2int(int32_t f){
  //to o dziwo też
  int s = (f>>31);
  int e = (((f & 0x7F800000) >> 23) - 127);
  int m = ((f & 0x007FFFFF) >>(23-e));
  int res = (1 << e)+m;
  return (s^res) - s;
}

int main(){
  float f = -23.5;

  int32_t i = float2int(floatbits(f));
  printf("%s\n", byte_to_binary(floatbits(f)));
  printf("%d\n", i);
  return 0;
}
