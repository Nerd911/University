#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

int main(){
  int x = 12344566;
  const char* bin = byte_to_binary(x);

  printf("%s\n", bin);
  x = (x & 0x55555555) + ((x >>  1) & 0x55555555);
  x = (x & 0x33333333) + ((x >>  2) & 0x33333333);
  x = (x & 0x0F0F0F0F) + ((x >>  4) & 0x0F0F0F0F);
  x = (x & 0x00FF00FF) + ((x >>  8) & 0x00FF00FF);
  x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
  printf("%d\n", x);
  return 0;
}
