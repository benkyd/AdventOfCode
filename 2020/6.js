const fs = require('fs');

const input = fs.readFileSync('6.txt').toString().split('\n\n');

let uniqueGroupAnswers = [];
for (let i of input)
    uniqueGroupAnswers.push([... new Set(i.replace(/\n/g, '').split(''))]);

let total = 0;
for (let i of uniqueGroupAnswers)
    total += i.length;

console.log(`Part 1, Sum of answer counts: ${total}`);
total = 0;

function invArrDiff(arr)
{
    let seen = [];
    for (str of arr)
    {
        str = str.split('');
        for (i of str)
        {
            if (seen.includes(i))
                seen.push(i);
        }
    }
    return seen;
}

for (let i of input)
{
    let group = i.split('\n');
    for (j of group)
        j.split('');

    total += invArrDiff(group).length;
}

console.log(`Part 2, Sum of answer counts: ${total}`);
