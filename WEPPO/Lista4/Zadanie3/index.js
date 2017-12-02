var Foo = (function() {
    function Qux() {
        console.log("private");
    }

    return function(){
        this.Bar = function() {
            Qux();
            console.log("public");
        }
    }
})();

var myObj = new Foo();
myObj.Bar();