const fs = require('fs');

const instructions = fs.readFileSync('9.input').toString().split('\n');

const directions = {
    U: { x: 0, y: -1 },
    R: { x: 1, y: 0 },
    D: { x: 0, y: 1 },
    L: { x: -1, y: 0 },
}

const rope = { 
    segments: [{x: 0, y: 0}, {x: 0, y: 0}],
    tailHistory: new Set(),
}
// add origin
rope.tailHistory.add(JSON.stringify({ x: 0, y: 0 }));

// we first want a distance vector between the two
// if it is greater than 2 unit lengths, we want 
// to move it one closer in the most optimal direction
const integrateTailSegment = (first, second) => {
    let dx = first.x - second.x;
    let dy = first.y - second.y;
    const distance = Math.round(Math.sqrt(dx * dx + dy * dy));
    if (distance <= 1) return second;
    // normalise dx, dy to get a direction vector
    dx /= distance;
    dy /= distance;
    const rx = dx > 0 ? Math.round(dx) : Math.floor(dx);
    const ry = dy > 0 ? Math.round(dy) : Math.floor(dy);
    return { x: second.x + rx, y: second.y + ry };
}


// moves by one, up to the caller to itterate
const processHeadTailMove = (direction) => {
    rope.segments[0].x += directions[direction].x;
    rope.segments[0].y += directions[direction].y;
    rope.segments[1] = integrateTailSegment(rope.segments[0], rope.segments[1]);
    rope.tailHistory.add(JSON.stringify(rope.segments[1]));
}

for (const instruction of instructions) {
    const breakdown = instruction.split(' ');
    const direction = breakdown[0];
    const distance = parseInt(breakdown[1]);

    for (let i = 0; i < distance; i++) {
        processHeadTailMove(direction);
    }
}

console.log(`Part 1: ${Array.from(rope.tailHistory).length}`);

const processLongRopeMove = (direction) => {
    rope.segments[0].x += directions[direction].x;
    rope.segments[0].y += directions[direction].y;

    for (let i = 1; i < 10; i++)
        rope.segments[i] = integrateTailSegment(rope.segments[i-1], rope.segments[i]);

    rope.tailHistory.add(JSON.stringify(rope.segments[9]));
}

rope.segments = [];
rope.tailHistory = new Set();
for (let i = 0; i < 10; i++)
    rope.segments.push({x: 0, y: 0});

for (const instruction of instructions) {
    const breakdown = instruction.split(' ');
    const direction = breakdown[0];
    const distance = parseInt(breakdown[1]);

    for (let i = 0; i < distance; i++) {
        processLongRopeMove(direction);
    }
}

console.log(`Part 2: ${Array.from(rope.tailHistory).length}`);
