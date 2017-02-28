void secret(uint8_t *to, uint8_t *from, size_t count) {
  size_t n = (count + 7) / 8;
  switch (count % 8) {
  case 0: do { *to++ = *from++;
  case 7:      *to++ = *from++;
  case 6:      *to++ = *from++;
  case 5:      *to++ = *from++;
  case 4:      *to++ = *from++;
  case 3:      *to++ = *from++;
  case 2:      *to++ = *from++;
  case 1:      *to++ = *from++;
            } while (--n > 0);
  }
}


void secret1(uint8_t *to, uint8_t *from, size_t count) {
  size_t n = (count + 7) / 8;
  void* arr[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
  goto arr[count%8];
  c0:
    *to++ = *from++;
  c7:
    *to++ = *from++;
  c6:
    *to++ = *from++;
  c5:
    *to++ = *from++;
  c4:
    *to++ = *from++;
  c3:
    *to++ = *from++;
  c2:
    *to++ = *from++;
  c1:
    *to++ = *from++;
  if(--n > 0) goto c0;
  }
}
