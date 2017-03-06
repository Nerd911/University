#include "stdint.h"
#include "stdio.h"
/* Oblicz x * 3 / 4 zaokrąglając w dół. */
//do poprawy
int32_t threefourths(int32_t x){
  return (x>>1)+(x>>2) + (x&3 == 3);
}

int main(){
  int32_t x = -3;
  printf("%d\n", x);
  printf("%d\n", threefourths(x));
  return 0;
}
