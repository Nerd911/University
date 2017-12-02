var piwo = {
    _rodzaj : "",
    get rodzaj() {
        return piwo._rodzaj;
    },
    set rodzaj(rodzaj) {
        piwo._rodzaj = rodzaj;
    },
    toString : function() {
        return piwo._rodzaj;
    }
}

piwo.rodzaj = "APA";
console.log(piwo.toString());

piwo._procent = 5;
piwo.czyMocne = function() {
    return piwo._procent > 5;
}

console.log(piwo.czyMocne());

Object.defineProperty(piwo, 'procent', {
    get : function() {
        return piwo._procent;
    },
    set : function(num) {
        piwo._procent = num;
    }
});

piwo.procent = 10;
console.log(piwo.procent);
console.log(piwo.czyMocne());
