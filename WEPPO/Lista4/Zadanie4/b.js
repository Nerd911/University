a = require('./a.js');

exports.b  = function () {
    a.a();
    console.log( 'b' );
}