#include "stdint.h"
#include "stdio.h"
/* Oblicz x * 3 / 4 zaokrąglając w dół. */
//poprawne
int32_t threefourths(int32_t x){
  int32_t y = x >> 2; // podziel przez 4
  y = (y << 1) + y;   // pomnóż przez 3, bez overflow
  int32_t z = x & 3;  // bity, których się pozbyliśmy
  z = (z << 1) + z;   // pomnóż przez 3, nadal bez przepełnienia
  return (y + (z >> 2)); // the two pieces
}

int main(){
  int32_t x = -7;
  printf("%d\n", x);
  printf("%d\n", threefourths(x));
  return 0;
}
