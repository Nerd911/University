const fs = require('fs');
const path = require('path');
const readline = require('readline');

const lineReader = readline.createInterface({
  input: fs.createReadStream(path.join(__dirname, './test'))
});

counter = {};
lineReader.on('line', function (line) {
  var temp = line.match(new RegExp("^[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}"));
  if(temp){
    if(counter[temp] == null)
      counter[temp] = 0;
    counter[temp] += 1;
  }
}).on('close', () => {
  console.log(counter)
});
