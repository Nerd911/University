var arr = new Array(100001).fill(0);
arr[0] = arr[1] = 1;

for(var i = 2; i <= 100000; ++i) {
    if (!arr[i]) {
        console.log(i);
        for(j = i; j <= 100000; j += i) {
            arr[j] = 1;
        }
    }
}