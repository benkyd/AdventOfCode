const fs = require('fs');

const forest = fs.readFileSync('8.input').toString().split('\n');
const Y_MAX = forest.length; 
const X_MAX = forest[0].length;

const directions = {
    u: { x: 0,  y: -1 },
    l: { x: -1, y: 0  },
    d: { x: 0,  y: 1  },
    r: { x: 1,  y: 0  },
}

const treeLocation = (x, y) => {
    // if tree is out of bounds we want to make it -1   
    if (x >= X_MAX || x < 0
     || y >= Y_MAX || y < 0) return -1;
    return forest[y][x];
}

const direcitonRecurse = (x, y, height, dir, viewDistance) => {
    const nextLocation = treeLocation(x + dir.x, y + dir.y);
    if (nextLocation == -1)
        return viewDistance;
    if (nextLocation >= height)
        return viewDistance + 1;
    return direcitonRecurse(x + dir.x, y + dir.y, height, dir, viewDistance + 1);
}

let part1 = 0;
let part2 = [];
for (let y = 0; y < forest.length; y++)
for (let x = 0; x < forest[y].length; x++) {
    // we need to look in all 4 directions until we reach a -1 now
    // part 1
    for (const direction of Object.keys(directions)) {
        if (direcitonRecurse(x, y, treeLocation(x, y), directions[direction], 0) <= 1) {
            part1++;
            break;
        }
    }
    // part 2
    let scenicScore = 1;
    for (const direction of Object.keys(directions)) {
        scenicScore *= direcitonRecurse(x, y, treeLocation(x, y), directions[direction], 0);
    }
    part2.push(scenicScore);
}

console.log(`Part 1: ${part1}`);
console.log(`Part 2: ${part2.sort((a, b) => b - a)[0]}`);
