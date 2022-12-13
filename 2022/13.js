const fs = require('fs');

const pairs = fs.readFileSync('13.input').toString().split('\n\n').map(e => e.split('\n').map(f => JSON.parse(f)));

const order = (left, right) => {
    for (let i = 0; i < left.length; i++) {
        if (right[i] == undefined) return false;
        let theOrder;
        let one = false;
        if (Array.isArray(left[i]) && Array.isArray(right[i])) {
            theOrder = order(left[i], right[i]);
            one = true;
        } else if (Array.isArray(left[i])) {
            theOrder = order(left[i], [right[i]]);
            one = true;
        } else if (Array.isArray(right[i])) {
            theOrder = order([left[i]], right[i]);
            one = true
        }
        if (theOrder != null) return theOrder;

        if (!one) {
            if (left[i] < right[i]) return true;
            else if (left[i] > right[i]) return false;
        }
    }
    return left.length < right.length ? true : null;
};
  
let part1 = 0;
for (let i = 0; i < pairs.length; i++) {
    if (order(pairs[i][0], pairs[i][1])) part1 += i + 1;
}

console.log(`Part 1: ${part1}`);

let joinedPairs = pairs.reduce((acc, cur) => {
    return [...acc, cur[0], cur[1]];
}, []);
const dividerPacket1 = [[2]];
const dividerPacket2 = [[6]]
joinedPairs.push(dividerPacket1);
joinedPairs.push(dividerPacket2);
joinedPairs.sort((a, b) => (order(a, b) ? -1 : 1));

// why are we 1 indexing
const part2 = (joinedPairs.indexOf(dividerPacket1) + 1) * (joinedPairs.indexOf(dividerPacket2) + 1);
  
console.log(`Part 2: ${part2}`);
  
