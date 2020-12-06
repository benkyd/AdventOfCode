const fs = require('fs');
const input = fs.readFileSync('4.txt').toString().split('\n');

const requiredFields = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'];

let currentPassport = {};
for (const line of input)
{
    console.log(input + '\nbruh')
    if (line == '') 
    {
        console.log('new passport')
        currentPassport = {};
    }
}
