function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

var root = new Tree(5);
console.log(root);
root.left = new Tree(3, new Tree(2), new Tree(1));
console.log(root);