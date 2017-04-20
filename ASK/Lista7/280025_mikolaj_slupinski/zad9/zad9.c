#include "stdlib.h"
#include "stdio.h"
long adds(long x, long y){
  long res;
  asm("movq %1, %0;"
  "addq %2, %0;"
  "movq %1, %%rbx;"
  "sarq $63, %%rbx;"
  "movq %2, %%rdx;"
  "sarq $63, %%rdx;"
  "andq %%rdx, %%rbx;"
  "movq %0, %%rdx;"
  "notq %%rdx;"
  "sarq $63, %%rdx;"
  "andq %%rdx, %%rbx;"
  "movq $0x8000000000000000, %%rdx;"
  "andq %%rbx, %%rdx;"
  "notq %%rbx;"
  "andq %%rbx, %0;"
  "orq %%rdx, %0;"
  "movq %1, %%rbx;"
  "notq %%rbx;"
  "sarq $63, %%rbx;"
  "movq %2, %%rdx;"
  "notq %%rdx;"
  "sarq $63, %%rdx;"
  "andq %%rdx, %%rbx;"
  "movq %0, %%rdx;"
  "sarq $63, %%rdx;"
  "andq %%rdx, %%rbx;"
  "movq $0x7FFFFFFFFFFFFFFF, %%rdx;"
  "andq %%rbx, %%rdx;"
  "notq %%rbx;"
  "andq %%rbx, %0;"
  "orq %%rdx, %0;" : "=r"(res) : "r"(x), "r"(y) : "rdx", "rbx", "cc");
  return res;
}

int main(int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  long l0, l1;
  l0 = atol(argv[1]);
  l1 = atol(argv[2]);
  printf("%ld\n", adds(l0, l1));
  return 0;
}
