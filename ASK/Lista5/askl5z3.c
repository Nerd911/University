typedef struct {
    int x[A][B];  // A * B * 4 + off1
    // A * B * 4 + off1 = 184
    // off1 <- {0, 4}
    // dla off1=0 mamy A * B = 46 = 2*23 => NOPE
    // dla off1=4 mamy A * B = 45 = 3*3*5 = 9*5
    // zatem (patrząc niżej) A=9, B=5
    long y; // 8 | adres + 184
} str1;

typedef struct {
    char array[B];  // B + ? = 8  on jest pod adresem: 8 | adres
    // B <- [1, 8]
    int t;  // 4  offsetu nie trzeba, 4 | adres+8
    short s[A];  // 2A
    // 2A + off2 = 20  off2 <- {6, 4, 2, 0}
    // dla off2=6 mamy A = 7
    // dla off2=4 mamy A = 8
    // dla off2=2 mamy A = 9
    // dla off2=0 mamy A = 10
    long u; // 8  to musi być pod adresem: 8 | adres+32
} str2;

void set_val(str1* p, str2* q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1 + v2;
}

/*
p->y      =   q->t    +   q->u
*(p + 184)  = *(q + 8)  + *(q + 32)
  21th          19th         20th linijka
```
A * B * 4 = 184  OR A * B * 4 + 4 = 184
A * B     = 46   OR A * B         = 45
A * B     = 2*23 OR A * B         = 9*5

B <- [5, 8]  bo jakby mniej to *(q+4) === q->t

Więc A=23, B=2 lub A=9, B=5

8 + 4 + 2*A  + ? =  32
8 + 4 + 2*23 + ? =  32 OR 8 + 4 + 2*9 + ? = 32
               ? = -26 OR               ? = 2
       sprzeczność     OR  offset po shorcie prawidłowy
*/
