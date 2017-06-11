#include "stdio.h"
#include "stdlib.h"
extern double approx_sqrt(double, double);
int main(int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr, "Za mało argumentów\n");
    return -1;
  }
  double d, eps;
  d = atof(argv[1]);
  eps = atof(argv[2]);

  printf("%f\n", approx_sqrt(d, eps));
  return 0;
}
