#include <stdio.h>
#include <string.h>
#include <stdint.h>

const char *int64_to_binary(uint64_t x)
{
    static char b[65];
    b[0] = '\0';

    uint64_t z;
    for (z = 0x8000000000000000; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

extern uint64_t convert(uint64_t a);

int main(){
  uint64_t a = 0xFA89000000000094;
  printf("%s\n", int64_to_binary(a));
  a = convert(a);
  printf("%s\n", int64_to_binary(a));
  return 0;
}
