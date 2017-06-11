int puzzle(long x, unsigned n) {
    if (n == 0) return 0;
    unsigned result = 0;

    // wiemy że n != 0; i == 0, wiec mozna for z pominiętym war
    for (unsigned i = 0; i < n; i++) {
        result += x & 1;  // wyciągamy parzystość x
        x >>= 1;  // x = x div 2
    }

    return result;
} // ile '1' w 'n' pierwszych (od najmłodszych) bitach
