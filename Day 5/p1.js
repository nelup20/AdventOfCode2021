const fs = require("fs");

let data = fs.readFileSync("./input.txt", "utf8");

let input = data.split("\r\n").map(d => d.split(" -> ").map(coords => coords.split(",").map(str => parseInt(str))));
input.pop();

let grid = [];

for(let i = 0; i < 1000; i++){
    let newRow = [];
    for(let j = 0; j < 1000; j++){
        newRow.push(0);
    }
    grid.push(newRow);
}

for(let line of input){
    let [x1, y1] = line[0];
    let [x2, y2] = line[1];

    if(x1 === x2){
       let yFrom = y1 > y2 ? y2 : y1;
       let yTo = y1 > y2 ? y1 : y2;

       for(let i = yFrom; i <= yTo; i++){
           grid[i][x1] += 1;
       }
    } else if(y1 === y2){
        let xFrom = x1 > x2 ? x2 : x1;
        let xTo = x1 > x2 ? x1 : x2;

        for(let i = xFrom; i <= xTo; i++){
            grid[y1][i] += 1;
        }
    }
}

let result = 0;

for(let i = 0; i < 1000; i++){
    for(let j = 0; j < 1000; j++){
        if(grid[i][j] > 1){
            result += 1;
        }
    }
}

console.log(`Result: ${result}`);
