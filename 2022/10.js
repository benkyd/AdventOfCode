const fs = require('fs');

const CPU = {
    signalIntegrity: 0,
    row: '',
    
    clk: 0,
    X: 1,
}

const microCode = {
    'noop': { 
        c: 1,
        o: null,
        t: null,
    },
    'addx': {
        c: 2,
        o: '+',
        t: 'X',
    }
}

for (const instruction of fs.readFileSync('10.input').toString().split('\n')) {
    const operator = instruction.split(' ')[0];
    const operand = instruction.split(' ')[1] ?? 0;
    const inst = microCode[operator];

    for (let cycle = 0; cycle < inst.c; cycle++) {
        CPU.clk++;cycle
        if (CPU.clk % 40 == 20) CPU.signalIntegrity += CPU.clk * CPU.X;

        const column = (CPU.clk - 1) % 40;
        CPU.row += CPU.X - 1 <= column && column <= CPU.X + 1 ? '█' : ' ';
        if(column == 39) {
            console.log(CPU.row);
            CPU.row = "";
        }

        // operation is applied on the last cycle of the show
        if (cycle != inst.c - 1) {
            continue;
        }

        if (inst.t == 'X') {
            CPU.X = eval(`CPU.${inst.t} ${inst.o} ${operand}`);
        }
        
    }
}

console.log(`Part 1: ${CPU.signalIntegrity}`);


