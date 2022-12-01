const fs = require('fs');

let elfIndex = 0;
const calorieAmounts = fs.readFileSync('1.input').toString().split(`\n`).reduce((a, c) => {
    if (c == '') {
        elfIndex++;
        a[elfIndex] = 0;
        return a;
    }

    a[elfIndex] += parseInt(c);
    return a;
}, [0]);

const part1 = Math.max(...calorieAmounts);
console.log(`PART 1: ${part1}`);

const sortedCalories = calorieAmounts.sort((a, b) => b - a);
console.log(`PART 2: ${sortedCalories[0] + sortedCalories[1] + sortedCalories[2]}`);
