const fs = require('fs');
const { default: test } = require('node:test');

const monkeys = [];

// parse monkeys
const parseMonkeys = (monkeyString) => {
    const lines = monkeyString.split('\n');
    const startingItems = lines[1].split(':')[1].split(',').map(x => parseInt(x));
    const op = lines[2].split('new = ')[1];
    const test = { 
        divis: parseInt(lines[3].split('by ')[1]),
        pass: parseInt(lines[4].split('monkey')[1]),
        fail: parseInt(lines[5].split('monkey')[1]),
    };

    monkeys.push({
        inventory: startingItems,
        operation: op,
        test: test,
        inspections: 0,
    });
}

const input = fs.readFileSync('11.input').toString().split('\n\n');
for (const monkey of input) parseMonkeys(monkey);

for (let round = 0; round < 20; round++) {
    for (let i in monkeys) {
        const monkey = monkeys[i];

        for (let j in monkey.inventory) {
            const item = monkey.inventory[j];
            monkey.inspections++;

            const old = item; // for eval
            let newWorry = Math.floor(eval(monkey.operation) / 3);
            if (newWorry % monkey.test.divis == 0) {
                monkeys[monkey.test.pass].inventory.push(newWorry);
            } else {
                monkeys[monkey.test.fail].inventory.push(newWorry);
            }
        }
        monkey.inventory = [];
    }
}

console.log(`Part 1: ${monkeys.sort((a, b) => b.inspections - a.inspections)[0].inspections * monkeys.sort((a, b) => b.inspections - a.inspections)[1].inspections}`);

monkeys.length = 0;
for (const monkey of input) parseMonkeys(monkey);

const product = monkeys.map((monkey) => monkey.test.divis).reduce((acc, n) => acc * n);

for (let round = 0; round < 10000; round++) {
    for (let i in monkeys) {
        const monkey = monkeys[i];

        for (let j in monkey.inventory) {
            const item = monkey.inventory[j];
            monkey.inspections++;

            const old = item; // for eval
            let newWorry = Math.floor(eval(monkey.operation) % product);
            if (newWorry % monkey.test.divis == 0) {
                monkeys[monkey.test.pass].inventory.push(newWorry);
            } else {
                monkeys[monkey.test.fail].inventory.push(newWorry);
            }
        }
        monkey.inventory = [];
    }
}

console.log(`Part 2: ${monkeys.sort((a, b) => b.inspections - a.inspections)[0].inspections * monkeys.sort((a, b) => b.inspections - a.inspections)[1].inspections}`);
