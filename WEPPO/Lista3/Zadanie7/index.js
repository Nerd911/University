function fib() {
  var _fibonacci = [0, 1];
  return {
    next : function() {
      var _temp = _fibonacci[1];
      _fibonacci[1] = _fibonacci[1] + _fibonacci[0];
      _fibonacci[0] = _temp;
      return {
        value : _fibonacci[0]
      }
    }
  }
}

function* fib1() {
  var fn1 = 1;
  var fn2 = 1;
  while (true) {  
    var current = fn1;
    fn1 = fn2;
    fn2 = current + fn1;
    var reset = yield current;
    if (reset) {
        fn1 = 0;
        fn2 = 1;
    }
  }
}

// var _it = fib1();
// for ( var _result; _result = _it.next(), !_result.done; ) {
//   console.log( _result.value );
// }

// for ( var i of fib1() ) {
//   console.log( i );
// }

function* take(it, top) {
  for ( var _result, _i = 0; _result = it.next(), !_result.done && _i < top; ++_i) {
    yield _result.value;
  }
}
// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fib1(), 10 ) ) {
  console.log(num);
}