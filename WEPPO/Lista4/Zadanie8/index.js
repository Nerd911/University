const fs = require('fs');
var path = require('path');

function readContent(callback) {
  fs.readFile(path.join(__dirname, './test'), function (err, content) {
      if (err) return callback(err)
      callback(null, content)
  })
}

readContent(function (err, content) {
  console.log(String(content))
})

function fspromise(p) {
  return new Promise( function( res, rej ) {
    fs.readFile(p, function(err, data) {
      if ( err )
        rej(err );
      res( data.toString() );
    });
  } );
}

fspromise(path.join(__dirname, './test'))
  .then(function(data) {
    console.log(data);
  });		

  const {promisify} = require('util');
  const readFileAsync = promisify(fs.readFile); // (A)
  
  
  readFileAsync(path.join(__dirname, './test'))
    .then((text) => {
        console.log(String(text));
    })
    .catch((err) => {
        console.log('ERROR:', err);
    });

async function asfun() {
  const text = await readFileAsync(path.join(__dirname, './test'));
  console.log(String(text));
}
asfun();