const exp = require('constants');
const fs = require('fs');

const terminalLines = fs.readFileSync('7.input').toString().split('\n');

const directoryTree = {
    '': { size: 0, items: [] },
};

let exploratoryPath = [];
for (let i in terminalLines) {
    const line = terminalLines[i].split(' ');

    if (terminalLines[i].startsWith('$')) {
        if (line[1] == 'ls') continue;
        switch (line[2]) {
            case '/': exploratoryPath = []; break;
            case '..': exploratoryPath.pop(); break;
            default: exploratoryPath.push(line[2]); break;
        }
        if (!directoryTree[exploratoryPath]) {
            directoryTree[exploratoryPath] = {};
            directoryTree[exploratoryPath].items = [];
            directoryTree[exploratoryPath].size = 0;
        }

    } else {
        if (isNaN(parseInt(line[0]))) continue;
        // we can assume it is a member of the active dir, exploratoryPath
        const item = {
            size: parseInt(line[0]),
            name: line[1],
        }
        directoryTree[exploratoryPath].items.push(item);
        directoryTree[exploratoryPath].size += item.size;
        // recursively update parents to reflect new size
        const tempPath = structuredClone(exploratoryPath);
        while (tempPath.pop())
            directoryTree[tempPath].size += item.size;
    }
}

let part1 = 0;
for (const dir in directoryTree) {
    if (directoryTree[dir].size <= 100000) {
        part1 += directoryTree[dir].size;
    }
}

console.log(`Part 1: ${part1}`);

let part2 = [];
const fsUsedSpace = directoryTree[''].size;
const fsMaxSpace = 70000000;
const fsNeededSpace = 30000000;
const fsDeleteMinSize = fsNeededSpace - (fsMaxSpace - fsUsedSpace)
for (const dir in directoryTree) {
    if (directoryTree[dir].size >= fsDeleteMinSize) {
        part2.push(directoryTree[dir].size);
    }
}

console.log(`Part 2: ${part2.sort((a, b) => a - b)[0]}`);
