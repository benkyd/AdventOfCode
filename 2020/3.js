const fs = require('fs');
const input = fs.readFileSync('3.txt').toString().split('\n');

function countTrees(lines, xoff, yoff)
{
    let treeCount = 0;
    let length = lines[0].length - 1;
    let x = 0;

    for (let i = 0; i < lines.length; i += yoff)
    {
        if (lines[i][x % length] == '#') treeCount++;
        x += xoff;
    }

    return treeCount;
}

let count = countTrees(input, 3, 1);
console.log(`Part 1, tree count: ${count}`);

let total1 = countTrees(input, 1, 1);
let total2 = countTrees(input, 3, 1);
let total3 = countTrees(input, 5, 1);
let total4 = countTrees(input, 7, 1);
let total5 = countTrees(input, 1, 2);

console.log(`Part 2, tree count: ${total1 * total2 * total3 * total4 * total5}`);


