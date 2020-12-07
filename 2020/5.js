const fs = require('fs');
const input = fs.readFileSync('5.txt').toString().split('\n');

function bsp(lower, upper, partitions)
{    
    const current = partitions.shift(); // like pop but begining
    const diff = upper - lower;

    if (current == 'F' || current == 'L') // lower half
    {
        if (partitions.length == 0) return lower;
        upper = upper - Math.floor(diff / 2);
    } else 
    {
        if (partitions.length == 0) return upper;
        lower = lower + Math.floor(diff / 2);
    }

    return bsp(lower, upper, partitions);
}

let takenSeats = [];

let highestID = 0;

for (let seat of input)
{
    const front = seat.substr(0, 7).split(''); // 8 partitions of 128
    const left = seat.substr(7, 9).split(''); // 3 partitions of 8
    
    const row = bsp(0, 127, front);
    const col = bsp(0, 7, left);

    const id = (row * 8) + col;

    takenSeats.push(id);

    if (id > highestID) highestID = id;
}

console.log(`Part 1, Highest seat ID: ${highestID}`);

let takenSeatsUnique = [...new Set(takenSeats)];
takenSeatsUnique.sort((a, b) => { return a - b});

console.log(JSON.stringify(takenSeatsUnique));
let seat;

for (let i = 5; i < takenSeatsUnique.length; i++)
{
    if (takenSeatsUnique[i] != takenSeatsUnique[i - 1] + 1)
    {
        seat = takenSeatsUnique[i] - 1;
        break;
    }
}

console.log(`Part 2, Empty seat: ${seat}`);
