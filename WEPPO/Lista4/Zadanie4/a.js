b = require('./b.js');

exports.a  = function () {
    b.b();
    console.log( 'a' );
}