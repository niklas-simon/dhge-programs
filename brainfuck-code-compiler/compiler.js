import fs from 'fs/promises';
import process from 'process';

if (process.argv.length != 3) {
    console.error("usage: node compiler.js file.bfc");
    process.exit(0);
}

const input = (await fs.readFile(process.argv[2])).toString("utf-8");
let pointer = 0;

const variables = [];

const assignVariable = (match) => {
    let output = "";

    const name = match.groups.name;
    const value = Number(match.groups.value);
    const existing = variables.findIndex(variable => variable === name);

    // get index of variable
    let index;
    if (existing !== -1) {
        index = existing;
    } else {
        index = variables.push(name);
    }

    // set pointer to variable
    if (pointer < index) {
        output += ">".repeat(index - pointer);
    } else {
        output += "<".repeat(pointer - index);
    }
    output += "\n";
    pointer = index;

    if (existing !== -1) {
        // set variable to 0 if existing
        output += "[-]";
    }

    // in- or decrement variable
    output += value > 0 ? ("+".repeat(value)) : ("-".repeat(value * -1));

    return output;
}

const output = input.replace(/\s/g, "").split(/(?![;{}])/g).map(line => {
    let newLine = "\n";
    const matchVar = line.match(/\$(?<name>\w+)=(?<value>\d+);/);
    if (matchVar) {
        newLine += assignVariable(matchVar);
    }
    return newLine == "\n" ? line : newLine;
}).join("\n");

console.log(output);