#include "stdio.h"
#include "string.h"
int even(int x){
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return (~x) & 1;
}

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
  int x = 14;
  printf("%s\n", byte_to_binary(x));
  printf("%d\n", even(x));
  return 0;
}
