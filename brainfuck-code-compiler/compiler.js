import fs from 'fs/promises';
import process from 'process';

if (process.argv.length != 3) {
    console.error("usage: node compiler.js file.bfc");
    process.exit(0);
}

const input = (await fs.readFile(process.argv[2])).toString("utf-8");
let pointer = 0;

const variables = [];
const loopvars = [];

const setPointerToVariable = (name) => {
    let output = "";
    const existing = variables.findIndex(variable => variable === name);

    // get index of variable
    let index;
    if (existing !== -1) {
        index = existing;
    } else {
        index = variables.push(name) - 1;
    }

    // set pointer to variable
    if (pointer < index) {
        output += ">".repeat(index - pointer);
    } else {
        output += "<".repeat(pointer - index);
    }
    pointer = index;

    return output;
}

const assignVariable = (match) => {
    let output = "";

    const name = match.groups.name;
    const value = Number(match.groups.value);
    const existing = variables.findIndex(variable => variable === name);
    
    output += setPointerToVariable(name);

    if (existing !== -1) {
        // set variable to 0 if existing
        output += "[-]";
    }

    // in- or decrement variable
    output += value > 0 ? ("+".repeat(value)) : ("-".repeat(value * -1));

    return output;
}

const startLoop = (match) => {
    let output = "";
    const name = match.groups.name;
    const next = match.groups.next;

    loopvars.push(name);
    output += setPointerToVariable(name);

    output += "[\n";
    output += compileLine(next);

    return output;
}

const endLoop = (match) => {
    let output = "";
    const next = match.groups.next;
    const name = loopvars[loopvars.length - 1];

    output += setPointerToVariable(name);
    loopvars.splice(loopvars.length - 1, 1);

    output += "]\n";
    output += compileLine(next);

    return output;
}

const incrementVariable = (match) => {
    let output = "";
    const name = match.groups.name;
    const sign = match.groups.sign;
    const value = Number(match.groups.value);

    output += setPointerToVariable(name);
    output += sign.repeat(value);

    return output;
}

const variableInOut = (match) => {
    let output = "";
    const mode = match.groups.mode;
    const name = match.groups.name;

    output += setPointerToVariable(name);
    output += match.groups.mode === "in" ? "," : ".";

    return output;
}

const compileLine = (line) => {
    let newLine = "";
    const matchAssign = line.match(/^\$(?<name>\w+)=(?<value>\d+)$/);
    if (matchAssign) {
        newLine += assignVariable(matchAssign);
    }
    const matchLoopStart = line.match(/^loop\(\$(?<name>\w+)\)\{(?<next>.+)$/);
    if (matchLoopStart) {
        newLine += startLoop(matchLoopStart);
    }
    const matchLoopEnd = line.match(/^\}(?<next>.+)$/);
    if (matchLoopEnd) {
        newLine += endLoop(matchLoopEnd);
    }
    const matchIncrement = line.match(/^\$(?<name>\w+)(?<sign>[+-])(?<value>\d+)$/);
    if (matchIncrement) {
        newLine += incrementVariable(matchIncrement);
    }
    const matchInOut = line.match(/^(?<mode>in|out)\(\$(?<name>\w+)\)$/);
    if (matchInOut) {
        newLine += variableInOut(matchInOut);
    }
    return (newLine === "" ? line : newLine);
}

const output = input
    .replace(/\s/g, "")
    .split(";")
    .map(compileLine)
    .join("\n");

await fs.writeFile("out.bf", output);