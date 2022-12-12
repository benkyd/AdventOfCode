const fs = require('fs');
const map = fs.readFileSync('12.input').toString().split('\n').map(s => s.split(''));

const [rows, cols] = [map.length, map[0].length - 1];
const traverseDirections = [[-1, 0], [1, 0], [0, -1], [0, 1]];

const isInMap = ([row, col]) => row >= 0 && row < rows && col >= 0 && col < cols ;
const bfsCost = currElevation => ([row, col]) => map[row][col].charCodeAt(0) - currElevation.charCodeAt(0) <= 1;

const BreadthFirst = (start, end) => {
    const viewQueue = [[start, 0]];
    const visited = new Set([JSON.stringify(start)]);
    let result = Infinity;

    while (viewQueue.length != 0) {
        const [pos, views] = viewQueue.shift();
        
        if (JSON.stringify(pos) == JSON.stringify(end)) {
            result = views;
            break;
        }
        
        // Map, so make new array for each up & right direction
        traverseDirections.map(([up, right]) => [pos[0] + up, pos[1] + right])
                          // Can we actually move there?
                          .filter(isInMap)
                          // Can we climb there?
                          .filter(bfsCost(map[pos[0]][pos[1]]))
                          // Have we seen this before?
                          .filter(pos => !visited.has(JSON.stringify(pos)))
                          // OK, add next in direction to view queue
                          .forEach(pos => {
                                visited.add(JSON.stringify(pos));
                                viewQueue.push([pos, views + 1]);
                          });
    }

    return result;
}

const partOne = () => {
    let start, end;
    for (let row = 0; row < rows; row++)
    for (let col = 0; col < cols; col++) {
        if (map[row][col] == 'S') { start = [row, col]; map[row][col] = "a"; }
        if (map[row][col] == 'E') { end = [row, col]; map[row][col] = "z"; }
    }

    const ret = BreadthFirst(start, end);
    map[end[0]][end[1]] = 'E';
    return ret;
}

const partTwo = () => {
    const starting = [];
    let end;
    for (let row = 0; row < rows; row++)
    for (let col = 0; col < cols; col++) {
        if (map[row][col] == 'a') { starting.push([row, col]) }
        if (map[row][col] == 'E') { end = [row, col]; map[row][col] = "z"; }
    }

    const candidates = [];
    for (const start of starting)
        candidates.push(BreadthFirst(start, end));

    return candidates.sort((a, b) => a - b)[0];
}

console.log(`Part 1: ${partOne()}`);
console.log(`Part 2: ${partTwo()}`);
