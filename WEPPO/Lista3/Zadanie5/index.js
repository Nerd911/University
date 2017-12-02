function sum(...args) {
  var result = 0;
  for (var arg of args) {
    result += arg;
  }
  return result;
}

console.log(sum(1, 2, 3, 4));

