const fs = require('fs');

const rangeCheck = (a, b) => (a[0] <= b[0] && a[1] >= b[1])
                           ||(b[0] <= a[0] && b[1] >= a[1]);

const pairs = fs.readFileSync('4.input')
                        .toString()
                        .split('\n')
                        .map(i => i.split(',')
                        .map(j => j.split('-')
                        .map(k => parseInt(k))));

const overlapingPairs = pairs.reduce((p, c) => {
    if(rangeCheck(c[0], c[1])) p++;
    return p;
}, 0);

console.log(`Part 1: ${overlapingPairs}`);

const overlapCheck = (a, b) => a[0] <= b[1] && b[0] <= a[1];

const anyOverlapingPairs = pairs.reduce((p, c) => {
    if(overlapCheck(c[0], c[1])) p++;
    return p;
}, 0);

console.log(`Part 2: ${anyOverlapingPairs}`);
