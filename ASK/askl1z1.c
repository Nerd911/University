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
  int x = 1234456600;
  int i = 1;
  int j = 5;

  printf("%s\n", byte_to_binary(x));
  x = (((x >> (31 - i)) & 1) << (31 - j)) ^ x;
  printf("%s\n", byte_to_binary(x));
  return 0;
}
