var http = require('http');
const express = require('express');
const fileUpload = require('express-fileupload');
const app = express();
var ejs = require('ejs');

// default options
app.use(fileUpload());
app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
    res.render('index');
});

app.post('/upload', function(req, res) {
  if (!req.files)
    return res.status(400).send('No files were uploaded.');
 
  // The name of the input field (i.e. "sampleFile") is used to retrieve the uploaded file
  let sampleFile = req.files.sampleFile;
 
  // Use the mv() method to place the file somewhere on your server
  sampleFile.mv('files/' + sampleFile.name, function(err) {
    if (err)
      return res.status(500).send(err);
 
    res.send('File uploaded!');
  });
});

http
.createServer(app)
.listen(3000);
console.log('started');