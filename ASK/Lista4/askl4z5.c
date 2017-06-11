int decode2(long long x, long long y, lobg long z) {
  int n = y - z; // 2-3
  int m = (n << 63) >> 63; // 4-6
  return (n * x) ^ m; // 7-8
}
