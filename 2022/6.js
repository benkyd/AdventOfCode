const fs = require('fs');

const searchSoP = (buffer, uniqueness) => {
    let ret = [];
    for (let i = 0; i < buffer.length; i++) {
        ret.push(buffer.charAt(i));
        if (ret.length > uniqueness) ret.shift();
        if (ret.length == uniqueness && (new Set(ret)).size == ret.length) return { str: ret, i: i };
    }
}

const dataStream = fs.readFileSync('6.input').toString();

console.log(`Part 1: ${searchSoP(dataStream, 4).i + 1}`);
console.log(`Part 2: ${searchSoP(dataStream, 14).i + 1}`);
