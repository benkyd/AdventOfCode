const fs = require('fs');

const action = { A: 0, B: 1, C: 2 };
const result = { L: 0, D: 3, W: 6 };
const matrix = [[result.D, result.W, result.L],
                [result.L, result.D, result.W],
                [result.W, result.L, result.D]]

const evalMove = (move) => {
    const theirMove = action[move[0]];
    const myMove = action[String.fromCharCode(move[1].charCodeAt(0) - 23)];
    return matrix[theirMove][myMove];
}

const moves = fs.readFileSync('2.input').toString().split('\n').map(v => v.split(' '));

const scorePot = moves.reduce((p, c, i) => { 
    p += action[String.fromCharCode(c[1].charCodeAt(0) - 23)] + 1;
    p += evalMove(c);
    return p;
}, 0);

console.log(`Part 1: ${scorePot}`);

const expected = { X: 0, Y: 3, Z: 6 };

const evalTarget = (move) => {
    const targetResult = expected[move[1]];
    for (let x = 0; x < 3; x++) {
        const char = String.fromCharCode(88 + x);
        if (evalMove([move[0], char]) == targetResult) {
            return action[String.fromCharCode(65 + x)] + 1;
        }
    }
}

const targetResolutionScorePot = moves.reduce((p, c, i) => {
    p += expected[c[1]];
    p += evalTarget(c);
    return p;
}, 0)

console.log(`Part 2: ${targetResolutionScorePot}`);
