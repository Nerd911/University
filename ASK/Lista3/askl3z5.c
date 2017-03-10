x == (int32_t)(double) x //zawsze ok, double ma większy zasięg i precyzję niż int
x == (int32_t)(float) x //to nie działa, niech x wynosi TMax
d == (double)(float) d //dla 1e40 dostajemy +inf
f == (float)(double) f //wszystko ok, uzasadnienie jak w 1
f == -(-f) //tak, zmiana znaku we floatach to po prostu negacja pierwszego bitu
1.0 / 2 == 1 / 2.0 // wszystko git, kompilator rzutuje wszystko na floaty przed porównaniem
d * d >= 0.0 //niby działa, ale może wywalić d*d do +inf
(f + d) - f == d //niech f = 1.0e20 i d = 1.0, wtedy f+f będzie zaokraglone do 1.0e20 więc całość wyniesie 0.0, a prawa strona będzie równa 1.0
