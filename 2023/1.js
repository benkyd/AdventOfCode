const input = require('fs').readFileSync('1.input').toString().split('\n').filter(Boolean);

const lookForFirstDigit = (line) => {
    for (let i = 0; i < line.length; i++) {
        const digit = parseInt(line[i]);
        if (!isNaN(digit)) {
            return [digit, i];
        }
    }
}

const lookForLastDigit = (line) => {
    for (let i = line.length - 1; i >= 0; i--) {
        const digit = parseInt(line[i]);
        if (!isNaN(digit)) {
            return [digit, i];
        }
    }
}

const part1 = () => {
    return input.reduce((acc, line) => {
        const first = lookForFirstDigit(line)[0];
        const last = lookForLastDigit(line)[0];
        const calibrated = first + "" + last;
        return acc + parseInt(calibrated);
    }, 0);
}


const words = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
const lookForFirstDigitWord = (line) => {
    let smallestIndex = 100000;
    let smallestIndexWord = "";
    for (const word of words) {
        const index = line.indexOf(word);
        if (index >= 0) {
            if (index < smallestIndex) {
                smallestIndex = index;
                smallestIndexWord = word;
            }
        }
    }
    if (smallestIndexWord === "") {
        return [0, 10000];
    }
    return [words.indexOf(smallestIndexWord) + 1, smallestIndex];
}

const lookForLastDigitWord = (line) => {
    let biggestIndex = -1;
    let biggestIndexWord = "";
    for (const word of words) {
        const index = line.indexOf(word);
        if (index >= 0) {
            if (index > biggestIndex) {
                biggestIndex = index;
                biggestIndexWord = word;
            }
        }
    }
    if (biggestIndexWord === "") {
        return [0, -1];
    }
    return [words.indexOf(biggestIndexWord) + 1, biggestIndex];
}

const part2 = () => {
    return input.reduce((acc, line) => {
        const firstDigit = lookForFirstDigit(line);
        const firstWord = lookForFirstDigitWord(line);
        const first = firstDigit[1] < firstWord[1] ? firstDigit[0] : firstWord[0];

        const lastDigit = lookForLastDigit(line);
        const lastWord = lookForLastDigitWord(line);
        const last = lastDigit[1] > lastWord[1] ? lastDigit[0] : lastWord[0];

        const calibrated = first + "" + last;
        return acc + parseInt(calibrated);
    }, 0);
}

console.log("Part 1: " + part1());
console.log("Part 2: " + part2());

