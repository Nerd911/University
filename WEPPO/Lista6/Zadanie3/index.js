var express = require('express');
var app = express();
var session = require('express-session');
var FileStore = require('session-file-store')(session);

app.use(session({ secret: 'keyboard cat',
    resave: false,
    saveUninitialized: false,
    store: new FileStore,
    cookie: { maxAge: 3600000,secure: false, httpOnly: true }
  })
);

app.get('/', function (req, res) {
  if (req.session.views) {
    req.session.views++;
    res.setHeader('Content-Type', 'text/html');
    res.write('<p>Wyswietlenia: ' + req.session.views + '</p>');
    res.end();
  } else {
    req.session.views = 1;
    res.end('Demonstracja session-file-store');
  }
});

var server = app.listen(3000, function () {
  var host = server.address().address;
  var port = server.address().port;

  console.log('Server started');
});