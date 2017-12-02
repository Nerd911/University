function forEach(a, f) {
  for(elem of a)
    f(elem);
}

function map(a, f) {
  var result = [];
  for(elem of a)
    result.push(f(elem));
  return result;
}

function filter(a, f) {
  var result = [];
  for(elem of a)
    if(f(elem)) result.push(elem);
  return result;
}

var a = [1,2,3,4];
forEach(a, _ => { console.log( _ ); } );
// [1,2,3,4]
console.log(filter( a, _ => _ < 3 ));
// [1,2]
console.log(map( a, _ => _ * 2 ));