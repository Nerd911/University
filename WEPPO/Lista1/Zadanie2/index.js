function isGood(num) {
    numText = String(num);
    var sum = 0;
    for (var i = 0; i < numText.length; ++i) {
        var digit = Number(numText.charAt(i));
        if (digit == 0 || num % digit) 
            return false;
        sum += digit;
    }
    return !(num % sum);
}

for(var i = 1; i <= 100000; ++i) {
    if(isGood(i))
        console.log(i);
}