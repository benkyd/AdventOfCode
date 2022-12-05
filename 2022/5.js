const fs = require('fs');

const lines = fs.readFileSync('5.input').toString().split('\n');
const setup = lines.slice(0, 9);
const challenge = lines.slice(10, lines.length);

const parseTowers = (inputLines) => {
    // iterrate over down the Y, down each tower
    let towers = [];
    let currentTower = -1;
    for (let x = 0; x < inputLines[0].length; x++)
    for (let y = 8; y >= 0; y--) {
        const active = inputLines[y][x];
        if (active == '' || active == ' ') continue;
        if (active == '[' || active == ']') continue;
        if (!isNaN(parseInt(inputLines[y][x]))) {
            towers.push([]);
            currentTower++;
        } else  {
            towers[currentTower].push(inputLines[y][x]);
        }
    }
    return towers;
}

// part 1
const resultingTowers1 = parseTowers(setup);
for (const instruction of challenge) {
    const order = instruction.split(' ').filter(e => !isNaN(parseInt(e))).map(e => parseInt(e));
    for (let n = 0; n < order[0]; n++)
        resultingTowers1[order[2]-1].push(resultingTowers1[order[1]-1].pop());
}

// collate part 1
let part1 = '';
for (const tower of resultingTowers1)
    part1 += tower.pop();

console.log(`Part 1: ${part1}`)

const resultingTowers2 = parseTowers(setup);
console.log(resultingTowers2)
for (const instruction of challenge) {
    const order = instruction.split(' ').filter(e => !isNaN(parseInt(e))).map(e => parseInt(e));
    resultingTowers1[order[2]-1].push(...resultingTowers1[order[1]-1].splice(-1, order[0]));
}

// collate part 2
let part2 = '';
for (const tower of resultingTowers2)
    part2 += tower.pop();

console.log(`Part 2: ${part2}`)
