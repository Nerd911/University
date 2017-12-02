function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
    if (this.left) {
        for (elem of this.left) {
            yield elem;
        }
    }
    yield this.val;
    if (this.right) {
        for (elem of this.right) {
            yield elem;
        }
    }
};

var root = new Tree(5);
console.log(root);
root.left = new Tree(3, new Tree(2), new Tree(1));
console.log(root);

for (elem of root) {
    console.log(elem);
}
