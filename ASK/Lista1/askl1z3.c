struct A {
  int8_t a; /*2 bytes*/
  /*2 bytes padding*/
  void *b; /*4 bytes*/
  int8_t c; /*1 byte*/
  /*1 byte padding*/
  int16_t d; /*2 bytes*/
};

struct B {
uint16_t a; /*2 bytes*/
/*2 bytes padding*/
double b; /*8 bytes*/
void *c; /*4 bytes*/
};

struct A1 {
  void *b; /*4 bytes*/
  int8_t a; /*2 bytes*/
  int16_t d; /*2 bytes*/
  int8_t c; /*1 byte*/
  /*3 bytes padding*/
};

struct B1 {
  double b; /*8 bytes*/
  void *c; /*4 bytes*/
  uint16_t a; /*2 bytes*/
  /*2 bytes padding*/
};
