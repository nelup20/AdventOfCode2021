<?php
$file = fopen("input.txt", "r") or die("Could not open file");
$input = explode("\n", fread($file, filesize("input.txt")));

for($row = 0; $row < count($input); $row++){
    $input[$row] = str_split($input[$row]);

    if($row < count($input) - 1){
        array_pop($input[$row]);
    }
}

$COLS = count($input[0]);
$ROWS = count($input);

$low_points = [];

for($row = 0; $row < $ROWS; $row++){
    for($col = 0; $col < $COLS; $col++){
        $currPoint = $input[$row][$col];
        if($row == 0 || $row == $ROWS - 1){
            if($row == 0){
                $down = $input[$row+1][$col];
                if($col == 0){
                    if($currPoint < $input[$row][$col+1] &&
                       $currPoint < $down){
                        $low_points[] = $currPoint;
                    }
                } else if($col == $COLS - 1){
                    if($currPoint < $input[$row][$col-1] &&
                        $currPoint < $down){
                        $low_points[] = $currPoint;
                    }
                } else {
                    if($currPoint < $input[$row][$col-1] &&
                        $currPoint < $input[$row][$col+1] &&
                        $currPoint < $down){
                        $low_points[] = $currPoint;
                    }
                }
            }

            if($row == $ROWS - 1){
                $up = $input[$row-1][$col];
                if($col == 0){
                    if($currPoint < $input[$row][$col+1] &&
                        $currPoint < $up){
                        $low_points[] = $currPoint;
                    }
                } else if($col == $COLS - 1){
                    if($currPoint < $input[$row][$col-1] &&
                        $currPoint < $up){
                        $low_points[] = $currPoint;
                    }
                } else {
                    if($currPoint < $input[$row][$col-1] &&
                        $currPoint < $input[$row][$col+1] &&
                        $currPoint < $up){
                        $low_points[] = $currPoint;
                    }
                }
            }
        } else {
            $up = $input[$row-1][$col];
            $down = $input[$row+1][$col];

            if($col == 0){
                if($currPoint < $input[$row][$col+1] &&
                   $currPoint < $down &&
                   $currPoint < $up){
                    $low_points[] = $currPoint;
                }
            } else if($col == $COLS - 1){
                if($currPoint < $input[$row][$col-1] &&
                   $currPoint < $down &&
                   $currPoint < $up){
                    $low_points[] = $currPoint;
                }
            } else {
                if($currPoint < $input[$row][$col-1] &&
                    $currPoint < $input[$row][$col+1] &&
                    $currPoint < $down &&
                    $currPoint < $up){
                    $low_points[] = $currPoint;
                }
            }
        }
    }
}

$result = 0;

foreach($low_points as $point){
    $result += ($point + 1);
}

echo "Result: $result";

fclose($file);
