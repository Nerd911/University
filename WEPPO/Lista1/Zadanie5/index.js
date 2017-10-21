function fibRec(n) {
    if (n == 0 || n == 1) return 1;
    return fibRec(n-1) + fibRec(n-1);
}

function fibIter(n) {
    var a = 1;
    var b = 1;
    for(var i = 2; i <= n; ++i) {
        var temp = b;
        b = b + a;
        a = b;
    }
    return b;
}

for(var i = 10; i <= 31; ++i) {
    var str = "fibonacci recursive " + i;
    console.time(str);
    fibRec(i);
    console.timeEnd(str);

    str = "fibonacci iterative " + i;
    console.time(str);
    fibIter(i);
    console.timeEnd(str);
}