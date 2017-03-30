long A[R][S][T];
//                 rdi,    rsi,    rdx,        rcx
long store_elem(long i, long j, long k, long *dest) {
    *dest = A[i][j][k];
    return sizeof(A);
}

/*
R * S * T * 8 = 3640
R * S * T     = 455
R * S * T     = 5 * 7 * 13

&(A[i][j][k]) = 8 * (k +  i + (i << 6) +   13j) + A =
              = 8 * (65i + 13j + k)             + A

455 > 65i + 13j + k
    Zał: R >= 13, wtedy i <- [0, 12], 65 * 12 = 845 > 455
    sprzeczność, zatem R = 1 | 5 | 7
65 > 13j + k
    65 / 13 = 5, zatem S = 1 | 5
13 > k
    więc T = 1 | 5 | 7 | 13

Tylko T może być 13, więc  T = 13  =>  k <- [0, 12]
Zatem teraz tylko R może być 7, więc R = 7 i S = 5
Ostatecznie: R=7, S=5, T=13
    // spr: 65*6 + 13*4 + 12 = 454 < 455 ok
*/
