long switch_prob(long x, long n)
{
    n -= 0x3C;
    long retVal;
    switch(n)
    {
        case 0:
        case 1:
            return x * 8;
        case 4:
            return x >> 3;
        case 2:
            retVal = x;
            retVal <<= 4;
            retVal -= x;
            x = retVal;
        case 5:
            x *= x;
        case 3:
        default:
            retVal = x + 0x4B;
    }
    return retVal;
}

int main() {
    return 0;
}
