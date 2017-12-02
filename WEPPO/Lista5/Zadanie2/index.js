var https = require('https');
var fs = require('fs');

https.createServer( {
    pfx : fs.readFileSync('certificate.pfx'),
    passphrase : 'foo'
    },
    (req, res) => {
        
            res.setHeader('Content-type', 'text/html; charset=utf-8');
            res.write('Witamy w node.js, polskie znaki ąłżńóź');
            res.end();
        
        })
        .listen(3000);
    