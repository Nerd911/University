#include "stdint.h"
#include "stdio.h"
/* Oblicz x * 3 / 4 zaokrąglając w dół. */
int32_t threefourths(int32_t x){
  return (x>>1)+((x+1)>>2);
}

int main(){
  int32_t x = -3;
  printf("%d\n", threefourths(x));
  return 0;
}
