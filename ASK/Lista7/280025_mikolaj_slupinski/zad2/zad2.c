#include "stdio.h"
#include "stdlib.h"

typedef struct {
unsigned long lcm, gcd;
} result_t;

extern result_t lcm_gcd(unsigned long a, unsigned long b);

int main(int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  result_t r;
  unsigned long l1, l2;
  l1 = strtoul(argv[1], NULL, 0);
  l2 = strtoul(argv[2], NULL, 0);

  r = lcm_gcd(l1, l2);
  printf("lcm: %lu gcd: %lu\n", r.lcm, r.gcd);
  return 0;
}
