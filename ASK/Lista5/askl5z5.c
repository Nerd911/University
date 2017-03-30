#define CNT 7


typedef struct {
  int first;
  a_struct a[CNT];
  int last;
} b_struct;

void test (long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}


/*
c
typedef struct { // 40B
    long idx;  // 8B
    long x[4]; // 32 = 4 * 8B
} a_struct;

n    = *(bp + 288) + *bp
rax  = bp + 40i
rdx  = *(bp + 8 + 40i) // bp->a[i] => 40B a_struct AND idx poczatek
*(rax + 8 + 8 * rdx + 8) = n // *(ap + 8 * idx + 8) = n
*/
