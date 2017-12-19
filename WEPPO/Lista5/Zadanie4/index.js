var http = require('http');
var express = require('express');
var ejs = require('ejs');
var session = require('express-session');
var cookieParser = require('cookie-parser');

var app = express();
const bodyParser = require('body-parser');
var expressValidator = require('express-validator');
app.use(expressValidator())
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended: true}))
app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
    res.render('formularz');
});

app.post('/', (req, res) => {
    req.checkBody('name', 'Imię wymagane').notEmpty();
    req.checkBody('surname', 'Nazwisko wymagane').notEmpty();
    req.checkBody('subject', 'Przedmiot wymagany').notEmpty();
    req.sanitize('name').escape();
    req.sanitize('name').trim();
    req.sanitize('surname').escape();
    req.sanitize('surname').trim();
    req.sanitize('subject').escape();
    req.sanitize('subject').trim();
    var errors = req.validationErrors();
    if (errors) {
        res.render('formularz', {error: errors});
        return;
    } 
    name = req.body.name;
    surname = req.body.surname;
    subject = req.body.subject;
    ex = new Array(10);
    for(var i = 1; i <= 10; ++i){
        ex[i-1] = req.body['ex' + i];
    }
    res.redirect('print');
});

app.get('/print', (req, res) => {
    var model = {
        name : name,
        surname : surname,
        ex : ex
    };
    res.render('print', model);
});

http
    .createServer(app)
    .listen(3000);
console.log('started');