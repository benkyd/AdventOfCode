const fs = require('fs');

const rucsacks = fs.readFileSync('3.input').toString().split('\n');

const accumilatePriority = (items) => {
    let ret = 0;
    for (const item of items) {
        const char = item.charCodeAt(0);
        if (char < 97 || char > 122) {
            ret += char - 38;
        } else {
            ret += char - 96;
        }
    }
    return ret;
}

const itemDuplicatesPerRucsack = rucsacks.reduce((p, c) => {
    const firstPocket = new Set(c.slice(0, c.length / 2));
    const secondPocket = new Set(c.slice(c.length / 2));
    const intersection = Array.from(new Set([...firstPocket].filter(x => secondPocket.has(x))));
    p.push(...intersection); return p;
}, []);

console.log(`Part 1: ${accumilatePriority(itemDuplicatesPerRucsack)}`);

const groupBadges = [];
for (let i = 0; i < rucsacks.length; i += 3) {
    const elf1 = new Set(rucsacks[i + 0]);
    const elf2 = new Set(rucsacks[i + 1]);
    const elf3 = new Set(rucsacks[i + 2]);
    const intersection12 = new Set([...elf1].filter(x => elf2.has(x)));
    const intersection = Array.from(new Set([...intersection12].filter(x => elf3.has(x))));
    groupBadges.push(...intersection);
}

console.log(`Part 2: ${accumilatePriority(groupBadges)}`);
