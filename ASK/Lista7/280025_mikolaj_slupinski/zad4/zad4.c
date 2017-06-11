#include "stdio.h"
#include "stdlib.h"
unsigned long fibonacci(unsigned long);
int main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  unsigned long ul = strtoul(argv[1], NULL, 0);

  printf("%lu\n", fibonacci(ul));
  return 0;
}
