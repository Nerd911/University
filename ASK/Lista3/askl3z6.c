#include "stdio.h"
#include "stdint.h"
#include "string.h"

int32_t floatbits(float f){
  int32_t result;
  memcpy(&result, &f, sizeof(result));
  return result;
}

int32_t power(int32_t f, int32_t i){
  //da sie to zrobic w jednym ifie, chciałem, żeby było widać czemu to odrzucamy
  if(!(f & 0x7F800000)) //denormalized
    return f;
  if(f == 0x7F800000) // infinity
    return f;
  if((f & 0x7F800000) == 0x7F800000)//NaN
    return f;
  if(!(f & 0xFF800000)) //negative denormalized
    return f;
  if(f == 0xFF800000) //negative infinity
    return f;
  if((f & 0xFF800000) == 0xFF800000)//NaN
    return f;
  int temp_e = ((f & 0x7F800000) << i) & 0x7F800000;
  return (f & ~0x7F800000) | temp_e;
}
int main(){

}
