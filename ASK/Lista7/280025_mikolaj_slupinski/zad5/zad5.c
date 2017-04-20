#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern unsigned mulf(unsigned, unsigned);

int main(int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  float f0, f1, f;
  f0 = atof(argv[1]);
  f1 = atof(argv[2]);
  unsigned u0, u1, u;
  memcpy(&u0, &f0, 4);
  memcpy(&u1, &f1, 4);
  u = mulf(u0, u1);
  memcpy(&f, &u, 4);
  printf("%f\n", f);


  return 0;
}
