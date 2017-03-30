typedef struct A {
  long u[2];
  long *v;
} SA;

typedef struct B {
  long p[2];
  long q;
} SB;


SB eval(SA s){
  SB res;
  long rcx, *rdx;
  long rsi;
  rcx = &s.u[1];
  rdx = &s.v;
  rsi = *rdx;
  rdx = rcx;
  rdx = rdx * rcx;

  return res;
}

SB eval(SA s){
  SB res;
  res.p[0] = s.u[1] * *s.v;
  res.p[1] = s.u[0] - *s.v;
  res.q = s.u[0] - s.u[1]
  return res;
}

long wrap(long x, long y, long z){
  
}
