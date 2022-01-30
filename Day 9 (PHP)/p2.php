<?php

$file = fopen("input.txt", "r") or die("Could not open file");
$input = explode("\n", fread($file, filesize("input.txt")));

for($row = 0; $row < count($input); $row++){
    $input[$row] = str_split($input[$row]);

    if($row < count($input) - 1){
        array_pop($input[$row]);
    }
}

define("COLS",  count($input[0]));
define("ROWS",  count($input));

$sizes = [];
$basin_areas = [];

$isNewBasin = true;


for($row = 0; $row < ROWS; $row++) {
    for($col = 0; $col < COLS; $col++){
        if(isInBasin($input[$row][$col])){
            if($isNewBasin){
                $sizes[] = 1;
                $basin_areas[] = [[$row, $col]];
                $isNewBasin = false;
            } else {
                incLast($sizes);
                addToBasinArea($basin_areas, $row, $col);
            }

            $input[$row][$col] = -1;

            if($row + 1 < ROWS && isInBasin($input[$row+1][$col])){
                calcBelow($input, $sizes, $basin_areas, $row + 1, $col);
            }
        } else {
            $isNewBasin = true;
        }
    }
}

// Yeah, I know it's bad (~n^2 and then n^2 in isConnected()), but I'm just glad I finally solved it
// with recursion. I struggled before with an iteration-based solution & couldn't solve it.
for($i = 0; $i < count($basin_areas); $i++){
    for($j = $i + 1; $j < count($basin_areas); $j++){
        if(isConnected($basin_areas[$i], $basin_areas[$j])){
            $sizes[$i] += $sizes[$j];
        }
    }
}

sort($sizes);
$result = array_product([$sizes[count($sizes) - 1],
                         $sizes[count($sizes) - 2],
                         $sizes[count($sizes) - 3]]);

echo "Result: $result";


function calcBelow(&$input, &$sizes, &$basin_area, $row, $col){
    while($col - 1 >= 0 && isInBasin($input[$row][$col - 1])) $col--;

    while($col < COLS && isInBasin($input[$row][$col])){
        if($row + 1 < ROWS && isInBasin($input[$row + 1][$col])){
            calcBelow($input, $sizes, $basin_area, $row + 1, $col);
        }

        $input[$row][$col] = -1;
        incLast($sizes);
        addToBasinArea($basin_area, $row, $col);

        $col++;
    }
}

function isInBasin($cell){
    return $cell >= 0 && $cell < 9;
}

function incLast(&$sizes){
    $sizes[count($sizes) - 1] += 1;
}

function addToBasinArea(&$basin_area, $row, $col){
    $basin_area[count($basin_area) - 1][] = [$row, $col];
}


function isConnected($arr1, $arr2){
    for($i = 0; $i < count($arr1); $i++){
        for($j = 0; $j < count($arr2); $j++){
            if(($arr1[$i][0] == $arr2[$j][0] && $arr1[$i][1] == $arr2[$j][1]) ||
               (abs($arr1[$i][0] - $arr2[$j][0]) == 1 && $arr1[$i][1] == $arr2[$j][1]) ||
               (abs($arr1[$i][1] - $arr2[$j][1]) == 1 && $arr1[$i][0] == $arr2[$j][0])) return true;
        }
    }

    return false;
}

