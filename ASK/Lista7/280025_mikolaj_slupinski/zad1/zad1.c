#include "stdio.h"
#include "stdlib.h"

extern int clz(long);

int main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  long l;
  l = atol(argv[1]);
  printf("%d\n", clz(l));
  return 0;
}
