//Jeżeli to czytasz nikczemniku, wziąłbyś się w końcu samemu do roboty
#include "stdio.h"
#include "stdint.h"
typedef int32_t Q16_16;

#define K   (1 << (16 - 1))

Q16_16 add(Q16_16 a, Q16_16 b){
  return a+b;
}

Q16_16 sub(Q16_16 a, Q16_16 b){
  return a-b;
}
Q16_16 sat32(int64_t x)
{
	if (x > 0x7FFFFFFF) return 0x7FFFFFFF;
	else if (x < -0x80000000) return -0x80000000;
	else return (Q16_16)x;
}

Q16_16 mul(Q16_16 a, Q16_16 b)
{
    Q16_16 result;
    int64_t temp;

    temp = (int64_t)a * (int64_t)b; // result type is operand's type
    // Rounding; mid values are rounded up
    temp += K;
    // Correct by dividing by base and saturate result
    result = sat32(temp >> 16);

    return result;
}

Q16_16 div(Q16_16 a, Q16_16 b)
{
    Q16_16 result;
    int64_t temp;

    // pre-multiply by the base (Upscale to Q16 so that the result will be in Q8 format)
    temp = (int64_t)a << 16;
    // Rounding: mid values are rounded up (down for negative values).
    if((temp >= 0 && b >= 0) || (temp < 0 && b < 0)) // OR compare most significant bits ie. if((temp >> 31) & 1 == (temp >> 15) & 1) {
        temp += b >>2;    // OR shift 1 bit ie. temp = (b >> 1);
    else
        temp -= b >>2;    // OR shift 1 bit ie. temp = (b >> 1);
    result = (Q16_16)(temp / b);

    return result;

}

//Jak już mamy operatory zdefiniowane, to reszta jest już do zrobienia ;)

int main(){
  return 0;
}
