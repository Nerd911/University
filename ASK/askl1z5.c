struct A {
  int8_t a; /*2 bytes*/
  /*2 bytes padding*/
  void *b; /*4 bytes*/
  int8_t c; /*1 byte*/
  /*1 byte padding*/
  int16_t d; /*2 bytes*/
};

struct A us[];
struct A *vs;
vs->d = us[1].a + us[j].c;

store_I8((void*)vs + 4, )
(void*)vs
