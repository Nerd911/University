s += b[j+1] + b[--j];

tempj = j + 1;
bptr1 = b + tempj;
j = j - 1;
bptr2 = b + j;
b1 = *bptr1;
b2 = *bptr2;
sum = b1 + b2;
s = s + sum;

a[i++] -= b * (c[j*2] + 1);


tempa = a+i;
i = i+1;
tempj = j*2;
cptr = c + tempj;
tempc = *(cptr);
sum = tempc + 1;
product = b * sum;
*tempa = *tempa - product; //tu mam wątpliwości
