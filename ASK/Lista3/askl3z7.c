#include "stdio.h"
#include "stdint.h"
#include "string.h"


//Porównywanie ze i bez znaku, patrz, lista 2 zad 6
int32_t comp(int32_t x, int32_t y){
  //return ((x-y)^((x^y)&((x-y)^x)))>>31 & 0x00000001;
  return ((x&(~y))|(~(x^y) & (x-y)))>>31 & 0x00000001; //oba poprawne
}

int32_t compu(uint32_t x, uint32_t y){
  return ((~x&y)|(~(x^y)&(x-y)))>>31 & 0x00000001;
}

int32_t floatbits(float f){
  int32_t result;
  memcpy(&result, &f, sizeof(result));
  return result;
}

float bitsfloat(int32_t f){
  float result;
  memcpy(&result, &f, sizeof(result));
  return result;
}

int32_t flipSign(int32_t x){
  x = x ^ 0x80000000; //zmiana znaku
  return x;
}

int32_t eq(int32_t x, int32_t y){
  return (x==y)|((x|y) == 0x80000000); //x == y
}

int32_t compf(int32_t x, int32_t y){
  return eq(x, y) | ~(x>>31)&comp(x,y) | (x>>31)&compu(y,x);
}

int32_t log2(int32_t x){
  return (((x & 0x7F800000) >> 23) - 127);
}
int main(){
  float x, y;
  x = -2.0;
  y = 10.0;

  int32_t ix, iy;
  ix = floatbits(x);
  iy = floatbits(y);

  printf("%f\n", bitsfloat(flipSign(ix)));
  printf("%d\n", eq(ix, iy));
  printf("%d\n", compf(ix, iy));
  printf("%f\n", log2(ix));

}
