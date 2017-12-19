var http = require('http');
var express = require('express');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

// tu dodajemy middleware

app.get('/', (req, res) => {
    res.render('index');
});

// tu uruchamiamy serwer
var server = http.createServer(app).listen(3000);

console.log( 'server started' );


