var http = require('http');
var express = require('express');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

// tu dodajemy middleware

app.get('/', (req, res) => {
    
    // proszę zaremować i odremować tę linijkę i porównać wynik
    res.setHeader('Content-disposition', 'attachment; filename=plik.txt');
    
    res.write('123');
    res.end();
});

// tu uruchamiamy serwer
var server = http.createServer(app).listen(3000);

console.log( 'serwer started' );
