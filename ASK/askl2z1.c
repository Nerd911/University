#include "stdio.h"
#include "stdint.h"

int main(){
  int32_t x, y;
  int res;

  x = 0x80000000;
  res = (x > 0) || (x - 1 < 0);
  printf("%d\n", res);

  x = 0x0000000F;
  res = (x & 7) != 7 || (x << 29 < 0);
  printf("%d\n", res);

  x = 0x0FFFFFFF;
  res = (x * x) >= 0;
  printf("%d\n", res);

  res = x < 0 || -x <= 0;
  printf("%d\n", res);

  x = 0x80000000;
  res = x > 0 || -x >= 0;
  printf("%d\n", res);

  res = x + y == (uint32_t)y + (uint32_t)x;
  printf("%d\n", res);

  res = x * ~y + (uint32_t)y * (uint32_t)x == -x;
  printf("%d\n", res);

  return 0;
}
