var http = require('http');
var express = require('express');
var ejs = require('ejs');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser')
var app = express();
var bcrypt = require('bcrypt');
app.set('view engine', 'ejs');
app.set('views', './views');
// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())
app.use( cookieParser() );
function authorize(req, res, next) {
    if ( req.cookies.user ) {
       // użytkownik jest zalogowany
       // "przepisanie" danych użytkownika żeby dostęp był jednolity
       req.user = req.cookies.user; 
       next();
    } else {
        // użytkownik niezalogowany
        // przekierowanie z zapamiętaniem strony która spowodowała przekierowanie
        res.redirect( '/login?returnUrl='+req.url); 
    }
}
var users = {
    usera : {name : "Adrian", pesel : "9607250394", pwd : "passa"},
    userb : {name : "Paweł", pesel : "9608250394", pwd : "passb"}
};

var salt = bcrypt.genSaltSync(10);

app.get('/', authorize, (req, res) => {
    res.redirect('user_info?id='+req.user+'&hash='+bcrypt.hashSync(req.user, salt));
});

app.get('/user_info', (req, res) => {
    if (req.query.hash == bcrypt.hashSync(req.query.id, salt)) {
        res.render('user_info', {user : users[req.query.id]});
    } else {
        res.render('error');
    }
});

app.get('/login', (req, res) => {
    // wyrenderuj stronę logowania
    res.render('login');
});

app.get('/resetpwd', authorize, (req, res) => {
    users[req.user].pwd = "default";
    res.redirect('/');
});

app.post('/login', (req, res) => {
    // użytkownik kliknął przycisk "zaloguj" na stronie logowania (POST)
    var username = req.body.txtUser; // na stronie jest <input type='text'     name='txtUser' ...
    var pwd      = req.body.txtPwd;  // na stronie jest <input type='password' name='txtPwd' ...
    
    if ( users[username] &&  users[username].pwd == pwd) { // w rzeczywistości - sprawdzenie w bazie danych 
        res.cookie('user', username); // wydanie ciastka, od tego momentu użytkownik jest zalogowany
        
        var returnUrl = req.query.returnUrl; 
        res.redirect( returnUrl ); // powrót do miejsca z którego nastąpiło przekierowanie tutaj
    } else {
        // nie udało się zalogować, trzeba znów pokazać stronę logowania z komunikatem
        res.render('login', { message : 'Zła nazwa logowania lub hasło' });
    }
});

http
    .createServer(app)
    .listen(3000);
console.log('started');