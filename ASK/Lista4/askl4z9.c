#include <stdio.h>
#include <stdint.h>

extern int64_t adds(int64_t x, int64_t y);

int main(){
  int64_t x, y;
  x = 345345354378;
  y = 0x7FFFFFFFFFFFFFFF;
  printf("%ld\n", adds(x, y));
  return 0;
}
