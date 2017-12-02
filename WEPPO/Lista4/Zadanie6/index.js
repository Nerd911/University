const fs = require('fs');
var path = require('path');
fs.readFile(path.join(__dirname, './test'), function (err, data) {
  if (err) throw err;
  console.log(String(data));
});