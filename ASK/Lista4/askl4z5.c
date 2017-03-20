int decode2(int x, int y, int z) {
  int n = y - z; // 2-3
  int m = (n << 31) >> 31; // 4-6
  return (n * x) ^ m; // 7-8
}
